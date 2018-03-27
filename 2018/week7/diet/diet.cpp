#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}


int main() {
	ios_base::sync_with_stdio(false);
	while(true){
		
		int n; cin >> n;
		int m; cin >> m;
		if(n==0 && m==0) return 0;
		
		Program lp (CGAL::SMALLER, true, 0, false, 0);
		
		//read in min and max of nutrient
		REP(i,n){
			int _min, _max; cin >> _min >> _max;
			lp.set_b(i, _min);
			lp.set_r(i, CGAL::LARGER);
			lp.set_b(i+n, _max);
		}
		
		//read in price and nutrients per food
		REP(i,m){
			int price; cin >> price;
			lp.set_c(i, price);
			
			REP(j,n){
				int nut; cin >> nut;
				//food i, nutrient j, set to value nut
				lp.set_a(i, j, nut);
				lp.set_a(i, j+n, nut);
			}
		}
	
	
		// solve the program, using ET as the exact type
		Solution s = CGAL::solve_quadratic_program(lp, ET());
		assert(s.solves_quadratic_program(lp));
		
		if(!s.is_optimal()) cout << "No such diet." << endl;
		else cout << floor_to_double(s.objective_value()) << endl;
	}
}
