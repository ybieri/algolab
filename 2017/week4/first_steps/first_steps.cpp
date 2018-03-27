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

typedef adjacency_list<vecS, vecS, undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,								// interior properties of vertices	
		property<edge_weight_t, int> 	     		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef graph_traits<Graph>::edge_iterator			EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t



void do_testcases(){
	int V, E; cin >> V >> E;
	
	Graph G(V);
	WeightMap weightmap = get(edge_weight, G);
	vector<vector<int> > graphedges(E);
	
	// read in edges. construct graph
	for(int i=0; i<E; ++i){
		int u,v,w;
		cin >> u >> v >> w;
		graphedges[i] = {u,v,w};
	}
	
	for (int i = 0; i < E; ++i) {
		Edge e;	bool success;
		Vertex u = graphedges[i][0];
		Vertex v = graphedges[i][1];
		int    w = graphedges[i][2];
		tie(e, success) = add_edge(u, v, G);	// Adds edge from u to v. If parallel edges are allowed, success is always true.
												// Caveat: if u or v don't exist in G, G is automatically extended!
		weightmap[e] = w;						// Otherwise it is false in case of failure when the edge is a duplicate
		assert(source(e, G) == u && target(e, G) == v);	// This shows how to get the vertices of an edge
	}
	
	// Kruskal minimum spanning tree
	// =============================
	vector<Edge>	mst; 											// We must use this vector to store the MST edges (not as a property map!)
																	// We can use the following vectors as Exterior Property Maps if we want to access additional information computed by Union-Find:	
	vector<Vertex>	kruskalpredmap(V);								// Stores predecessors needed for Union-Find (NOT the MST!)
	vector<int>	rankmap(V);											// Stores ranks needed for Union-Find
	kruskal_minimum_spanning_tree(G, back_inserter(mst),			// kruskal_minimum_spanning_tree(G, back_inserter(mst)); would be fine as well 
			rank_map(make_iterator_property_map(rankmap.begin(), get(vertex_index, G))).
			predecessor_map(make_iterator_property_map(kruskalpredmap.begin(), get(vertex_index, G))));			
	
	//cout << "Kruskal builds a minimum spanning tree of total weight: ";
	int totalweight = 0;
	// go through the minimum spanning tree with an iterator
	vector<Edge>::iterator	mstbeg, mstend = mst.end();
	for (mstbeg = mst.begin(); mstbeg != mstend; ++mstbeg) {
		totalweight += weightmap[*mstbeg];		
	}
	


	// Dijkstra shortest paths
	// =======================
	vector<Vertex> predmap(V);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	Vertex start = 0;
	dijkstra_shortest_paths(G, start, // We MUST provide at least one of the two maps
		predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	// distance map as Named Parameter
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
	cout << totalweight << " " << maxdist << endl;;

}




int main(){
	int t; cin >> t;
	while(t--) do_testcases();
	return 0; 
}
