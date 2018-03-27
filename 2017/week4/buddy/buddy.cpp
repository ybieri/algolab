// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <set>
#include <string>
#include <iterator>
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
typedef adjacency_list<vecS, vecS, undirectedS>     Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	




void do_testcases(){
	int num_students, num_characteristics, optimum;
	cin >> num_students >> num_characteristics >> optimum;
	
	map<int, set<string> > student_characteristics;
	Graph G(num_students);
	
	for(int i=0; i<num_students; ++i){
		set<string> characteristics_set;

		for(int j=0; j < num_characteristics; ++j){
			string charac; cin >> charac;
			characteristics_set.insert(charac);
		}
		student_characteristics[i] = characteristics_set;
	}
	
	//intersect every two student sets.
	//check size. if large enough add edge in graph
	for(int i=0; i < num_students; ++i){
		for(int j=i+1; j < num_students; ++j){
			vector<string> intersection;
			intersection.clear();
			set_intersection(student_characteristics.at(i).begin(), student_characteristics.at(i).end(), 
							 student_characteristics.at(j).begin(), student_characteristics.at(j).end(),
							 back_inserter(intersection)
							 );
			if(intersection.size() > optimum){
				bool success;
				Edge e;
				tie(e, success) = add_edge(i, j, G);
			}
		}
	}
	
	vector<Vertex> mate(num_students);
	
	bool success = checked_edmonds_maximum_cardinality_matching(G, make_iterator_property_map(mate.begin(), get(vertex_index, G)));
	int matchingsize = matching_size(G, make_iterator_property_map(mate.begin(), get(vertex_index, G)));
	
	
	if(matchingsize == num_students/2){
		cout << "not optimal" << endl;
	} else {
		cout << "optimal" << endl;
	}
	
}



int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
