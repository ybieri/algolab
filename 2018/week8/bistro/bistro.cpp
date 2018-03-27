#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;

void do_testcases(int n){
	
	//get bistros/points
	vector<P> pts(n);
	REP(i,n){
		cin >> pts[i];
	}
	
	// construct triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());
	
	int m; cin >> m;
	//for all possible locations
	REP(i,m){
		P point; cin >> point;
		P nearest = t.nearest_vertex(point)->point();
		//output squared distance
		cout << CGAL::squared_distance(point, nearest) << endl;
	}
}


int main(){
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(0);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
}
