#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;
using namespace CGAL;

struct investor{
	int maxcost;
	int minreturn;
	int maxvariance;
};

struct asset{
	int cost;
	int expectedreturn;
};

double floor_to_double(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void do_testcases(int n) {// num assets
	int m; cin >> m; //num investors

	//populate assets
	vector<asset> assets(n);
	for(int i=0; i<n; ++i){
		cin >> assets[i].cost;
		cin >> assets[i].expectedreturn;
	}
	// populate variance matrix
	vector<vector<int> > covariance(n,vector<int>(n));
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			cin >> covariance[i][j];
		}
	}

	//populate investors
	vector<investor> investors(m);
	for(int i=0; i<m; ++i){
		cin >> investors[i].maxcost;
		cin >> investors[i].minreturn;
		cin >> investors[i].maxvariance;
	}

	// for each investor
	for(int i=0; i<m; ++i){
		Program qp (CGAL::SMALLER, true, 0, false, 0);

		// sum assets
		for(int j=0; j<n; ++j){	
			qp.set_a(j, 0, assets[j].cost);
			qp.set_a(j, 1, assets[j].expectedreturn);
		}

		qp.set_r(0, SMALLER);
		qp.set_r(1, LARGER);
		
		qp.set_b(0, investors[i].maxcost);
		qp.set_b(1, investors[i].minreturn);		

	
		// set objective function
		for(int i=0; i<n; ++i){ 
			for(int j=0; j<=i; ++j){ //i
				qp.set_d(i, j, 2*covariance[i][j]);
			}
		}

		// solve the program, using ET as the exact type
		Solution s = CGAL::solve_quadratic_program(qp, ET());
		assert(s.solves_quadratic_program(qp));

		if(s.is_optimal() && s.objective_value() <= investors[i].maxvariance) cout << "Yes." << endl;
		else cout << "No." << endl;
	}
  
}

int main(){
	ios_base::sync_with_stdio(false);
	cout << setprecision(15);
	for(int n; cin >> n && n > 0;) do_testcases(n);
	return 0;
}
