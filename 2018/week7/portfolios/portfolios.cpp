#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

// choose exact rational type
typedef CGAL::Gmpzf ET;
// solution type the solver provides
typedef CGAL::Quotient<ET> SolT;
// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


int main() {
	ios_base::sync_with_stdio(false);
	
	//true, 0 because we cannot buy negative share. lower bound: 0

	while(true){
		int n, m; cin >> n >> m;
		if(n==0 && m==0) return 0;
		
		Program qp (CGAL::LARGER, true, 0, false, 0); 

		//read in cost and expected return
		int c, r;
		REP(i,n){
			cin >> c >> r;
			qp.set_a(i, 0, r); //returns
			qp.set_a(i, 1, c); //costs
		}

		//read in covariance matrix
		int v;
		REP(i,n){
			REP(j,n){
				cin >> v; //v_{i,j}
				if(j<=i)
					qp.set_d(i, j, 2*v);
			}
		}
		
		//solve for each of m persons
		int C, R, V;
		REP(i,m){
			cin >> C >> R >> V;
			
			qp.set_b(0, R);
			qp.set_b(1, C);
			qp.set_r(1, CGAL::SMALLER); //smaller than cost

			//assert(qp.is_nonnegative());
			Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
			//assert(s.solves_quadratic_program(qp));
			
			if(s.is_optimal() && s.objective_value() <= V) cout << "Yes." << endl;
			else cout << "No." << endl;
			
		}
	}
}
