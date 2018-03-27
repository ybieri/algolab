#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define mp(x,y) make_pair(x,y)

typedef vector<pair<int,int>> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;

void do_testcases(){
	int n, k; cin >> n >> k;
	
	vi c(n); vi v(n); //cost and volume per drink
	int maxVol = 0;
	REP(i,n){
		cin >> c[i] >> v[i];
		maxVol = std::max(maxVol, v[i]);
	}

	//no people coming haha
	if(k==0){
		cout << 0 << " " << 0 << endl;
		return;
	}
	maxVol += k; //worst case is we have maxVol and buy largest drink
	
	// cost[0][3] : cost if we use drink0 for the remaining 3 liters
	vvii dp(n, vii(maxVol));
	
	dp[0][0] = mp(0,0);
	
	FOR(i,1,maxVol){
		int ntimes = (i+v[0]-1)/v[0]; //basically i/v[0] but with round up
		dp[0][i] = mp(c[0]*ntimes, 1); //ntimes drink times cost, only using 0th drink
	}
	
	//for all other drinks
	FOR(i,1,n){
		dp[i][0] = dp[i-1][0];
		
		FOR(j,1,maxVol){ //can we reduce cost if we replace previous beverage with ours?
			auto take_none = dp[i-1][j];
			int mincost, maxdrink;
			
			if(j < v[i]){//one would be enough to finish, take it, we have 1 drink
				mincost = c[i];
				maxdrink = 1;
			} else { // needed volume - taken volume. are we botter in cost or #drinks?
				auto take_one = dp[i][j-v[i]]; //took one, so we are at needed j - v[i]
				mincost = take_one.first + c[i]; //cost there plus drink costs
				maxdrink = take_one.second + (dp[i-1][j-v[i]] == dp[i][j-v[i]] ? 1 : 0 ); //if  its the same as the previous we didn't take ours yet so we add it
				//if they are different it means ours has improved to there somewher and we have already take ours there
			}
			
			if(mincost > take_none.first){ //cheaper to keep old beverage
				mincost = take_none.first;
				maxdrink = take_none.second;
			}else if(mincost == take_none.first){ //if same cost we take more drink
				maxdrink = std::max(maxdrink, take_none.second);
			}
			dp[i][j] = mp(mincost, maxdrink);	
		}
	}
	
	cout << dp[n-1][k].first << " " << dp[n-1][k].second << endl;
}




int main(){
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
