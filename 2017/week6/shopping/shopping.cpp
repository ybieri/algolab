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
    property<edge_reverse_t, Traits::edge_descriptor
    > > > >Graph;
    
    
// Interior Property Maps
typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

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

    void addEdge(int u, int v, long c, bool bidirectional) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        capacitymap[reverseE] = 0;
        revedgemap[e] = reverseE; 
        revedgemap[reverseE] = e; 
        if(bidirectional) addEdge(v, u, c, false);
    }
};

void do_testcases() {
	int V, E, S; //intersections, streets, stores
	cin >> V >> E >> S;
	
    // Create Graph and Maps
    Graph G(V+1);
    EdgeCapacityMap capacitymap = get(edge_capacity, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, revedgemap);
    
    // read in location of stores
	vector<int> stores(V, 0);
	for(int i=0; i<S; ++i){
		int store;
		cin >> store;
		++stores[store];
	}

	// add edges
	for(int i=0; i<E; ++i){
		int u, v;
		cin >> u >> v;
		eaG.addEdge(u,v,1, true);
	}
	
	int sink = V;
	// add edge from each store to sink. At least one store is present if stores > 0
	for(int i=0; i<V; ++i){
		if(stores[i] > 0)
			eaG.addEdge(i, sink, stores[i], false);
	}
	
    int flow = push_relabel_max_flow(G, 0, sink);
    
    if(flow == S) cout << "yes" << endl;
    else cout << "no" << endl;

}

int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
    return 0;
}

