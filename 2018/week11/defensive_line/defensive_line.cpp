//includes STD
#include <iostream>
#include <bits/stdc++.h>
//namespaces
using namespace std;
//defines
#define REP(i,n) for(int i=0; i<(int)n; ++i)
//typedefs
typedef vector<int> vi;
typedef vector<vi> vvi;

void do_testcases(){
	int D, A, k; cin >> D >> A >> k;
	
	//read in defensive values
	vi def(D);
	REP(i,D){
		cin >> def[i];
	}
	
	//build defensive sums for sliding windows
	vi sum(D);
	REP(i,D){
		if(i==0) sum[i] == def[i];
		else sum[i] = sum[i-1] + def[i];
	}
	
	//at position i we have an interval ending of length x
	vi blocks(D,0);
	
	//sliding window
	int l = 0; int r = 0;
	while(l < D && r < D){
		int power = sum[r] - sum[l] + def[l]; // l-1 but would give index problems so  we just add the defence again
		if(power == k){
			blocks[r] = r-l+1;
			++l; ++r;
		}else if(power > k){
			++l;
		} else {
			++r;
		}
	}
	
	//dynamic programming to find best selection
	//either attack interval and take the value there and continue with 1 attacker less
	//or not attack but continue with same attackers
	vvi DP(D+1, vi(A+1, 0));
	for(int d=1; d <=D; ++d){
		for(int a=1; a<=A; ++a){
			//new value = max of not taken, took block d-1, so we are d-1 defenders further and have 1 attacker less but gained blocks[d-1]
			DP[d][a] = std::max(DP[d-1][a], DP[d-blocks[d-1]][a-1] + blocks[d-1]); //either we comve from before and didn't take it or we come from one less and did take it
		}
	}
	
	if(DP[D][A] != DP[D][A-1]){ //could use every attacker otherwise it would be the same and the attacker would not make a difference
		cout << DP[D][A] << endl;
	} else {
		cout << "fail" << endl;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
