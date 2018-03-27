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
	
	int V, E, s, start, end;
	cin >> V >> E >> s >> start >> end;
	
	vector<Graph> GG;
	vector<WeightMap> weightmaps; // = boost::get(boost::edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38
	
	
	REP(i,s){
		Graph G(V); GG.push_back(G);
		WeightMap weightmap = get(edge_weight, G);
		weightmaps.push_back(weightmap);
	}
	
	REP(i,E){
		int u, v; cin >> u >> v;
		//read all weights
		REP(j,s){
			int w; cin >> w;
			Edge e;	bool success;
			tie(e, success) = add_edge(u, v, GG[j]);
			weightmaps[j][e] = w;
		}
	}
	
	//read and forget. MST can be formed easier without needing it
	REP(i,s){
		int hive; cin >> hive;
	}
	
	Graph G(V);
	WeightMap wm;
	
	//creaste MST for each species
	REP(i,s){
		// Kruskal minimum spanning tree
		// =============================
		vector<Edge>	mst; 
		kruskal_minimum_spanning_tree(GG[i], back_inserter(mst));		
		
		for (auto it = mst.begin(); it != mst.end(); ++it) {
			Edge e; bool success;
			//add edges of mst to final graph G
			tie(e, success) = add_edge(source(*it, GG[i]), target(*it, GG[i]), G);
			wm[e] = weightmaps[i][*it];
		}		
	}
	
	
	// Dijkstra shortest paths
	// =======================
	vector<Vertex> predmap(V);	
	vector<int> distmap(V);		
	dijkstra_shortest_paths(G, start, 
		boost::predecessor_map(boost::make_iterator_property_map(predmap.begin(), boost::get(boost::vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(boost::make_iterator_property_map(distmap.begin(), boost::get(boost::vertex_index, G))));	// distance map as Named Parameter
	
	cout << distmap[end] << endl;

}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	cin >>  T;
	while(T--)	testcases();
	return 0;
}

