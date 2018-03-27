
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include <limits>

//typedefs
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 S;
typedef K::Point_2 P;
typedef std::result_of<K::Intersect_2(K::Ray_2,S)>::type IT;




using namespace std;


inline S read_segment() {
   long x1, y1, x2, y2;
   cin >> x1 >> y1 >> x2 >> y2;
   return S(P(x1,y1), P(x2,y2));
}


// clip/set target of s:segment of ray to o:intersection
void shorten_segment(S& s, const IT& o) {
  if (const P* p = boost::get<P>(&*o)){
     s = S(s.source(), *p);
   }else if (const S* t = boost::get<S>(&*o)){
// select endpoint of *t closer to s.source()
     if (CGAL::collinear_are_ordered_along_line(s.source(), t->source(), t->target()))
       s = S(s.source(), t->source());
     else
       s = S(s.source(), t->target());
   }else{
     throw std::runtime_error("Strange segment intersection.");
	}
 }


double floor_to_double(const K::FT& x){
  double a = floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void find_hit(std::size_t n) {

// read input
   K::Ray_2 r;
   cin >> r;
   vector<S> segs;
   segs.reserve(n);
   for (size_t i = 0; i < n; ++i) segs.push_back(read_segment());
   random_shuffle(segs.begin(), segs.end());


// clip the ray at each segment hit (cuts down on the number of
// intersection points to be constructed: for a uniformly random
// order of segments, the expected number of constructions is
// logarithmic in the number of segments that intersect the initial
// ray.)

   S rc(r.source(), r.source());


// find some segment hit by r
   size_t i = 0;
   for (; i < n; ++i)
     if (CGAL::do_intersect(segs[i], r)) {
       shorten_segment(rc, CGAL::intersection(segs[i], r));
       break;
     }
   if (i == n) { std::cout << "no\n"; return; }

// check remaining segments against rc
   while (++i < n)
     if (CGAL::do_intersect(segs[i], rc))
       shorten_segment(rc, CGAL::intersection(segs[i], r));// not rc!

   std::cout << floor_to_double(rc.target().x()) << " "
             << floor_to_double(rc.target().y()) << "\n";
}





int main(){
	if (numeric_limits<long>::digits < 51)
		throw runtime_error("long has <51 bits mantissa");
	ios_base::sync_with_stdio(false);
	cout << setiosflags(ios::fixed) << setprecision(0);
	for (size_t n; cin >> n && n > 0;)
		find_hit(n);

	return 0;
}
