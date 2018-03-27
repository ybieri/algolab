#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <bits/stdc++.h>

using namespace std;

#define DEBUG(x) cerr << #x << " = " << (x) << endl;

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<ET>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

double ceil_to_double(const CGAL::Quotient<ET>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}



void do_testcases() {
	while(true){
		int p; cin >> p;
		if(p == 0) return;
		
		int a, b; cin >> a >> b;
		
		const int X = 0;
		const int Y = 1;
		const int Z = 2;
		
		//first program
		if(p == 1){
			//smaller <=. true 0, false 0 -> lower bound 0, no upper bound
			Program lp (CGAL::SMALLER, true, 0, false, 0);
			lp.set_a(X, 0, 1);  lp.set_a(Y, 0, 1); lp.set_b(0, 4);
			lp.set_a(X, 1, 4);  lp.set_a(Y, 1, 2); lp.set_b(1, a*b);
			lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);
			
			lp.set_c(Y, -b); //-b*y
			lp.set_d(X, X, 2*a); //2a*x^2. if we go quadratic we need 2d	
			
			// solve the program, using ET as the exact type
			Solution s = CGAL::solve_quadratic_program(lp, ET());
			
			if (s.is_unbounded() ) {
				cout << "unbouned" << endl;
			} else if (s.is_infeasible()){
				cout << "no" << endl;
			} else { //negative objective value because we negated everything
				cout << floor_to_double(-s.objective_value()) << endl;
			}
			
			
		}else if(p == 2){ //second program: trick. for z reduce z^2 -> z. z^4 -> z^2
			// larger >=. flase 0 no lower bound, true 0 upper bound 0 
			Program lp (CGAL::LARGER, false, 0, true, 0);
			lp.set_a(X, 0, 1);  lp.set_a(Y, 0, 1); lp.set_b(0, -4);
			lp.set_a(X, 1, 4);  lp.set_a(Y, 1, 2); lp.set_a(Z, 1, 1); lp.set_b(1, -a*b);
			lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, -1);
			
			lp.set_l(Z, true, 0); //lower bound on Z is 0 as it is quadratic
			lp.set_u(Z, false, 0); //remove upper vound of 0 for Z
			
			lp.set_c(Y, b); //b*y
			lp.set_d(X, X, 2*a); //2a*x^2. if we go quadratic we need 2d
			lp.set_d(Z, Z, 2); //z^2. 2 for 2D

	
			// solve the program, using ET as the exact type
			Solution s = CGAL::solve_quadratic_program(lp, ET());
			
			if (s.is_unbounded() ) {
				cout << "unbouned" << endl;
			} else if (s.is_infeasible () ){
				cout << "no" << endl;
			} else {
				cout << ceil_to_double(s.objective_value()) << endl;
			}
		}
	}
	  
}

int main(){
	ios_base::sync_with_stdio(false);
	cout << setprecision(15);
	do_testcases();
	return 0;
}
