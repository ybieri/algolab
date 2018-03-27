// example: decide whether there exists a disk that covers a given set
// of points R in the plane and is disjoint from another set of points B
#include <iostream>
#include <bits/stdc++.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;
using namespace boost;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

// choose exact integral type
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;

// round up to next integer double
double floor_to_double(const SolT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int getSizeOfDifference(vector<P> s1, vector<P> s2){
    vector<P> p(s1.size() + s2.size());
    vector<P> p2(s1.size() + s2.size());
    auto it = set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), p.begin());
    auto it2 = set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), p2.begin());
    return (it2 - p2.begin()) - (it - p.begin());
}


void do_testcases(){
	int warehouse, stadium, c; cin >> warehouse >> stadium >> c;
	
	//lower bound 0
	Program lp (CGAL::SMALLER, true, 0, false, 0);
 
	vector<P> objects(warehouse + stadium);

	//per stadium get max supply and alcool % of beer
	//have n*m variables. each stadium n has m warehouses 
	

	// (1) sum of supplies of pure alcohol per stadium <= max total pure alcohol per stadium
	// (2) sum of supplies for stadium = demand of stadium

	//stadium constraints for alcohol
	//stadium constraints for demand
	//warehouse constraints for max supply


	REP(w, warehouse){
		cin >> objects[w];
		int sup, alc; cin >> sup >> alc;
		REP(s, stadium){
			lp.set_a(w*stadium + s, s, 			alc); // (1) alcohol percentage
			lp.set_a(w*stadium + s, s+stadium, 	1); // (2) 1x this amount 
		}
		lp.set_r(2 * stadium + w, CGAL::SMALLER); //smaller than total suplly of this warehouse
		lp.set_b(2 * stadium + w, sup);
	}
 
	REP(s, stadium){
		int demand,upper;
		cin >> objects[warehouse + s];
		cin >> demand >> upper;
		lp.set_r(s, CGAL::SMALLER);
		lp.set_b(s, upper*100);
		lp.set_r(stadium + s, CGAL::EQUAL);
		lp.set_b(stadium + s, demand);
		//set x_{w,s} for outgoing supply
		REP(w, warehouse){
			lp.set_a(w*stadium + s, 2*stadium + w, 1); // max supply x_{w,s}
		}
	}
	
	vector<vector<int>> revenues(warehouse, vector<int>(stadium));
	
	REP(w,warehouse){
		REP(s,stadium){
			cin >> revenues[w][s];
		}
	}
	
	Triangulation t;
	t.insert(objects.begin(),objects.end());
	
	// center, radius 
	vector<pair<P,int>> c_lines;
	REP(i,c){
		int x,y,r;
		cin >> x >> y >> r;
		P pt(x,y);
		//cline closest to stadium or warehouse
		auto nearest = t.nearest_vertex(pt);
		//if a stadium or warehouse is inside the contour line we add it
		if(r*r >= squared_distance(nearest->point(), pt)){
			c_lines.push_back(make_pair(pt, r*r));
		}
	}
	
	//compute in which contour line each stadium, warehouse is
	//holst all contour lines warehouse/stadium is inside
	vector<vector<P>> circles(stadium + warehouse);
	REP(i, warehouse+stadium){
		for(auto it = c_lines.begin(); it!=c_lines.end(); ++ it){
			if(CGAL::squared_distance(objects[i], it->first) <= it->second){ //if sqdist(point to center) <= radius its inside
				circles[i].push_back(it->first);
			}
		}
		sort(circles[i].begin(), circles[i].end());
	}
	
	REP(w, warehouse){
		REP(s, stadium){
			int r = revenues[w][s] * 100;
			int intersections = getSizeOfDifference(circles[w], circles[warehouse + s]); //basically you could also for every countour line check if s and w are in it, if not add 1 to s,w counter
			r-=intersections;
			lp.set_c(w*warehouse+s, ET((-1) * r));
		}
	}
	
	// solve the program, using ET as the exact type
    Solution s = CGAL::solve_nonnegative_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    // output solution
    if(s.is_infeasible())
        std::cout << "RIOT!\n";
    else {
        double res = floor_to_double(((-1) * s.objective_value()) / 100);
        std::cout << std::setprecision(15) << res << std::endl;
    }
	
}
int main(){
    
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) do_testcases();
    return 0;
}
