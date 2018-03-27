#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <CGAL/number_utils.h>

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef  K::Point_2 					 Point;

typedef  Traits::Circle					 Circle;
using namespace std;
using namespace CGAL;


//global variables
Point capital;

bool compare_cities(Point p1, Point p2){
	return squared_distance(p1, capital) > squared_distance(p2, capital);
}

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void do_testcases(){
	double num_cities; cin >> num_cities;
	//read in the capital
	cin >> capital;
	vector<Point> cities(num_cities-1);
	
	//read in all the points of the other cities
	for(int i=0; i<num_cities-1; ++i){
		cin >> cities[i];
	}
	
	// if maximum of two cities, one antenna each is optimal. radius = 0
	if(num_cities <=2){
		double radius = 0;
		cout << radius << endl;
		return;
	}

	//further city first, nearest last
	sort(cities.begin(), cities.end(), compare_cities);

	//compute distance from capital to all cities
	vector<K::FT> distances(num_cities-1);
	for(int i=0; i<cities.size(); ++i){
		distances[i] = squared_distance(cities[i], capital); //largest distance first
	}

	//define radius1,2 and old radius 1,2
	K::FT r1, r2, or1, or2;
	//minimum circle around antenna 2
	//initially only farthest city
	Min_circle mc(cities.begin(), ++cities.begin(), true);
	
	Circle current_circle;
	r1 = distances[1];
	r2 = 0.0;
	or1 = r1;
	or2 = r2;
	int i = 1;

	
	while(r2 < r1){ //TODO: binary search
		or1 = r1;
		or2 = r2;
		
		//add next city to antenna 2, recompute min circle
		mc.insert(cities[i]);
		
		current_circle = mc.circle();
		r2 = current_circle.squared_radius();
		r1 = distances[i+1];
		++i;	
	}

	K::FT result = min(max(r1,r2), max(or1,or2));
	cout << ceil_to_double(result) << endl;
}

int main(){
	cin.sync_with_stdio(false);
 	cout.sync_with_stdio(false);
 	cout << fixed << setprecision(0);

	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}

