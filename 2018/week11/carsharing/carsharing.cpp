// ALGOLAB BGL Tutorial 3
// Code snippets demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Compile and run with one of the following:
// g++ -std=c++11 -O2 bgl_mincostmaxflow.cpp -o bgl_mincostmaxflow; ./bgl_mincostmaxflow
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl_mincostmaxflow.cpp -o bgl_mincostmaxflow; ./bgl_mincostmaxflow

// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

typedef vector<int> vi;


// BGL Graph definitions
// ===================== 
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, Traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > Graph; // new!
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type      EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t >::type       EdgeWeightMap; // new!
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type       ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w; // new!
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w; // new
        revedgemap[e] = rev_e; 
        revedgemap[rev_e] = e; 
    }
};

struct Booking{
	int s,t,d,a,p;
};

void do_testcases(){
	int N, S; cin >> N >> S;
	
	const int DELTA = 100;
	vector<set<int>> times(S);

	//stations
	vi init(S);
	REP(i,S){
		cin >> init[i];
		times[i].insert(0);
		times[i].insert(100000); //time of first and last station time
	}
	
	
	vector<Booking> bookings(N);
	REP(i,N){
		int s,t,d,a,p; cin >> s >> t >> d >> a >> p;
		--s; --t; //fucking 1 based indexing
		bookings[i] = {s,t,d,a,p};
		times[s].insert(d); times[t].insert(a);
	}
	
	//map individual station times to global index
	vector<map<int,int>> M(N);
	//how many statios before
	vi starting(S+1, 0);
	REP(s,S){//for all stations
		int i=0;
		for(auto &it : times[s]){
			M[s][it] = i;
			++i;
		}
		starting[s+1] = starting[s] + M[s].size();
	}
	
	
    // Create Graph and Maps
    int T = starting.back();
    
    Graph G(T+2);
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);
    
    int src = T;
    int trg = T+1;

	
	REP(i,S){//add src,trg edges
		eaG.addEdge(src, starting[i], init[i], 0);
		eaG.addEdge(starting[i+1]-1, trg, INT_MAX, 0);
		//add parking edges
		int it = -1; int lastt = 0;
		for(auto &t: times[i]){
			if(it != -1){
				eaG.addEdge(starting[i]+it, starting[i]+it+1, INT_MAX, DELTA * (t-lastt)); //difference in times * DELTA.
			}
			++it; lastt = t;
		}
	}
	
	//add booking edges
	REP(i,N){
		eaG.addEdge(starting[bookings[i].s] + M[bookings[i].s][bookings[i].d], //staring index of the start station + index of edge in station
					starting[bookings[i].t] + M[bookings[i].t][bookings[i].a],
					1, (bookings[i].a-bookings[i].d)*DELTA - bookings[i].p); //time difference time delta minus cost
	}
	
	
    boost::successive_shortest_path_nonnegative_weights(G, src, trg);

	int flow = 0;
    // Iterate over all edges leaving the source to sum up the flow values.
    OutEdgeIt e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(src,G), G); e != eend; ++e) {
        flow += capacitymap[*e] - rescapacitymap[*e];
    }
	
	int cost = DELTA*100000*flow-find_flow_cost(G);
    cout << cost << endl; 
	
}

// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false);
	int T;	cin >> T;	// First input line: Number of testcases.
	while(T--)	do_testcases();
	return 0;
}
