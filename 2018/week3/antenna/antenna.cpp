#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <CGAL/number_utils.h>
#include <cmath>
using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define DEBUG(x) ;// cerr << #x << " = " << (x) << endl;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K; 
typedef K::Point_2 P;
typedef Min_circle_2_traits_2<K>  Traits;
typedef Min_circle_2<Traits>      Min_circle;
typedef vector<int> vi;
typedef vector<vi> vvi;


double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}


double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


void do_testcases(int n){
	
	vector<P> citizens(n);
	REP(i,n){
		double x,y;
		cin >> x >> y;
		citizens[i] = P(x,y);		
	}
	
	Min_circle mc(citizens.begin(), citizens.end(), true);
	
	cout << ceil_to_double(sqrt(mc.circle().squared_radius())) << endl;
}




int main(){
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(0);
	for(int t; cin >> t && t > 0;) do_testcases(t);
	return 0;	
}
