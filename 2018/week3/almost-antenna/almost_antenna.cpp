#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(x)  cerr << #x << " = " << (x) << endl;


// typedefs
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef K::Point_2 P;


double floor_to_double(const K::FT& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

double ceil_to_double(const K::FT& x){
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void do_testcases(int n){
	vector<P> citizens;
	
	REP(i,n){
		long x, y;
		cin >> x >> y; 
		citizens.push_back(P(x,y));		
	}
	
	Min_circle mc(ALL(citizens), true);
	
	K::FT min_distance = (mc.circle().squared_radius());	

	
	//for all support points we check if removing it results in smaller circle
	for (auto it = mc.support_points_begin(); it < mc.support_points_end(); ++it) {
	 	vector<P> almost = citizens;
		for(auto i = almost.begin(); i < almost.end(); ++i){
			if(*it == *i){
				almost.erase(i);			
			}
		}
		Min_circle almost_mc(ALL(almost), true);
		min_distance = std::min(min_distance, (almost_mc.circle().squared_radius()));
	}
	
	cout << ceil_to_double(sqrt(min_distance)) << endl;

}



int main(){
	ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
	
	for(int n; cin >> n && n > 0;) do_testcases(n);
	return 0;	
}
