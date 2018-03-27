
// example: decide whether there exists a disk that covers a given set
// of points R in the plane and is disjoint from another set of points B
#include <iostream>
#include <bits/stdc++.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
// choose exact integral type
typedef CGAL::Gmpq ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef vector<P> pi;
typedef vector<int> vi;


void do_testcases(){
	
	int A, S, B;
	cin >> A >> S >> B;
	
	int E; cin >> E;
	
	pi asteroids(A);
	vi densities(A);
	REP(i,A){
		cin >> asteroids[i];
		cin >> densities[i];
	}
	
	pi shooting(S);
	REP(i,S){
		cin >> shooting[i];
	}
	
	pi bounty(B);
	REP(i,B){
		cin >> bounty[i];
	}
	
	Program lp (CGAL::LARGER, true, 0, false, 0);
	
	Triangulation t;
	t.insert(bounty.begin(), bounty.end());

	vector<double> distToHunter(S, INT_MAX);
	//get distance to closest bouny hunter for each shooting point
	REP(i,S){
		if(B > 0){//we have hunters
			P nearest = t.nearest_vertex(shooting[i])->point();
			double sqrd = CGAL::squared_distance(nearest, shooting[i]);
			distToHunter[i] = sqrd;
		}
		lp.set_c(i, 1); //1*e_i
	}

	//for each asteroid check if it is in range of shooting point
	REP(i,A){
		REP(j,S){
			K::FT sqrd = CGAL::squared_distance(asteroids[i], shooting[j]);
			if(sqrd < distToHunter[j]){ //asteroid closer than closest hunter
				sqrd = std::max(1.0, sqrd);
				double rr = 1.0/sqrd;
				lp.set_a(j, i, rr);
			}
		}
		lp.set_b(i, densities[i]); //set densitiy per asteroid line
	}
	
	
	Solution s = CGAL::solve_linear_program(lp, ET());
	
	if(s.is_infeasible() || s.objective_value() > E){
		cout << "n" << endl;
	}else{
		cout<< "y" << endl;
	}

}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
