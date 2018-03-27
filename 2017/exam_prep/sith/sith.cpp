#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
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
using namespace std;
using namespace boost;

// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices	
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef graph_traits<Graph>::edge_iterator			EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;


int best(int k, vector<Point>& planets, std::map<Point,int> pI, int n, double rad){

	int remaining = n-k;
	Graph G(remaining);

	Triangulation t;
	t.insert(planets.begin()+k, planets.end());
	for(Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
		Point v1 = e->first->vertex((e->second + 1) % 3)->point();
		Point v2 = e->first->vertex((e->second + 2) % 3)->point();
		double rr = rad*rad;
		if(CGAL::squared_distance(v1, v2) <= rad * rad){
			add_edge(pI[v1]-k, pI[v2]-k, G);
		}
	}
	
	int largestcomp = 0;
	// Connected components
	// ====================
	vector<int> componentmap(remaining);
	int ncc = connected_components(G, make_iterator_property_map(componentmap.begin(), get(vertex_index, G))); 
	vector<int> componentsize(ncc);
	// Iterate over all vertices
	for (int i = 0; i < remaining; ++i)
		++componentsize[componentmap[i]];
	for (int i = 0; i < ncc; ++i)
		largestcomp = std::max(componentsize[i], largestcomp);
	
	return min(k,largestcomp);
}

int binary_search(int l, int r, vector<Point>& planets, std::map<Point, int>& pI, int n, double rad){
	if(l == r)
		return best(l, planets, pI, n, rad);
	if(l+1 == r)
		return std::max(best(l, planets, pI, n, rad), best(r, planets, pI, n, rad));
	
	int m = l+(r-l)/2;
	int midbest = best(m, planets, pI, n, rad);
	if(midbest == m)
		return binary_search(m, r, planets, pI, n, rad);
	else
		return binary_search(l, m, planets, pI, n, rad);

}

void do_testcases(){
	int n;
	double rad;
	cin >> n >> rad;
	vector<Point> planets(n);
	std::map<Point, int> pI;
	for(int i=0; i<n; ++i){
		Point p;
		cin >> p;
		pI[p] =  i;
		planets[i] = p;
	}
	int bst = binary_search(0, n, planets, pI, n, rad);
	cout << bst << endl;
}




int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
