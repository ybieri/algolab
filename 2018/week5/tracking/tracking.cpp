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
#define DEBUG(x) cerr << #x << " = " << (x) << endl;

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
	
	int V, E, k, start, end;
	cin >> V >> E >> k >> start >> end;
	
	//we make an additional full graph for each river we have to cross and put the end node in the last graph.
	//traversal to next "leve" over river paths (back and forth)
	//start point in first graph, end point in last graph
	Graph G(V*(k+1));	
	WeightMap weightmap = get(edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38
	

	REP(i,E){
		int u, v, w, d;
		cin >> u >> v >> w >> d;
		Edge e;	bool success;
		if(d==0){
			REP(j,k+1){
				tie(e, success) = add_edge((j*V)+u, (j*V)+v, G);	
				weightmap[e] = w;
			}	
		}else if(d==1){
			REP(j,k){//k-1 because we cannot go further from last level
				tie(e, success) = add_edge((j*V)+u, ((j+1)*V)+v, G);
				weightmap[e] = w;
				tie(e, success) = add_edge((j*V)+v, ((j+1)*V)+u, G);	
				weightmap[e] = w;
			}
			//add edge normally for last "level"
			tie(e, success) = add_edge(k*V+u, k*V+v, G);	
			weightmap[e] = w;
		}
	}


	// Dijkstra shortest paths
	// =======================
	vector<int> distmap(V*(k+1));
	dijkstra_shortest_paths(G, start,
		distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	
	
	cout << distmap[(k*V)+end] << endl;
	

}

// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	cin >> T;
	while(T--)	testcases();
	return 0;
}
