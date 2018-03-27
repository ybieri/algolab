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
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
// Namespaces
using namespace std;
using namespace boost;


// Define custom interior edge property
namespace boost {
	enum edge_component_t { edge_component = 216 };
	// arbitrary, unique id
    BOOST_INSTALL_PROPERTY(edge, component);
}

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()




// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,								// interior properties of vertices	
		property<edge_component_t, int> 			// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef graph_traits<Graph>::edge_iterator			EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_component_t>::type ComponentMap;


// Functions
// ========= 
void testcases() {
	// Create Graph, Vertices and Edges
	// ================================
	
	int V, E;
	cin >> V >> E;
	
	Graph G(V);	// creates an empty graph on n vertices
	
	REP(i,E){
		int u, v; cin >> u >> v;
		Edge e;	bool success;
		tie(e, success) = add_edge(u, v, G);	// Adds edge from u to v. If parallel edges are allowed, success is always true.
		assert(source(e, G) == u && target(e, G) == v);	// This shows how to get the vertices of an edge	
	}

	

	// Biconnected components
	// ====================
	ComponentMap componentmap = get(edge_component, G); 	// We MUST use such a vector as an Exterior Property Map: Vertex -> Component
	int nbcc = biconnected_components(G, componentmap);
	
	vector<int> componentsize(nbcc);
	
	EdgeIt ebeg, eend;
	for (tie(ebeg, eend) = edges(G); ebeg != eend; ++ebeg) {	
		componentsize[componentmap[*ebeg]]++;
	}
	vector<pair<int,int>> important_bridges;

	for (tie(ebeg, eend) = edges(G); ebeg != eend; ++ebeg) {	
		if(componentsize[componentmap[*ebeg]] == 1){
			int u = source(*ebeg, G);
			int v = target(*ebeg, G);
			important_bridges.push_back(make_pair(min(u,v), max(u,v)));
		}
	}
	
	sort(ALL(important_bridges));
	
	cout << important_bridges.size() << endl;
	
	REP(i,important_bridges.size()){
		cout << important_bridges[i].first << " " << important_bridges[i].second << endl;
	}
	
}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	cin >> T;
	while(T--)	testcases();
	return 0;
}
