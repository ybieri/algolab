// Includes
// ========
// STL includes
#include <iostream>
#include <bits/stdc++.h>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


// Functions
// ========= 
void testcases() {
	
	int V, E;
	cin >> V >> E;
	
	// Create Graph, Vertices and Edges
	// ================================
	Graph G(V);	
	WeightMap weightmap = boost::get(boost::edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38
	
	//create weighter graph
	REP(i,E) {
		Edge e;	bool success;
		int u, v, w;
		cin >> u >> v >> w;
		tie(e, success) = add_edge(u, v, G);	// Adds edge from u to v. If parallel edges are allowed, success is always true.
		weightmap[e] = w;			// Otherwise it is false in case of failure when the edge is a duplicate
		assert(boost::source(e, G) == u && boost::target(e, G) == v);	// This shows how to get the vertices of an edge
	}

	Vertex start = 0;

	// Prim minimum spanning tree
	// ==========================
	std::vector<Vertex> primpredmap(V);	// We MUST use this vector as an Exterior Property Map: Vertex -> Prim Predecessor
	boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(primpredmap.begin(), boost::get(boost::vertex_index, G)));	// Prim from *vertices(G).first (usually 0)
	boost::prim_minimum_spanning_tree(G, boost::make_iterator_property_map(primpredmap.begin(), boost::get(boost::vertex_index, G)),	// Prim from user-defined start,
			boost::root_vertex(start));									// old primpredmap gets reset first!	
	int totalweight = 0;
	for (int i = 0; i < V; ++i) {
		if (primpredmap[i] != i) {
			Edge e; bool success;
			boost::tie(e, success) = boost::edge(i, primpredmap[i], G);
			totalweight += weightmap[e];
		}
	}
	
	// Dijkstra shortest paths
	// =======================
	std::vector<Vertex> predmap(V);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	std::vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	boost::dijkstra_shortest_paths(G, start, // We MUST provide at least one of the two maps
		boost::predecessor_map(boost::make_iterator_property_map(predmap.begin(), boost::get(boost::vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(boost::make_iterator_property_map(distmap.begin(), boost::get(boost::vertex_index, G))));	// distance map as Named Parameter
	int maxdist = 0;
	Vertex furthest = start;
	int reachable = 0;
	for (int i = 0; i < V; ++i) {
		if (distmap[i] < INT_MAX) {	// check whether vertex i is reachable, i.e. has "finite" distance from the start
			++reachable;		// INT_MAX comes from climits and the type of distmap (vector<int>).
			if (distmap[i] > maxdist) {
				maxdist = distmap[i];
				furthest = i;
			}
		}
	}

	cout << totalweight << " " << maxdist << endl;
	
}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); 
	int T;	cin >> T;
	while(T--)	testcases();
	return 0;
}
