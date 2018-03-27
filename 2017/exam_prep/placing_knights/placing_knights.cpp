// ALGOLAB BGL Tutorial 1
// Code snippets demonstrating 
// - graph definitions
// - several algorithms (components, distance-based algorithms, maximum matching)
// - how to pass exterior property maps
// - use of iterators

// Compile and run with one of the following:
// g++ -std=c++11 -O2 bgl-code_snippets.cpp -o bgl-code_snippets; ./bgl-code_snippets
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl-code_snippets.cpp -o bgl-code_snippets; ./bgl-code_snippets

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


// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices	
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) //cout << #x << " = " << x << endl 

// Functions
// ========= 
void do_testcases() {
	int n; cin >> n;
	vector<vector<bool> > cb(n, vector<bool>(n));
	
	int num_holes = 0;
	REP(i, n){
		REP(j, n){
			bool b; cin >> b;
			cb[i][j] = b;
			if(!b) ++num_holes;
		}
	}
	DEBUG(num_holes);
	Graph G(n*n);


	REP(i, n){
		REP(j, n){	
			
			if(!cb[i][j]) continue;
			
			if(i-1 >= 0 && j-2 >= 0 && cb[i-1][j-2])
				add_edge(i + j*n, (i-1)+ (j-2)*n, G);
			if(i-1 >= 0 && j+2 < n && cb[i-1][j+2])
				add_edge(i + j*n, (i-1)+ (j+2)*n, G);
			if(i+1 < n && j-2 >= 0 && cb[i+1][j-2])
				add_edge(i + j*n, (i+1)+ (j-2)*n, G);
			if(i+1 < n && j+2 < n && cb[i+1][j+2])
				add_edge(i + j*n, (i+1)+ (j+2)*n, G);
			if(i-2 >= 0 && j-1 >= 0 && cb[i-2][j-1])
				add_edge(i + j*n, (i-2)+ (j-1)*n, G);
			if(i-2 >= 0 && j+1 < n && cb[i-2][j+1])
				add_edge(i + j*n, (i-2)+ (j+1)*n, G);
			if(i+2 < n && j-1 >= 0 && cb[i+2][j-1])
				add_edge(i + j*n, (i+2)+ (j-1)*n, G);
			if(i+2 < n && j+1 < n && cb[i+2][j+1])
				add_edge(i + j*n, (i+2)+ (j+1)*n, G);
		}
	}
	
	// Edmonds' maximum cardinality matching
	// =====================================
	vector<Vertex> matemap(n*n);		// We MUST use this vector as an Exterior Property Map: Vertex -> Mate in the matching
	edmonds_maximum_cardinality_matching(G, make_iterator_property_map(matemap.begin(), get(vertex_index, G)));
	// Using the matemap 
	// =================
	const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();	// unmatched vertices get the NULL_VERTEX as mate.
	int matchingsize = matching_size(G, make_iterator_property_map(matemap.begin(), get(vertex_index, G)));
	DEBUG(matchingsize);
	
	cout << (((n*n) - num_holes) - matchingsize) << endl;
}

// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false); 
	int t;	cin >> t;
	while(t--)	do_testcases();
	return 0;
}


