// Includes
// ========
// STL includes
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

#define REP(i,n) for(int i=0; i<(int) n; ++i)
#define DEBUG(x) //cout << #x << " = " << x << endl

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices	
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


// Functions
// ========= 
void do_testcases() {
	int k; cin >> k;
	int line;
	vector<int> tree;
	int V=0;
	vector<int> startindex(k); //0 - k-1
	REP(i,k){
		startindex[i] = V;
		REP(j, i+1){
			int we; cin >> we;
			tree.push_back(we);
			++V;
		}
	}
		
	Graph G(2*V);	// creates an empty graph on n vertices
	WeightMap weightmap = get(edge_weight, G);
	
	REP(i,k-1){
		REP(j,i+1){			
			int from = 2*(startindex[i] + j);
			int v = 2*(startindex[i+1]+j)+1;
			Edge e;	bool success;
			tie(e, success) = add_edge(from, v, G); weightmap[e] = 0; //0 3
			tie(e, success) = add_edge(v-1, from+1, G);	weightmap[e] = 0; // 2 1
			tie(e, success) = add_edge(from, v+2, G); weightmap[e] = 0; //0 5
			tie(e, success) = add_edge(v+1, from+1, G); weightmap[e] = 0; // 4 1
			tie(e, success) = add_edge(v-1, v+2, G); weightmap[e] = 0;  // 2 5
			tie(e, success) = add_edge(v+1, v, G); weightmap[e] = 0; // 4 3
		}
	}
	
	REP(i,V){
		Edge e;	bool success;			
		tie(e, success) = add_edge(2*i+1, 2*i, G); 
		weightmap[e] = tree.at(i);	
	}

	// Dijkstra shortest paths
	// =======================
	vector<int> distmap1(2*V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	vector<int> distmap2(2*V);
	vector<int> distmap3(2*V);
	
	
	
	dijkstra_shortest_paths(G, 0, // We MUST provide at least one of the two maps
		distance_map(make_iterator_property_map(distmap1.begin(), get(vertex_index, G))));	// distance map as Named Parameter
	dijkstra_shortest_paths(G, 2*startindex.at(k-1), // We MUST provide at least one of the two maps
		distance_map(make_iterator_property_map(distmap2.begin(), get(vertex_index, G))));
	dijkstra_shortest_paths(G, 2*(V-1), // We MUST provide at least one of the two maps
		distance_map(make_iterator_property_map(distmap3.begin(), get(vertex_index, G))));
	
	int mindist = INT_MAX;
	REP(i, V){
		int in = 2*i + 1;
		DEBUG(in);
		DEBUG(distmap1[in]); DEBUG(distmap2[in]); DEBUG(distmap3[in]);

		mindist = std::min(mindist, distmap1[in]+distmap2[in]+distmap3[in] + tree[i]);
	}
	cout << mindist << endl;
	
}

// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int t;	cin >> t;
	while(t--)	do_testcases();
	return 0;
}


