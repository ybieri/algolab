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


void do_testcases(int n){
	int a, b;
	cin >> a >> b;
	const int X = 0;
	const int Y = 1;
	const int Z = 2;
	
	if(n==1){
		Program lp (CGAL::SMALLER, true, 0, false, 0); //lower bound 0
		
		lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);  
		lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);
		lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);

		lp.set_c(Y, -b);                                       
		lp.set_d(X, X, 2*a); 
		                                     
		Solution s = solve_quadratic_program(lp, ET());

		if (s.is_unbounded()) {
		  cout << "unbounded" << endl;
		} else if (s.is_infeasible()){
		  cout << "no" << endl;
		} else {
			cout << floor_to_double(-s.objective_value()) << endl;
		}
	}
	
	if(n==2){
		Program qp (CGAL::LARGER, false, 0, true, 0); 
		
		qp.set_a(X, 0, 1);  qp.set_a(Y, 0, 1); 					  qp.set_b(0, -4);  
		qp.set_a(X, 1,  4); qp.set_a(Y, 1, 2); qp.set_a(Z, 1, 1); qp.set_b(1, -a*b);
		qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1);                    qp.set_b(2, -1);
		 
		qp.set_l(Z, true, 0);   // Lower bound for z: 0
		qp.set_u(Z, false, 0); // No upper bound for z
		
		qp.set_d(X, X, 2*a);
		qp.set_c(Y, b);
		qp.set_d(Z, Z, 2);
		
		Solution s = solve_quadratic_program(qp, ET());

	
		if (s.is_unbounded()) {
		  cout << "unbounded" << endl;
		} else if (s.is_infeasible()){
		  cout << "no" << endl;
		} else {
			cout << ceil_to_double(s.objective_value()) << endl;
		}
		
	}
}


int main(){
	ios_base::sync_with_stdio(false);
	cout << setprecision(15);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
}
