#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
typedef Triangulation::Edge_iterator  EI;
typedef Triangulation::Vertex_iterator VI;
typedef Triangulation::Vertex_handle VH;
typedef K::Segment_2 S;


double ceil_to_double(const EK::FT& x){
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


double hours(double distance){
	return ceil_to_double(CGAL::sqrt(CGAL::sqrt(EK::FT(distance))-0.5));
}

void do_testcases(int n){
	int l, b, r, t;
	cin >> l >> b >> r >> t;
	
	vector<P> pts(n);
	
	map<P, double> distance;
	REP(i,n){
		int x, y;
		cin >> x >> y;
		P p(x,y);
		pts[i] = p;
		
		int minlr = std::min(x-l, r-x);
		int mintb = std::min(t-y, y-b);
		
		distance[p] = std::min(minlr, mintb);
		distance[p] *= distance[p]; //squared distance
	}
	// construct triangulation
	Triangulation dt;
	dt.insert(pts.begin(), pts.end());
	
	//e->first->vertex(t.cw(e->second);
	//edge is (face, i, j) thus first gets face handle and then we can get vertices +1 and +2 ans 0 is opposite and representing the face
	//alternatively: Segment s = t.segment(e)
	//				 s.point(0), s.point(1)
	
	// output all edges
	for (Edge_iterator e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e){
		S s = dt.segment(e);
		P p0 = s.point(0);
		P p1 = s.point(1);
		
		//we have r^2 to walls and here (2r)^2 = 4r^2 thus divide by 4
		double dist = CGAL::to_double(CGAL::squared_distance(p0, p1))/4;
		distance[p0] = std::min(distance[p0], dist);
		distance[p1] = std::min(distance[p1], dist);
	}
	
	//now sort all distances and we are good to go:
	vector<double> d;
	for(auto x : distance){
		d.push_back(x.second);
	}
	
	sort(ALL(d));
	
	//n/2 works because: if n is odd (3) then n/2 = 1 so the second element. when the second element dies, we are below 50%
	cout << hours(d[0]) << " " << hours(d[n/2]) << " " << hours(d[n-1]) << endl;;
}


int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed << setprecision(0);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
}
