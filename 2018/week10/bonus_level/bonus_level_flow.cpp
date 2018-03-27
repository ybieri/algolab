// Includes
// ========
// STL includes
#include <iostream>
#include <bits/stdc++.h>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

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

void do_testcases() {
   int N; cin >> N;
   
   const int DELTA = 100;
   
	// Create Graph and Maps
	Graph G(2*N*N);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	Vertex src = add_vertex(G);
	Vertex trg = add_vertex(G);

	vector<vector<int>> coins(N, vector<int>(N,0));
	REP(i,N){
		REP(j,N){
			cin >> coins[i][j];
		}
	}

	//add source and target edges
	eaG.addEdge(src, 0 , 2, 0);
	eaG.addEdge(2*N*N-1, trg, 2, 0);

	REP(i,N){
		REP(j,N){
			int IN = i*N+j;
			int OUT = IN+N*N;
			int CAP = (i==0 && j==0 || i==N-1 && j==N-1) ? 2 : 1;
			eaG.addEdge(IN, OUT, CAP, DELTA-coins[i][j]); //vertex capacity edge
			
			int DOWN = IN+N;
			int RIGHT = IN+1;
			
			//add movement down and right from out edges
			if(i<N-1) eaG.addEdge(OUT, DOWN,  1, 0);
			if(j<N-1) eaG.addEdge(OUT, RIGHT, 1, 0);
		}
	}

	boost::successive_shortest_path_nonnegative_weights(G, src, trg);
    int cost = boost::find_flow_cost(G);
	
	// 2*2 = 4 movements, N -1 vertices to visit, n-2 edges. 
	int totaldelta = (4*N-2)*DELTA;

	cout << -(cost-totaldelta + coins[0][0] + coins[N-1][N-1]) << endl;

}


int main(){
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
