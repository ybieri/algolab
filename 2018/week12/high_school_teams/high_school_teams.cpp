#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define mp(x,y) make_pair(x,y)
typedef long long ll;

void do_testcases(){
	int n, k; cin >> n >> k;
	vector<ll> skills(n);
	REP(i,n){
		cin >> skills[i];
	}
	
	int N1 = n/2; int N2 = n-N1;
	map<pair<pair<ll,ll>,ll>,ll> pairs; // map(team1, team2, #selected) -> count
	
	for(int i=0; i < 1<<N1; ++i){//for all possibilities in N1 (2^N1)
		vector<ll> selected;
		REP(j, N1){
			// if jth person was chosen, get his skill
			if(i & 1 << j){
				selected.push_back(skills[j]);
			}
		}
		int ssize = selected.size(); //how many selected
		for(int j=0; j< 1 << ssize; ++j){ //all possibilities among the selected
			ll team1 = 0; ll team2 = 0;
			REP(k,ssize){
				//all selected into team 1, others into team 2
				if(j & 1<<k){
					team1 += selected[k];
				}else{
					team2 += selected[k];
				}
			}
			auto team = mp(mp(team1, team2), ssize);
			//add that combination to possible pairs
			//maps don't have default value so we need this ugly construct
			if(pairs.find(team) == pairs.end()){
				pairs[team] = 1;
			}else{
				++pairs[team];
			}
		}
	}
	
	
	map<ll, vector<pair<ll,ll>>> finalMap;
	for(auto it = pairs.begin(); it != pairs.end(); ++it){
		//finalMap[team1-team2] -> vector of mp(#selected, count)
		finalMap[it->first.first.first - it->first.first.second].push_back(mp(it->first.second, it->second));
	}
	ll counter = 0;
	for(int i=0; i< 1<<N2; ++i){
		vector<ll> selected;
		REP(j,N2){
			if(i & 1 << j){
				selected.push_back(skills[j+N1]);
			}
		}
		
		int ssize = selected.size();
		for(int j=0; j< 1 << ssize; ++j){
			ll team1 = 0; ll team2 = 0;
			REP(k,ssize){
				if(j & 1<<k){
					team1 += selected[k];
				}else{
					team2+=selected[k];
				}
			}
			//if we have two times the same difference we found a pair. larger element of one set with smaller element of other set is equal to the other two. always.
			auto team = team2-team1;
			
			//exists something in first half with same difference
			if(finalMap.find(team) != finalMap.end()){
				auto vec = finalMap[team];
				for(auto it = vec.begin(); it != vec.end(); ++it){
					if(ssize + it->first >= n-k){ //together at least n-k were selected
						counter += it->second; // we add number of such pairs that existed to counter (pairs had same difference with equal number of people used)
					}
				}
			}
		}	
	}
	cout << setprecision(17) << counter << endl;
	
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
