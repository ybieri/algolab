#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
// Namespaces
using namespace std;
using namespace boost;


// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices	
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


// Functions
// ========= 
void testcases() {
	int V, E;
	cin >> V >> E;
	int s, t;
	cin >> s >> t;
	
	Graph G(4*V);	// 4 graphs. even paths, odd paths, even weight, odd weight
	WeightMap weightmap = get(edge_weight, G);
	
	for (int i = 0; i < E; ++i) {
		Edge e;	bool success;
		int u, v, w; cin >> u >> v >> w;
		//first two even length, second two odd lenghts.
		// 1, 3 even weight, 2,4 odd weight
		tie(e, success) = add_edge(4*u,		4*v+2 + w%2, G); 	weightmap[e] = w;
		tie(e, success) = add_edge(4*u+1, 	4*v+3 -	w%2, G);	weightmap[e] = w;
		tie(e, success) = add_edge(4*u+2, 	4*v   +	w%2, G);	weightmap[e] = w;
		tie(e, success) = add_edge(4*u+3, 	4*v+1 -	w%2, G);	weightmap[e] = w;
	}
	
	// Dijkstra shortest paths
	// =======================
	vector<int> predmap(4*V);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	vector<int> distmap(4*V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	dijkstra_shortest_paths(G, 4*s, // We MUST provide at least one of the two maps
		predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	// distance map as Named Parameter
	
	
	if(distmap[(4*t)+3] == INT_MAX)
		cout << "no" << endl;
	else
		cout << distmap[(4*t)+3] << endl;
}

// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	cin >> T;
	while(T--)	testcases();
	return 0;
}


