#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Edge_iterator  EI;
typedef Triangulation::Vertex_iterator VI;
typedef Triangulation::Vertex_handle VH;

using namespace std;
using namespace CGAL;


EK::FT hours(const EK::FT& distance){
	return CGAL::sqrt(CGAL::sqrt(distance)-0.5);
}

double ceil_to_double(const EK::FT& x){
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


void do_testcases(int n){
	int l, b, r, t;
	cin >> l >> b >> r >> t;
	
	vector<P> points(n);
	for(int i=0; i<n; ++i){
		cin >> points[i];
	}
	
	Triangulation tr;
	tr.insert(points.begin(), points.end());
	
	map<P, double> distances;
	
	for(VI v = tr.finite_vertices_begin(); v != tr.finite_vertices_end(); ++v){
		P point = v->point();
		double minlr = std::min(point.x()-l, r-point.x());
		double mintb = std::min(point.y()-b, t-point.y());
		distances[point] = std::min(minlr, mintb);
		distances[point] *=distances[point]; //we use squared distances
	}
	
	for(EI e = tr.finite_edges_begin(); e != tr.finite_edges_end(); ++e){
		VH v1 = e->first->vertex(tr.cw(e->second));
		VH v2 = e->first->vertex(tr.ccw(e->second));
		P p1 = v1->point();
		P p2 = v2->point();
		
		double distance = CGAL::to_double(CGAL::squared_distance(p1, p2))/4; //distance = 2*border distance. squared thus /4.
		distances[p1] = std::min(distances[p1], distance);
		distances[p2] = std::min(distances[p2], distance);
	}
	
	
	vector<double> ds;
	ds.reserve(n);
	for(auto it=distances.begin(); it!=distances.end(); ++it){
		ds.push_back(it->second);
	}
	
	sort(ds.begin(), ds.end());
	
	EK::FT first = hours(EK::FT(ds[0]));
	EK::FT median = hours(EK::FT(ds[n/2]));
	EK::FT last = hours(EK::FT(ds[n-1]));

	cout << ceil_to_double(first) << " " << ceil_to_double(median) << " " << ceil_to_double(last) << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
}
