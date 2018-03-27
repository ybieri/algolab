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
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t,int> > DiGraph; // An edge-weighted digraph

typedef graph_traits<DiGraph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<DiGraph>::vertex_descriptor	Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef property_map<DiGraph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

void do_testcases(){

	int V, E, A, S, C, D;
	cin >> V >> E >> A >> S >> C >> D;
	
	DiGraph G(V);
	WeightMap weightmap = get(edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38

	for(int i=0; i<E; ++i){
		char slope_lift;
		int u, v, w;
		cin >> slope_lift >> u >> v >> w;
		Edge e; bool success;
		tie(e, success) = add_edge(u, v, G);
		weightmap[e] = w;
		// if we have a skilift, add reverse edge too
		if (slope_lift == 'L') {
			tie(e, tuples::ignore) = add_edge(v, u, G);
			weightmap[e] = w;
		}
	}

	// need dijkstra from every agent
	
	vector<vector<int> > distmap(A, vector<int>(V));		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source

	for(int a=0; a<A; ++a){
		int position; cin >> position;
		dijkstra_shortest_paths(G, position, // We MUST provide at least one of the two maps
			distance_map(make_iterator_property_map(distmap[a].begin(), get(vertex_index, G))));	// distance map as Named Parameter
	}
	
	// graph from Agents to Shelters
	
	vector<vector<int> > T(A, vector<int>(S));
	
	for(int s=0; s<S; ++s){
		int position; cin >> position;
		for(int a=0; a<A; ++a){
			T[a][s] = distmap[a][position]; //shortest distance from a to shelter position
		}
	}
	
	
	// Binary search for the smallest t.
    int low = 0, high = INT_MAX;
    while (low < high) {
		int mid = low + (high-low)/2;
		Graph GG(A + S*C);
		
		//build the graph
		for(int s=0; s<S; ++s){
			for(int a=0; a<A; ++a){
				if(T[a][s] == INT_MAX) continue;
				
				for(int c=0; c<C; ++c){
					if(T[a][s] + (c+1) * D <=mid){ //path plus capacity * enter time
						add_edge(a, A + s + c * S, GG); // A + s number agents are vertices 0 - (A-1). A+s are vertices of shelters. and plus S for second entry in shelter
					}
				}
			}
		}

		vector<Vertex> matemap(A + S*C);		// We MUST use this vector as an Exterior Property Map: Vertex -> Mate in the matching
		edmonds_maximum_cardinality_matching(GG, make_iterator_property_map(matemap.begin(), get(vertex_index, GG)));
		
		//count number of matched agents
		const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();
        int matching_size = 0;
        for (int a=0; a<A; ++a) {
			matching_size += (matemap[a] != NULL_VERTEX);
        }
        if(matching_size == A){
			//we have a full matching and can try smaller graph
			high = mid;
		}else{
			low = mid+1;
		}
	}
	
	cout << low << endl;	
		
}	
	
	
// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int t;	cin >> t;
	while(t--)	do_testcases();
	return 0;
}
