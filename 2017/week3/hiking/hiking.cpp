#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

//do tyepdefs((
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef std::vector<P> Pts;
typedef std::vector<std::size_t> Covered;
typedef std::vector<Covered> Trs;
typedef Covered::const_iterator CCI;

using namespace std;

//test if line segment is in triangle
//giving two points of triangle side and one point of segment (end, start)
//3rd point for orientation comparison. from other side of triangle

//check if a point is contained
inline bool contains(const Pts& t, const P& p){
	return !CGAL::right_turn(t[0],t[1],p) && !CGAL::right_turn(t[2],t[3],p) && !CGAL::right_turn(t[4],t[5],p);
}



void find_cover(){
	
	//read in segments
	//read in triangle points
	size_t m, n;
	cin >> m >> n;
	
	Pts path;
	path.reserve(m);
	for(size_t i=0; i<m; ++i){
		P p;
		cin >> p;
		path.push_back(p);
	}
	
	Trs triangles(n);
	for(size_t i=0; i<n; ++i){
		Pts t;
		for(size_t j=0; j<6; ++j){
			P p;
			std::cin >> p;
			t.push_back(p);;
		}
		// order triangle: check for each if it is a right turn, if not swap
		for(size_t j=0; j<6; j+=2)
			if(CGAL::right_turn(t[j],t[j+1], t[(j+2)%6])) swap(t[j], t[j+1]);
		//check what paths the triangle contains
		//identify path by startpoint
		bool start = contains(t, path[0]);
		for(size_t j=1; j<m; ++j)
			if(contains(t, path[j])){
				if(start) triangles[i].push_back(j-1); else start = true;
				
			}else 
				start = false;
	}


	// sliding window
	// how often a path is covered by the current rectangles
	Covered covered(m-1,0);
	size_t uncovered = m-1; //number of paths not yet covered
	size_t best = n;
	for(size_t tb=0, te=0; tb != triangles.size();){
		for (; uncovered > 0 && te != triangles.size(); ++te)
			for (CCI j = triangles[te].begin(); j != triangles[te].end(); ++j)
				if (++covered[*j] == 1) --uncovered;
		
		if(uncovered != 0) break;
		//cout << "tb " << tb << " te " << te << " best "  << best << endl;

		do
			for( CCI j = triangles[tb].begin(); j != triangles[tb].end(); ++j)
				if( --covered[*j] == 0) ++uncovered;
		while (++tb != te && uncovered == 0);
		//cout << "tb " << tb << " te " << te << " best "  << best << endl;
		best = std::min(best,te-tb+1);
	}
	cout << best << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; 	
	for (std::cin >> t; t > 0; --t) find_cover();
	return 0;
}
