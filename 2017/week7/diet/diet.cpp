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

struct nutritient{
	int min;
	int max;
};

struct food{
	int price;
	vector<int> nutritients;
};

double floor_to_double(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void do_testcases(int n) {
  // by default, we have an LP with Ax <= b and no bounds for
  // the four variables alpha, beta, gamma, delta
	Program lp (CGAL::SMALLER, true, 0, false, 0);
	int m; cin >> m;
	
	vector<nutritient> nus(n);
	for(int i=0; i<n; ++i){
		cin >> nus[i].min;
		cin >> nus[i].max;
	}
	vector<food> foods(m);
	
	for(int i=0; i<m; ++i){
		cin >> foods[i].price;
		for(int j=0; j<n; ++j){
			int x;
			cin >> x;
			foods[i].nutritients.push_back(x);
		}
	}
	
	for(int i=0; i<m; ++i){
		lp.set_c(i, foods[i].price);
	}
	for(int i=0; i<n; ++i){ // for each nutrition
		lp.set_r(i, LARGER);
		lp.set_b(i, nus[i].min);
		
		// first m foods min, second m foods max
		lp.set_r(i+n, SMALLER);
		lp.set_b(i+n, nus[i].max);
		
		// per nutrition, sum up all foods
		for(int j=0; j<m; ++j){
			lp.set_a(j, i,  foods[j].nutritients[i]);
			lp.set_a(j, m+i,foods[j].nutritients[i]);
		}
	}

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(lp, ET());
	assert(s.solves_quadratic_program(lp));
	
	if(!s.is_optimal()) cout << "No such diet." << endl;
	else cout << floor_to_double(s.objective_value()) << endl;
  
}

int main(){
	ios_base::sync_with_stdio(false);
	cout << setprecision(15);
	for(int n; cin >> n && n > 0;) do_testcases(n);
	return 0;
}
