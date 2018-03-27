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
#define ALL(x) (x).begin(), (x).end()

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
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
	
	int V, E, q;
	cin >> V >> E >> q;
	
	Graph G(V);
	WeightMap weightmap = get(edge_weight, G);

	REP(i, V){
		long lon,lat; cin >> lon >> lat;
	}
	
	REP(i,E){
		int u,v,w; cin >> u >> v >> w;
		Edge e;	bool success;
		boost::tie(e, success) = boost::add_edge(u, v, G);	// Adds edge from u to v. If parallel edges are allowed, success is always true.
		weightmap[e] = w;			// Otherwise it is false in case of failure when the edge is a duplicate	
	}
	
	REP(i,q){
		int s,t; cin >> s >> t;
		
		vector<int> distmap(V);
		dijkstra_shortest_paths(G, s, distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));

		
		if(distmap[t] < INT_MAX){
			cout << distmap[t] << endl;
		}else {
			cout << "unreachable" << endl;
		}
	}
}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); 
	testcases();
	return 0;
}
