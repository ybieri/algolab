#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

void do_testcases(){
	int N; cin >> N;
	//read in coins
	vvi coins(N, vi(N, 0));
	REP(i,N){
		REP(j,N){
			cin >> coins[i][j];
		}
	}
	
	//2N-1 diag, N x1 pos, N x2 pos
	vvvi dp(2*N-1, vvi(N, vi(N,0)));
	dp[0][0][0] = coins[0][0];
	
	//all diagonals to middle
	FOR(d,1,N){
		REP(x1,d+1){//for diag 1 x can be 0 or 1. thus d+1 because for is strictly less <
			REP(x2,d+1){
				int y1 = d-x1;
				int y2 = d-x2;
				int c = coins[x1][y1];
				if(x1 != x2) c += coins[x2][y2]; //cannot have it twice
				
				int  v = dp[d-1][x1][x2]; //down down
				if(x1) v = max(v, dp[d-1][x1-1][x2]);// x1 larger than 0, right, down
				if(x2) v = max(v, dp[d-1][x1][x2-1]); // x2 larger than 0, down right
				if(x1 && x2) v = max(v, dp[d-1][x1-1][x2-1]);//both larger than 0, right, right
				
				dp[d][x1][x2] = v+c; //max of last plus current coins
			}
		}
	}
	
	FOR(d,N,2*N-1){ //past middle until end
		FOR(x1,d+1-N,N){ //d is N too high right now
			FOR(x2,d+1-N,N){
				int y1 = d-x1;
				int y2 = d-x2;
				int c = coins[x1][y1];
				if(x1 != x2) c += coins[x2][y2]; //cannot have it twice
				
				int    v = dp[d-1][x1-1][x2-1];  //right, right. on this diagonal there is for sure something on the left
				v = max(v, dp[d-1][x1-1][x2]); //right, down
				v = max(v, dp[d-1][x1][x2-1]); //down right
				v = max(v, dp[d-1][x1][x2]); //right, right
				
				dp[d][x1][x2] = v+c; //max of last plus current coins
			}
		}
	}
	// diagns 0 to 2*N-2, x1 0 to N-1, x2 0 to N-1
	// print last field
	cout << dp[2*N-2][N-1][N-1] << endl;
	
}



int main(){
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
