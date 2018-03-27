#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>

#define REP(i,n) for(int i=0; i<(int)n; ++i)

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

using namespace std;
using namespace CGAL;

void do_testcases(int n){
	R ray; cin >> ray;
	bool flag = true;
	
	REP(i,n){
		long long x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		if(flag){
			if(do_intersect(ray, S(P(x1, y1),P(x2, y2)))){
				cout << "yes" << endl;
				flag = false;
			} 	
		}
	}
	if(flag){
		cout << "no" <<  endl;
	}
}


int main(){
	ios_base::sync_with_stdio(false);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
}
