#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose exact integral type
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void do_testcases(int n){
	// by default, we have a nonnegative LP with Ax <= b
	int d;
	cin >> d;
	Program lp(CGAL::SMALLER, false, 0, false, 0);
	
	for(int i=0; i<n; ++i){
		double norm2 = 0;
		int ai;
		for(int j=0; j<d; ++j){
			cin >> ai;
			norm2 += ai*ai;
			lp.set_a(j, i, ai); //ai*j0 + ai*j1 etc
		}	
		double norm = std::floor(std::sqrt(norm2));
		  if (norm2 != norm*norm)
			 throw std::domain_error("Warning: norm2!= norm*norm.\n");

		lp.set_a(d, i, norm); //d is the index of radius. r*norm
		int bi;
		std::cin >> bi;       
		lp.set_b(i, bi);
    }                        
	lp.set_c(d, -1); //minimize -r
	lp.set_l(d, true, 0); //lower bound on r: 0
	
   // solve the program, using ET as the exact type
   Solution s = CGAL::solve_linear_program(lp, ET());
	
	if (s.is_infeasible())
		std::cout << "none\n";
	else if (s.is_unbounded())
		std::cout << "inf\n";
	else {
		ET out = -(s.objective_value().numerator()/s.objective_value().denominator()); //represented as "Bruch". Integer division rounds down to nearest integer
		std::cout << out << std::endl;
	}
}

// Main function to loop over the testcases
int main() {
	ios_base::sync_with_stdio(false);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
}
