#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

// choose exact floating-point type
typedef CGAL::Gmpzf ET;

// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
using namespace std;

void do_testcases(int n){
	int m; cin >> m; //n:#assets, m:#friends
	Program qp(CGAL::SMALLER, true, 0, false, 0);
	
	for(int i=0; i<n; ++i){
		int c, r;
		cin >> c >> r;
		qp.set_a(i, 0, c);
		qp.set_a(i, 1, r);
	}
	vector<vector<int> > covar(n, vector<int>(n));
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			cin >> covar[i][j];
			if(j<=i)
				qp.set_d(i, j,  2*covar[i][j]);
		}
	}

	qp.set_r(0, CGAL::SMALLER); 
	qp.set_r(1, CGAL::LARGER); 
	
	for(int pers =0; pers<m; ++pers){
		int c, v;
		cin >> c >> v;
		// 1:cost
		// 2:return
		qp.set_b(0, c);

		int lmin = 0; int lmax = 40 * 1000000; //40 assets. max 1 mio return per asset
		int best_res = INT_MIN;
		while(lmin  != lmax){
			int	middle = lmin + (lmax-lmin)/2;
			qp.set_b(1, middle);
			Solution s = CGAL::solve_quadratic_program(qp, ET());
						
			if(s.is_optimal() && s.objective_value() <= v){				
				lmin = middle + 1;
				best_res = std::max(best_res, middle);
			}else{
				lmax = middle;
			}
		}

	cout <<  best_res << endl;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(0);
	for(int n; cin >> n && n>0;) do_testcases(n);
  return 0;
}

