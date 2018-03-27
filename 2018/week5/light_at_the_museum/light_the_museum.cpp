#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x);//  cerr << #x << " = " << (x) << endl;
#define mp(x,y) make_pair(x,y)
#define ALL(x) (x).begin(), (x).end()

typedef vector<int> vi;
typedef vector<vi> vvi;

// flip the switches
void flip(int i, vi& lights, const vvi& diff){
	//for each room
	int M = lights.size();

	REP(j,M){
		lights[j] += diff[i][j];
	}
}


void do_testcases(){
	int N, M; //num switches, num rooms
	cin >> N >> M;
	
	//read in target brightness
	vi b(M);
	REP(i,M){
		cin >> b[i];
	}
	
	int best = INT_MAX;
	
	//matrices for on, off diff. diff: value to add if switch is flicked: +off - on
	vvi ON(N, vi(M));
	vvi OFF(N, vi(M));
	vvi DIFF(N, vi(M));
	vi init_light(M, 0);
	// read in NXM matrices
	REP(i,N){
		REP(j,M){
			cin >> ON[i][j] >> OFF[i][j];
			DIFF[i][j] = OFF[i][j] - ON[i][j];
			init_light[j] += ON[i][j];
		}
	}
	
	
	//split and list
	int N1 = N/2;
	int N2 = N - N1;
	
	vector<pair<vector<int>, int >> S2;
	//compute S2. 1 << N2 = 2^N2
	//for each combination
	REP(i,(1 << N2)){	
		//need to store #flip, #num lights on
		int counter = 0;
		//for each switch in the second half:
		vi lights(init_light);
		REP(j, N2){
			if(i & (1 << j)){ // if j-th switch is choosen 
				flip(j+N1, lights, DIFF);
				++counter;
			}
		}
		DEBUG(counter)
		//adding lights on in room with needed amount of flips
		S2.push_back(mp(lights, counter));
	}
	
	//for fast binary search afterwards
	sort(ALL(S2));
	//add vectors of S2 separate from 
	vvi S2_veconly;
	for(auto p : S2){
		S2_veconly.push_back(p.first);
	}
	
	//part2
	REP(i, (1<<N1)){
		int counter = 0;
		//for each switch check if it was choosen
		vi lights(M, 0);
		REP(j, N1){
			if(i & (1 << j)){ // if j-th switch is choosen 
				flip(j, lights, DIFF);
				++counter;
			}
		}
		
		//see if we found a result
		//each room  has to have at least b[j] lights on
		vi remaining(M);
		REP(j,M){
			//lights per room that need to be added (subtracted)
			remaining.at(j) = b.at(j) - lights.at(j);
		}
		
		bool success = std::binary_search(ALL(S2_veconly), remaining);
		
		if(success){
			//get counter of that value
			auto it = lower_bound(ALL(S2_veconly), remaining);
			int index = it - S2_veconly.begin();
			best = min(best, counter + S2[index].second);
		}		
	}
	
	if(best == INT_MAX){
		cout << "impossible" << endl;
	} else {
		cout << best << endl;
	}
	
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
