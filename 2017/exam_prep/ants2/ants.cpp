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

#define REP(i,n) for(int i=0; i<(int)n; ++i)


// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices	
		property<edge_index_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


// Functions
// ========= 
void do_testcases(){
	
	int V, E, s, a, b;
	cin >> V >> E >> s >> a >> b;
	
	Graph G(s);
	property_map<Graph, edge_index_t>::type edgeindex = get(edge_index, G);
	vector<vector<int> > weights(s, vector<int>(e,-1))
	REP(i, E){
		Edge e;	bool success;
		int u, v; cin >> u >> v;
		tie(e, success) = add_edge(u, v, G);
		
		REP(j,s){
			cin >> weights[j][i];
		}
	}
	// ignore hives
	REP(i,s){
		int x; cin >> x;
	}

	vector<int> mstweight(E, INT_MAX);
	REP(i, s){
		vector<Edge>	mst; 
		kruskal_minimum_spanning_tree(G, back_inserter(mst),
				weight_map(make_iterator_property_map(weights[i].begin(), edgeindex)));			

		totalweight = 0;
		// go through the minimum spanning tree with an iterator
		vector<Edge>::iterator	mstbeg, mstend = mst.end();
		for (mstbeg = mst.begin(); mstbeg != mstend; ++mstbeg) {
			if(weights[i][edgeindex[*mstbeg] < mstweight[edgeindex[*mstbeg]]){
				 mstweight[edgeindex[*mstbeg]] = weights[i][edgeindex[*mstbeg];
			}
		}
	
	}
	
	vector<Vertex> predecessors(num_vertices(graph));
    vector<int> distances(num_vertices(graph));
	dijkstra_shortest_paths(G, a, predecessor_map(&predecessors[0]).distance_map(&distances[0]).
		weight_map(make_iterator_property_map(&spanning_tree_weights[0], indices)));
	cout << distances[b] << endl;
	
}

// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int t; cin >> t;
	while(t--)	do_testcases();
	return 0;
}

