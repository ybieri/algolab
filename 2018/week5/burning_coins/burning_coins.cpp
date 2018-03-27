#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

typedef vector<int> vi;
typedef vector<vi> vvi;

int f(vvi& matrix, vi&coins, int i, int j){
	
	//arrived at last coin. take it
	if(i == j){
		return coins[i];
	}
	
	//already computed the value. return it
	if(matrix[i][j] > 0){
		return matrix[i][j];
	}
	
	//2 coins left, take maximum
	if(j-i == 1){
		int best = max(coins[i], coins[j]);
		matrix[i][j] = best;
		return matrix[i][j];
	}
	// enemy took last coins. we get 0 more
	if(i > j){
		return 0;
	}
	
	matrix[i][j] = max(
					coins[i] + min(f(matrix, coins, i+2, j),f(matrix, coins, i+1, j-1)),
					coins[j] + min(f(matrix, coins, i+1, j-1),f(matrix, coins, i, j-2))
	);
	
	return matrix[i][j];
}



void do_testcases(){
	int n; cin >> n;
	
	// read in coins
	vi coins(n);
	REP(i,n){
		cin >> coins[i];
	}
	
	//dp table. 2 dimensional, for 2 values, right, left aka i,j. 
	//-1 if not defined
	vvi matrix(n, vi(n, -1));
	
	cout << f(matrix, coins, 0, n-1) << endl;
	
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
