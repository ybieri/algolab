#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef K::Point_2 Point;


using namespace std;


void do_testcases(){
	int a, s, b, e;
	cin >> a >> s >> b >> e;
	
	vector<std::pair<Point, int> > asteroids(a);
	for(int i=0; i<a; ++i){
		Point p; cin >> p;
		int density; cin >> density;
		asteroids.at(i) = make_pair(p, density);
	}
	vector<Point> shots(s);
	for(int i=0; i<s; ++i){
		cin >> shots[i];		
	}
	vector<Point> bounty_hunters;
	for(int i=0; i<b; ++i){
		int x, y;
		cin >> x >> y;
		bounty_hunters.push_back(Point(x,y));		
	}
	Program lp(CGAL::LARGER, true, 0, false, 0);
	Triangulation t;
	t.insert(bounty_hunters.begin(), bounty_hunters.end());
	vector<double> closest_bh(s, INT_MAX);
	for(int i=0; i<s; ++i){
		if(b>0){
			Triangulation::Vertex_handle v1 = t.nearest_vertex(shots.at(i));
			closest_bh[i] = CGAL::squared_distance(shots.at(i), v1->point());
		}
		lp.set_c(i, 1);
	}
	for(int i=0; i<a; ++i){
		for(int j=0; j<s; ++j){
			K::FT sqd = CGAL::squared_distance(asteroids.at(i).first, shots.at(j));
			if(sqd < closest_bh[j]){
				if(sqd > 0)
					lp.set_a(j, i, 1/ET(sqd));
				else
					lp.set_a(j, i, 1);
			}
		}
		lp.set_b(i, asteroids.at(i).second);
	}
	
	
	Solution sol = CGAL::solve_linear_program(lp, ET());
	assert(sol.solves_linear_program(lp));
	if (sol.is_infeasible() || sol.objective_value() > e){
		cout << "n" << endl;
	}else{
		cout << "y" << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
