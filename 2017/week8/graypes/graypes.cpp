#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;

using namespace std;
using namespace CGAL;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

double ceil_to_double(const EK::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


void do_testcases(int n){

	vector<Point> points(n);	
	for(int i=0; i<n; ++i){
		Point P;
		cin >> points[i];
	}
	// construct triangulation
	Triangulation t;
	t.insert(points.begin(), points.end());
	// output all edges	
	
	K::FT min_squared_distance = std::numeric_limits<K::FT>::max();
	
	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
		min_squared_distance = std::min(min_squared_distance, t.segment(*e).squared_length());
	}
	
	EK::FT time = 50 * CGAL::sqrt(EK::FT(min_squared_distance));
	
	cout << ceil_to_double(time) << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	for(int n; cin >> n && n > 0;) do_testcases(n); 
}
