#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

using namespace std;


long long ceil_to_double(const K::FT& x)
{
	double a = ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return (long long) a;
}


void find_radius(size_t n){
	
	vector<K::Point_2> P(n);

	for (long i = 0; i < n; ++i){
		long x, y;
		std::cin >> x >> y;
		P[i] = K::Point_2(x,y);
	}
	
	Min_circle mc(P.begin(), P.end(), true);
	Traits::Circle c = mc.circle();
	
	cout << ceil_to_double(sqrt(c.squared_radius())) << std::endl;

}



int main()
{
	ios_base::sync_with_stdio(false);
	for(long long n; cin >> n && n>0;){
		find_radius(n);
	}
}
	

