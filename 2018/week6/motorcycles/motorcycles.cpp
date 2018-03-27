#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <stdexcept>
#include <bits/stdc++.h>
#include <CGAL/Quotient.h>

#######
#80/100
#######

using namespace std;
using namespace CGAL;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)

#define ALL(x) (x).begin(), (x).end()

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;

//  K::FT d = CGAL::squared_distance(r,l);


struct biker_t{
	K::FT y0;
	K::FT x1;
	K::FT y1;
	int index;
	Quotient<K::FT> steep;
	bool continuing = true;
};


bool comp(const biker_t &a, biker_t& b){
	return to_double(a.y0) < to_double(b.y0);
}

bool compsteep(const biker_t &a, biker_t& b){
	return to_double(a.steep) >= to_double(b.steep);
}


void do_testcases(){
	int n; cin >> n;
	//read in all the bikers
	vector<biker_t> bikers;
	REP(i,n){
		biker_t biker;
		cin >> biker.y0 >> biker.x1 >> biker.y1;
		CGAL::Quotient<K::FT> q(biker.y1-biker.y0, biker.x1);
		biker.steep = q;
		biker.index = i;
		bikers.push_back(biker);
	}
	
	
	
	
	//sort according to y0
	sort(ALL(bikers), comp);
	
	//for all bikers check if he drives to infinity
	
	vector<biker_t> candidates;
	candidates.push_back(bikers[0]);
	
	FOR(i,1,n){
		while(true){
			//no current candidate, add ourselfes
			if(candidates.empty()){
				candidates.push_back(bikers[i]);
				break;
			}
			//candidate exists, check if steepness is bigger
			if((bikers[i]).steep >=  (candidates.back()).steep){
				candidates.push_back(bikers[i]);
				break;
			}
			//if absolute value of steepness is larger or equal: the right one (old) continues
			if(CGAL::abs(bikers[i].steep) >= CGAL::abs((candidates.back()).steep)){
				break;
			}else{//new steepness is smaller thus old will fall out of race
				candidates.pop_back();
			}
		}
	}
	
	vector<int> out;
	REP(i, candidates.size()){
		out.push_back((candidates[i]).index);
	}
	
	sort(ALL(out));
	
	REP(i, out.size()){
		cout << out[i] << " ";
	}
	cout << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
