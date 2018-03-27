#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) ; // cerr << #x << " = " << (x) << endl;
#define mp(x,y) make_pair(x,y)
#define ALL(x) (x).begin(), (x).end()

typedef vector<int> vi;
typedef vector<vi> vvi;

int play(int u, bool maximize, const vvi& matrix, vvi& memo){
	int n = matrix.size();
	if(u == n-1) return 0; //moved past last position
	
	if(memo[maximize][u]!= -1) return memo[maximize][u];
	
	int best = maximize ? 0 : n; //maximize will be more than 0, minimize will be less than n
	
	for(auto v : matrix[u]){
		if(maximize) best = std::max(best, 1+play(v, 1-maximize, matrix, memo)); //if we maximze we want as many rounds as possible
		else 		 best = std::min(best, 1+play(v, 1-maximize, matrix, memo));
	}
	memo[maximize][u] = best;
	return best;
}


void do_testcases(){
	int n,m; cin >> n >> m; //#positions, transitions
	int r,b; cin >> r >> b; //starting positions red, black meeple
	--r; --b; //0 indexing
	
	vvi matrix(n, vi());
	REP(i,m){
		int u,v; cin >> u >> v;
		--u; --v; //0 indexing
		matrix[u].push_back(v); //i will have all targets v reachable from u as a matrix
	}
	
	vvi memo(2, vi(n, -1)); //maximize, minimize for all n positions

	int red = play(r, 0, matrix, memo); //holmes moves red first, wants to minimize number of rounds needed.
	int black = play(b, 0, matrix, memo); //moriarty moves black first, wants to minimize number of rounds needed.
	
	if(red < black || (red == black && red%2 == 1)){ 
		cout << 0 << endl;
	} else {
		cout << 1 << endl;
	}
}




int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
