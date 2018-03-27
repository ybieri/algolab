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
	
	int n, c, f; cin >> n >> c >> f; //students, characteristics, min_common characteristics
	
	
	//set of characteristics per student
	vector< set<string> > characteristics(n);
	
	// for each student
	REP(i,n){
		set<string> charset;
		charset.clear();
		//c characteristics per student
		REP(j,c){
			string chara; cin >> chara;
			charset.insert(chara);
		}
		characteristics[i] = charset;
	}
	

	Graph G(n);
	
	REP(i,n){
		for(int j=i+1; j<n; ++j){
			vector<string> is;
			set_intersection(	ALL(characteristics[i]),
								ALL(characteristics[j]),
								back_inserter(is));
            if(is.size() > f){
				Edge e;	bool success;
				tie(e, success) = add_edge(i, j, G);
			}
		}
	}

	
		// Edmonds' maximum cardinality matching
	// =====================================
	vector<Vertex> matemap(n);		// We MUST use this vector as an Exterior Property Map: Vertex -> Mate in the matching
	edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(matemap.begin(), get(vertex_index, G)));
	
	int matchingsize = matching_size(G, boost::make_iterator_property_map(matemap.begin(), get(vertex_index, G)));
	
	
	if(matchingsize == n/2){
		cout << "not optimal" << endl;
	} else {
		cout << "optimal" << endl;
	}

}

// Main function looping over the testcases
int main() {
	std::ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int T;	cin >> T;
	while(T--)	testcases();
	return 0;
}
