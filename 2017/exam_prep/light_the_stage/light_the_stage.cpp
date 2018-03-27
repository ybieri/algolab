#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;
using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) //cout << #x << " = " << x << endl


struct pala{ //participants/lamps
	Point mid; int r;
};


void do_testcases(){
	int num_p, num_l;
	cin >> num_p >> num_l;
	
	vector<Point> part_center(num_p);
	vector<int> part_radius(num_p);
	REP(i, num_p){
		Point p; cin >> p;
		part_center[i] = p;
		cin >>	part_radius[i];
	}	
	vector<Point> lamp_center(num_l);
	int lamp_radius; cin >> lamp_radius;

	REP(i, num_l){
		cin >>	lamp_center[i];
	}
	int l=0; int r=num_l;
	vector<int> solution;
	vector<int> candidates(num_p);
	REP(i, num_p)
		candidates[i] = i;

	while(l <= r) {
		int m = l+(r-l)/2;
		DEBUG(l); DEBUG(r);
		solution.clear();
		Triangulation t;
		t.insert(lamp_center.begin(), lamp_center.begin() + m);

		REP(i, candidates.size()){
			Point closest_lamp = t.nearest_vertex(part_center[candidates[i]])->point();
			K::FT sqdr = CGAL::squared_distance(closest_lamp, part_center[candidates[i]]); //squared distance to nearest delaunay
			K::FT lrpr = lamp_radius + part_radius[candidates[i]]; //lamp radius person radius
			K::FT lrpr2 = lrpr*lrpr;
			if(sqdr >= lrpr2){
				DEBUG(i);
				solution.push_back(candidates[i]);
			}
		}

		if(solution.size() == 0){
			r = m;
		}else{// some are certainly dead. all in solution are possible candidates			
			l = m+1;
			candidates.clear();
			REP(i, solution.size()){
				DEBUG(solution[i]);
				candidates.push_back(solution[i]);
			}
		}	
		
		if(solution.size() > 0 && m == num_l) //have solution and went through all
			break;
	}

	sort(solution.begin(), solution.end());
	REP(i, solution.size())
		cout << solution[i] << " ";
	cout << endl;
	
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}

	//~ REP(i, num_p){
		//~ Point closest_lamp = t.nearest_vertex(part_center[i])->point();
		//~ K::FT sqdr = CGAL::squared_distance(closest_lamp, part_center[i]); //squared distance to nearest delaunay
		//~ K::FT lrpr = lamp_radius + part_radius[i]; //lamp radius person radius
		//~ K::FT lrpr2 = lrpr*lrpr;
		//~ if(sqdr >= lrpr2){
			//~ solution.push_back(i);
		//~ }
	//~ }
