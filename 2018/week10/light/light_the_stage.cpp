#include <iostream>
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) ; //cerr << #x << " = " << (x) << endl;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
typedef K::Segment_2 S;

struct participant{
	P p;
	int r;
};


void do_testcases(){
	int n, m; cin >> m >> n;
	
	//get participants
	vector<participant> participants(m);
	REP(i,m){
		cin >> participants[i].p;
		cin >> participants[i].r;	
	}
	//lamp height/radius
	int h; cin >> h;
	
	//get lamps
	vector<P> lamps(n);
	REP(i,n){
		cin >> lamps[i];
	}
	
	DEBUG(m) DEBUG(n)

	vector<int> solution;

	Triangulation t;
	t.insert(lamps.begin(), lamps.end());
	
	bool won = false;
	
	vector<pair<int,int>> eliminatedby(m);
	
	//for each participant check if  he is hit by closest lamp 
	REP(i,m){
		DEBUG(i)
		P nearest_lamp = t.nearest_vertex(participants[i].p)->point();
		K::FT dist = squared_distance(nearest_lamp, participants[i].p);
		K::FT lrpr = h + participants[i].r; //lamp radius person  radius
		lrpr *= lrpr;
		
		//if radius + lamp is smaller equal nearets point, we don't get eliminated
		if(dist >= lrpr){
			solution.push_back(i);
			won = true;
		} else { //if all get hit we need to find who gets hit last
			if(won) continue;
			//for all lamps we check if we get hit, keep first index
			REP(j,n){
				DEBUG(j)
				dist = squared_distance(participants[i].p, lamps[j]);
				if(dist < lrpr){//we are too close to current lamp, we get eliminated
					eliminatedby[i] = make_pair(j, i); //pair contains lamp index and person index
					break;
				}
			}
		}
	}
	
	
	//all get eliminated, find largest index
	if(solution.size() == 0){
		std::sort(eliminatedby.begin(), eliminatedby.end(), std::greater<pair<int,int>>());
		int index = eliminatedby[0].first;
		DEBUG(index)
		REP(i,m){
			if(eliminatedby[i].first == index){
				solution.push_back(eliminatedby[i].second);
			}else{
				break;
			}
		}
	}
	
	sort(solution.begin(), solution.end());
	
	for(auto x : solution){
		cout << x << " ";
	}

	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
