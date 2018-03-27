#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<int(n); ++i)
#define FOR(i,x,n) for(int i=x; i<int(n); ++i)
#define ALL(x) (x).begin(), (x).end()
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++) 
#define DEBUG(x) cerr << #x << " = " << (x) << endl;


typedef vector<int> vi;
typedef vector<vi> vvi;


void do_testcases(){
	int n,k; cin >> n >> k;
	
	vi v(n);
	
	REP(i,n){
		cin >> v[i];
	}
	
	int start = 0, end = 0; 
	int sum = v[0];
	int best_i = 0, best_j = 0;
	int best = abs(k-v[0]);
	int lastdiff = abs(k-sum);
	int newdiff;
	
	if(best == 0){
		cout << best_i << " " << best_j << endl;
		return;
	}

	while(end < n){
		// we are too large, increase start
		if(sum > k ){
			sum -= v[start];
			++start;
			if(abs(sum-k) < best){
				best = abs(sum-k);
				best_i = start;
				best_j = end;
			}
		} else  if(sum < k ){ // we are too small, increase end
			++end;
			sum += v[end];
			if(abs(k-sum) < best){
				best = abs(k-sum);
				best_i = start;
				best_j = end;
			}
		} else if(sum == k ){ //bingo
			cout << best_i << " " << best_j << endl;
			return;
		}
	}
		
	cout << best_i << " " << best_j << endl;
	
}



int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;	
}
