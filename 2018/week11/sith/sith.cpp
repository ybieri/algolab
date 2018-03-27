// Includes
// ========
// STL includes
#include <iostream>
#include <bits/stdc++.h>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

// BGL Graph definitions
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor	Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges

//CGAL typedefs
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;


int max_component(map<P, int>& planetindex, vector<P>& planets, K::FT rad, int m, int n){
	Triangulation t;
	t.insert(planets.begin() + m, planets.end());
	
	Graph G(n-m);
	//for all edges in triangulation check if they are shorter than scouting vessel radius
	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
		P u = t.segment(*e).source();
		P v = t.segment(*e).target();
		
		if(CGAL::squared_distance(u, v) <= rad * rad){
			boost::add_edge(planetindex[u]-m, planetindex[v]-m, G); //have to subtract m as we only have n-m vertices
		}
	}
		// Connected components
	// ====================
	int maxcomponent = 0;
	vector<int> componentmap(n-m);	
	int ncc = connected_components(G, make_iterator_property_map(componentmap.begin(), boost::get(boost::vertex_index, G))); 
	vector<int> componentsize(ncc);
	// Iterate over all vertices
	for (int i = 0; i < n-m; ++i)
		++componentsize[componentmap[i]];
	for (int i = 0; i < ncc; ++i)
		maxcomponent = std::max(maxcomponent, componentsize[i]);
	
	return std::min(m, maxcomponent);
}



void do_testcases(){
	int n;
	K::FT rad;
	cin >> n >> rad;
	
	vector<P> planets(n);
	map<P, int> planetindex;
	REP(i,n){
		P p; cin >> p;
		planets[i] = p;
		planetindex[p] = i;
	}
	
	int l = 0; 
	int r = n/2+1; //cannot get more than half +1
	
	while(l != r){
		int m = l + (r-l)/2;
		int res = max_component(planetindex, planets, rad, m , n);
		
		if(m > res){
			r = m;
		}else{
			l = m+1;
		}
	}
	cout << l-1 << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
