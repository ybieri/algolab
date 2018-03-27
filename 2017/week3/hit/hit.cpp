#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>

//do tyepdefs
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

using namespace std;

void does_hit(size_t n){
	//read in ray
	R ray;
	cin >> ray;
		
	bool flag = true;
	bool printno = true;
	//for every segment. compare to ray. if intsersect stop
	for(size_t i=0; i<n; ++i){
		long long x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		//cout <<"segment " << x1 << " " << y1 <<" "<< x2 <<" "<< y2<<endl;
		
		if(flag){
			//cout << "flagtrue" << endl;
			if(CGAL::do_intersect(ray, S(P(x1,y1),P(x2,y2)))){
				cout << "yes" << endl;
				flag = false;
			} 
			 
		}
	}
	// none intersected, output no
	if(flag)
		cout << "no" << endl;
	return;
}


int main(){
	ios_base::sync_with_stdio(false);
	
	for(size_t n; cin >> n && n>0;){
		//cout <<"n " <<n<<endl;
		does_hit(n);
	}

	return 0;
}
