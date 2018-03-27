
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}


void do_testcases(int n){
	R ray; cin >> ray;
	vector<S> segments(n);
	REP(i,n){
		long x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		segments[i] = S(P(x1,y1),P(x2,y2));		
	}
	// so we can use a random algorithm for clipping
	random_shuffle(ALL(segments));
	
	S clipped(ray.source(), ray.source());
	
	int i = 0;
	for(; i<n; ++i){
		if(do_intersect(segments[i], ray)){
			auto o = CGAL::intersection(segments[i], ray);
			if (const P* op = boost::get<P>(&*o)){
				clipped = S(clipped.source(), *op);
			}else if (const S* os = boost::get<S>(&*o)){
				if(collinear_are_ordered_along_line(clipped.source(), os->source(), os->target())){
					clipped = S(clipped.source(), os->source());
				}else{
					clipped = S(clipped.source(), os->target());
				}
			}
			break;
		}
	}
 
	if(i == n){
		cout << "no" << endl;
		return;
	}
 
	while(++i < n){
		if(do_intersect(segments[i], clipped)){
			auto o = CGAL::intersection(segments[i], ray);
			if (const P* op = boost::get<P>(&*o)){
				clipped = S(clipped.source(), *op);
			}else if (const S* os = boost::get<S>(&*o)){
				if(collinear_are_ordered_along_line(clipped.source(), os->source(), os->target())){
					clipped = S(clipped.source(), os->source());
				}else{
					clipped = S(clipped.source(), os->target());
				}
			}
		}
	}
	
	cout << floor_to_double(clipped.target().x()) << " " << floor_to_double(clipped.target().y()) << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	cout << setiosflags(ios::fixed) << setprecision(0);
	for(int n; cin >> n && n>0;) do_testcases(n);
	return 0;
	
}
