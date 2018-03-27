#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()

typedef vector<int> vi;
typedef vector<vi> vvi;

void do_testcases(){
	int n; cin >> n;
	bool possible = true;;
	vi explosionTime(n);
	
	REP(i,n){
		cin >> explosionTime[i];
	}
	
	REP(i,(n-1)/2){
		if(explosionTime[2*i+2] == explosionTime[i]-2){
			explosionTime[2*i+1] = min(explosionTime[2*i+1], explosionTime[i]-1);
		}else{
			explosionTime[2*i+1] = min(explosionTime[2*i+1], explosionTime[i]-2);
			explosionTime[2*i+2] = min(explosionTime[2*i+2], explosionTime[i]-1);
		}
	}
	sort(ALL(explosionTime));
	
	REP(i,n){
		if(explosionTime[i] < i+1){ //because index starts at 0 and first bomb has to be defused at 1..
			possible = false;
		}
	}
	
	cout << (possible ? "yes" : "no") << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;	
}
