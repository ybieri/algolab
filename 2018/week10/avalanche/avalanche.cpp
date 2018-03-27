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
// Namespaces
using namespace std;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef adjacency_list<vecS, vecS, undirectedS, no_property> GGraph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

typedef vector<int> vi;
typedef vector<vi> vvi;

// Functions
// =========
// Function for an individual testcase
void testcases() {
	int N, M, A, S, C, D;
	cin >> N >> M >> A >> S >> C >> D;
	
	Graph G(N);
	WeightMap weightmap = get(edge_weight, G);
	
	REP(i,M){
		char w; int x,y,z;
		cin >> w >> x >> y >> z;
		Edge e;	bool success;
		tie(e, success) = add_edge(x, y, G);
		weightmap[e] = z;
		
		if(w == 'L'){ //ski Lift is bidirectional
			tie(e, success) = add_edge(y, x, G);
			weightmap[e] = z;
		}
	}
	
	//compute distances to each vertex per agent
	vvi distmap(A, vi(N));
	REP(a,A){
		int i; cin >> i; //agent position
		dijkstra_shortest_paths(G, i, distance_map(make_iterator_property_map(distmap[a].begin(), get(vertex_index, G))));	
	}
	
	//matrix distance agents to shelters
	vvi T(A, vi(S));
	REP(s,S){
		int j; cin >> j; //shelter position
		REP(a,A){
			T[a][s] = distmap[a][j];
		}
	}
	
	//binary search to find smallest time s.t. all can escape
	int l = 0;
	int r = INT_MAX;
	
	//creating graph, adding edges from a-s that are smaller than our current limit r, finding maximum cardinality matching
	while(l <= r){
		int m = l+(r-l)/2;
		GGraph GG(A + S*C); //double shelter vertex to possibly add second person
		
		REP(a,A){ //for each agent
			REP(s,S){ //for each shelter
				if(T[a][s] == INT_MAX) continue; //not reachable, thus INT_MAX in dijkstra
				REP(c,C){
					if(T[a][s] + (c+1)*D <= m){ //c+1 so we have 1 and 2, D being the time before we can enter
						add_edge(a, A + c * S + s, GG);
					}
				}
			}
		}
		
		//max cardinality matching
		vector<Vertex> matemap(A + C*S);		
		edmonds_maximum_cardinality_matching(GG, make_iterator_property_map(matemap.begin(), get(vertex_index, GG)));
		
		// Using the matemap 
		// =================
		const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();	// unmatched vertices get the NULL_VERTEX as mate.
		int matchingsize = matching_size(GG, make_iterator_property_map(matemap.begin(), get(vertex_index, GG)));

		if(matchingsize == A){ //all still make it
			r = m-1;
		}else{ //some die
			l = m+1;
		}		
	}
	cout << l << endl;

}

// Main function to loop over the testcases
int main() {
	std::ios_base::sync_with_stdio(false);
	int T;	cin >> T;
	for (; T > 0; --T)	testcases();
	return 0;
}
