#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) ;// cerr << #x << " = " << (x) << endl;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
typedef Triangulation::Face_handle FH;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef K::Segment_2 	Segment;

bool dfs(FH& face, map<FH, int>& visited, Triangulation& t, int roundnumber, double d){
	visited[face] = roundnumber;

	DEBUG(roundnumber) 
	//we got out, return true
	if(t.is_infinite(face))	{
		return true;
	}
	
	//for all 3 neighboring faces
	REP(i,3){
		DEBUG(i)
		
		Segment s = t.segment(face, i);
		double dist = CGAL::to_double(s.squared_length());
		DEBUG(dist)
		
		if(dist >= 4*d){
			FH nextface = face->neighbor(i);

			DEBUG(t.is_infinite(nextface))

			if(t.is_infinite(nextface)){
				 return true;
			}
			
			//already been there
			if(visited[nextface] == roundnumber){
				continue;
			}
							
			if(dfs(nextface, visited, t, roundnumber, d)){
				 return true;
			}
		}
	}
	return false;
	
}




void do_testcases(int n){

	vector<P> pts(n);
	REP(i,n){
		cin >> pts[i];
	}
	// construct triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());
	// output all edges
	
	//visited faces for dfs. initialize to -1
	map<FH, int> visited;
	for(Face_iterator f = t.finite_faces_begin(); f!=t.finite_faces_end(); ++f){
		visited[f] = -1;
	}


	int m; cin >> m;
	REP(i,m){
		P point; cin >> point;
		double d; cin >> d;
		
		P nearest = t.nearest_vertex(point)->point();
		
		//are already to close to start with
		if(CGAL::to_double(CGAL::squared_distance(point, nearest)) < d){
			DEBUG("init too close")
			cout << "n";
			continue;
		}
		//start face. 
		FH startface = t.locate(point);
		
		if(t.is_infinite(startface) || dfs(startface, visited, t, i, d)){
			cout << "y";
		}else{
			cout << "n";
		}
	}
	//new testcase on new line
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	for(int n; cin >> n && n > 0;) do_testcases(n);
	return 0;
}
