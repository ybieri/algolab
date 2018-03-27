#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;


#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) x.begin(), x.end()


double ceil_to_double(const EK::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}



int main(){
	ios_base::sync_with_stdio(false);
	while(true){
		int n; cin >> n;
		if(n==0) return 0;
		
		vector<P> pts(n);
		REP(i,n){
			cin >> pts[i];
		}

		// construct triangulation
		Triangulation t;
		t.insert(ALL(pts));
		// output all edges
		K::FT min_dist = numeric_limits<K::FT>::max(); 
		
		for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
			min_dist = std::min(min_dist, t.segment(*e).squared_length());
		}
		
		//100/2 100th of second, but 2 run
		EK::FT dist = 50 * CGAL::sqrt((min_dist));

		std::cout << ceil_to_double(dist) << endl;
	}
}
