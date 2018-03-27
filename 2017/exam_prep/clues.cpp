#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::pair<int,bool> info_t;
typedef CGAL::Triangulation_vertex_base_with_info_2<info_t,K> vertex_t;
typedef CGAL::Triangulation_face_base_2<K> face_t;
typedef CGAL::Triangulation_data_structure_2<vertex_t,face_t> triangulation_t;
typedef CGAL::Delaunay_triangulation_2<K,triangulation_t> delaunay_t;
typedef delaunay_t::Vertex_handle vhandle_t;
typedef delaunay_t::Vertex_circulator vcirculator_t;
typedef K::Point_2 Point;

using namespace std;


bool try_two_coloring(delaunay_t& trg, K::FT& rr){
	
	for (auto v = trg.finite_vertices_begin(); v != trg.finite_vertices_end(); ++v)
		v->info() = {0, false}; //component, color
	
	int components = 0;
	delaunay_t trg0, trg1;
	
	for (auto v = trg.finite_vertices_begin(); v != trg.finite_vertices_end(); ++v){
		if(v->info().first == 0){
			v-info().first == ++components;
			vector
		}
		
	}
	
	
	
	
}




void do_testcases(){
	int n, m;
	K::FT r, rr;
	cin >> n >> m >> r;
	rr = r*r;
	
	vector<Point> stations(n);
	for(int i=0; i<n; ++i) 
		cin >> stations[i];
	
	delaunay_t trg;
	trg.insert(stations.begin(), stations.end());
	
	bool success = try_two_coloring(trg, rr);
	
}




int main(){
	ios_base::sync_with_stdio(false:
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}



