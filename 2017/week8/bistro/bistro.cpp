#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;
using namespace std;
using namespace CGAL;

void do_testcases(int n){
	// read points
	vector<P> bistros;
	bistros.reserve(n);
	for (int i = 0; i < n; ++i){
		P p; cin >> p;
		bistros.push_back(p);
	}
	Triangulation t;
	t.insert(bistros.begin(), bistros.end());
	int m; cin >> m;
	for (int i = 0; i < m; ++i){
		P p; cin >> p;
		P nearest = t.nearest_vertex(p)->point();
		cout << CGAL::to_double(CGAL::squared_distance(p, nearest)) << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(0);
	for(int n; cin >> n && n > 0;) do_testcases(n);
	return 0;
}
