#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define DEBUG(x) ;// cerr << #x << " = " << (x) << endl;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef vector<int> vi;
typedef vector<vi> vvi;




bool contains(vector<P>& pts, P& p){
	return !right_turn(pts[0], pts[1], p) && !right_turn(pts[2], pts[3], p) && !right_turn(pts[4], pts[5], p);	
}


void do_testcases(){
	int m, n; cin >> m >> n;
	
	vector<P> path(m);
	REP(i,m){
		cin >> path[i];
	}
	
	vvi triangles(n);
	REP(i,n){
		vector<P> points;
		REP(j,6){
			P point; cin >> point;
			points.push_back(point); // contains the 6 points that describe the triangle
		}
		
		//need correct ordering
		REP(i,3){
			if(right_turn(points[2*i], points[2*i+1], points[(2*i+2)%6])){
				swap(points[2*i], points[2*i+1]);
			}
		}
		
		bool prev = contains(points, path[0]);
		FOR(j,1,m){
			if(contains(points, path[j])){
				if(prev){ //point before in triangle and this point in tirange -> path in triangle
					triangles[i].push_back(j-1); //triangles[j] contains a list of all starting points for which it covers the path
				} else { // this point will be prev for the next iteration
					prev = true;
				}
			} else {
				prev = false;
			}
		}
	}
		
	vi covered(m-1,0); //all m-1 legs are initally covered by 0 triangles
	int uncovered = m-1; //initally all m-1 legs are uncovered
	int best = n; //know that buying all is a cover
	
	int start, end; 
	start = 0; end = 0;
	
	while(end < n){
		//add all paths that are covered by this segment
		REP(i, triangles[end].size()){
			if(++covered[triangles[end][i]] == 1){
				--uncovered;
			}
		}
		
		DEBUG(start) DEBUG(end) DEBUG(uncovered)
		
		if(uncovered == 0){
			best = std::min(best, end-start+1); DEBUG(best)
		}
		
		//if all paths are covered we increase start
		while(uncovered == 0 && start != end){
			//remove 1 from all triangles covered by start
			REP(i, triangles[start].size()){
				if(--covered[triangles[start][i]] == 0){
					++uncovered;
				}
			}
			++start;
			DEBUG(start) DEBUG(end) DEBUG(uncovered)

			if(uncovered == 0){
				best = std::min(best, end-start+1); DEBUG(best)
			}
		}
		++end;
	}
	
	cout << best << endl;

}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;	
}
