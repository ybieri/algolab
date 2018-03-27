#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Finite_faces_iterator FI;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef Triangulation::Face_handle FH;

using namespace std;
using namespace CGAL;

bool dfs(FH& start_face, map<FH, int>& visited, Triangulation& t, double d, int round){
	visited[start_face] = round;
	if(t.is_infinite(start_face)){
		//cout << "infinite" << endl;
		return true;
	}
	//for all thre neighbouring faces
	for(int i=0; i<3; ++i){
		FH neighbor = start_face->neighbor(i);
		if(visited[neighbor] != round){
			//Triangulation::Segment 
			S seg = t.segment(start_face, i);
			double distance = CGAL::to_double(seg.squared_length());
			//cout << "distance " << distance << " 4d " << 4*d << endl;
			if(distance >= 4*d){
				if(t.is_infinite(neighbor))	return true;

				if(dfs(neighbor, visited, t, d, round))
					return true;
			}
		}
	}
	return false;
}


void do_testcases(int n){
	// read in infected patients
	vector<P> infected(n);
	for (int i=0; i<n; ++i) {
		cin >> infected[i];
	}
	// construct triangulation
	Triangulation t;
	t.insert(infected.begin(), infected.end());
	
	int m; cin >> m;

	map<FH, int> visited;
	for (FI f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f){
		visited[f] = -1;
	}
		
	for(int i=0; i<m; ++i){
		P p; cin >> p;
		double d; cin >> d;
		
		//check if nearest infection is closer than minimum distance. sqrt(d) = r. d = r^2.
		P nearest = t.nearest_vertex(p)->point();
		if(CGAL::squared_distance(nearest, p) < d){
			cout << "n"; continue;
		}
		FH start_face = t.locate(p);
		if(t.is_infinite(start_face) || dfs(start_face, visited, t, d, i)) cout << "y";
		else cout <<"n";
	}
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
}
