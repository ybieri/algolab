#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define ALL(x) begin(x), end(x)
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++) 
#define DBG(vari) ;//cerr<<#vari<<" = "<<(vari)<<endl;

typedef vector<int> vi;
typedef vector<vi> vvi;

void do_testcases(){
	int n; cin >> n;

	int m, h;
	m=0;
	REP(i,n){
		cin >> h;
		if (m >=i){
			m = max(m, i+h-1);
		}
	
	}
	cout << min(m+1, n) << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
}
