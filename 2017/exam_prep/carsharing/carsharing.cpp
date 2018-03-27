#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
// Namespaces
using namespace boost;
using namespace std;

// BGL Graph definitions
// ===================== 
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;
// Interior Property Maps
typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  		OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w;
        capacitymap[reverseE] = 0;
        weightmap[reverseE] = -w;
        revedgemap[e] = reverseE; 
        revedgemap[reverseE] = e; 
    }
};

const int MAXP = 100;
const int INF = INT_MAX;

struct Booking{
	int s, t, d, a, p;
};


void do_testcases(){
	int N, S; cin >> N >> S;
	vector<set<int> > times(S);
	vector<map<int, int> > time_to_pos(S);
	vector<int> L(S);
	for(int i=0; i<S; ++i){
		cin >> L[i];
		times[i].insert(0);
		times[i].insert(100000); //insert first and last time of station
	}
	
	vector<Booking> bookings(N);
	for(int i=0; i<N; ++i){
		int s, t, d, a, p;
		//we want 0 based indexing
		cin >> s >> t >> d >> a >> p;
		s--; t--; 
		bookings[i] = {s, t, d, a, p};
		times[s].insert(d);
		times[t].insert(a);
	}
	
	vector<int> psum(S+1);
	for(int i=0; i<S; ++i){
		int j = 0;
		for(auto &it : times[i]){
			time_to_pos[i].insert(make_pair(it, j));
			++j;
		}
		psum[i+1] = psum[i] + time_to_pos[i].size();
	}
	
	
	int graphsize = 0;
	vector<int> timesize(S);	
	vector<int> timesizesum(S);

	for(int i=0; i<S; ++i){
		graphsize += times[i].size();
		timesize[i] = times[i].size();
	}

    // Create Graph and Maps
    int T = psum.back();
    Graph G(T+2);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    EdgeWeightMap weightmap = get(edge_weight, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder ea(G, capacitymap, weightmap, revedgemap);
    
    int source = T;
    int target = T+1;
      
    for(int i=0; i<S; ++i){
		ea.addEdge(psum[i+1]-1, target, INF, 0); //add to target
		ea.addEdge(source, psum[i], L[i], 0); //add to source
		
		int it = -1, lastt = 0;
		for(auto &t : times[i]){
			if(it != -1){
				ea.addEdge(psum[i]+it, psum[i]+it+1, INF, (t-lastt) * MAXP);
			}
			it++; lastt = t;
		}
		
	}
    
	//add drive edges
	for(int i=0; i<N; ++i){
		int u = psum[bookings[i].s] + time_to_pos[bookings[i].s][bookings[i].d];
		int v = psum[bookings[i].t] + time_to_pos[bookings[i].t][bookings[i].a];
		ea.addEdge(u, v, 1, (bookings[i].a-bookings[i].d)*MAXP-bookings[i].p);
	}

    

    // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights
    successive_shortest_path_nonnegative_weights(G, source, target);
    int flow = 0;
    OutEdgeIt e, eend;
    for(tie(e, eend) = out_edges(vertex(source,G), G); e != eend; ++e) {
        flow += capacitymap[*e] - rescapacitymap[*e];
    }

	int cost = MAXP*100000*flow-find_flow_cost(G);
    cout << cost << endl;
}
int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
    return 0;
}
