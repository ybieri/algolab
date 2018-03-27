// ALGOLAB BGL Tutorial 3
// Code snippets demonstrating 
// - MinCostMaxFlow with negative edge costs using cycle_canceling
// - MinCostMaxFlow with negative edge costs using successive_shortest_path_nonnegative_weights

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
    property<edge_reverse_t, Traits::edge_descriptor > > > > Graph;
// Interior Property Maps
typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        capacitymap[reverseE] = 0;
        revedgemap[e] = reverseE; 
        revedgemap[reverseE] = e; 
    }
};

void do_testcases() {
	int N, M; //num players, num rounds
	cin >> N >> M;
	

    // Create Graph and Maps
    Graph G(N + M + 2); //2: source, target
    
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, revedgemap);
    
    
    int source = N+M;
    int target = N+M+1;
    
    //add edges. player to target missing
    for(int i=0; i<M; ++i){
		int a ,b, c; 
		cin >> a >> b >> c;
		
		//vetices 0 - N-1 are players, the next M are rounds
		
		int round = N+i;
		
		eaG.addEdge(source, round, 1); //add edge from source to the round
		
		if(c==1) eaG.addEdge(round,a,1);
		else if(c==2) eaG.addEdge(round,b,1);
		else if (c==0){
			eaG.addEdge(round,a,1);
			eaG.addEdge(round,b,1);
		}
    
	}
    
    int totalscore = 0;
	for(int i=0; i<N; ++i){
		int score; cin >> score;
		totalscore += score;
		eaG.addEdge(i,target,score);
	}
	
    // Run the algorithm

    // Option 1: Min Cost Max Flow with cycle_canceling
    int flow = push_relabel_max_flow(G, source, target);

	if(flow == totalscore && totalscore == M) cout << "yes" << endl;
	else cout << "no" << endl;
}

int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
    return 0;
}
