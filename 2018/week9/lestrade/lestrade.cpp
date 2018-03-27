#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <bits/stdc++.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;




using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) x.begin(), x.end()

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
typedef K::Segment_2 S;


struct gangster{
	int u;
	int v;
	int w;
	bool seen;
};


double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


void do_testcases(){
	
	int Z, U, V, W;
	cin >> Z >> U >> V >> W;
	
	int A, G; cin >> A >> G;
	
	vector<P> gangPos(G);
	map<P, gangster> gangMap;
	REP(i, G){
		P point; cin >> point;
		int u, v, w;
		cin >> u >> v >> w;
		gangster g{u, v, w, false};
		gangMap[point] = g;
		gangPos[i] = point;
	}
	
	// construct triangulation
	Triangulation t;
	t.insert(gangPos.begin(), gangPos.end());
	
	vector<pair<int, P>> agents(A); //wage, closest gangster position
	REP(i,A){
		P point; cin >> point;
		int z; cin >> z;
		
		//get closest gangste
		P closest = t.nearest_vertex(point)->point();
		agents[i] = make_pair(z, closest);
	}
	
	//lowest wage first. So if more agents shadow the same gangster we pick the cheapest
	sort(ALL(agents));
	
	//linear program
	Program lp (CGAL::LARGER, true, 0, true, 24);
	int i = 0;
	for(auto a:agents){
		gangster g = gangMap[a.second];
		if(g.seen){
			continue;
		}else{
			gangMap[a.second].seen = true;
		}
		//create lp:
		
		lp.set_a(i, 0, g.u);
		lp.set_a(i, 1, g.v);
		lp.set_a(i, 2, g.w);
		lp.set_c(i, a.first); //cost
		++i;
	}
	
	lp.set_b(0, U);
	lp.set_b(1, V);
	lp.set_b(2, W);

	// solve the program, using ET as the exact type
	Solution s = CGAL::solve_linear_program(lp, ET());
	assert (s.solves_linear_program(lp));

	if(s.is_optimal()){
		double cost = CGAL::to_double(s.objective_value());
		if(cost <= Z) cout << "L" << endl;
		else cout << "H" << endl;
	}else{
		cout << "H" << endl;
	}
	
}

int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed << setprecision(0);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
