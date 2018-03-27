#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); ++i)
#define DEBUG(x) cerr << #x << " = " << (x) << endl;
#define mp(i,j) make_pair(i, j)

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;


void do_testcases(){
	int n; cin >> n;
	
	vector<ii> boats(n); // position, length

	REP(i,n){
		int l,p;
		cin >> l >> p;
		boats[i] = mp(p,l);
	}
	sort(ALL(boats));
	
	
	int right = INT_MIN;
	int old_right = INT_MIN;
	int counter = 0;
	
	REP(i,n){
		int p = boats[i].first;
		int l = boats[i].second;
		if(p >= right){ //we take it
			++counter;
			old_right = right;
			right = max(p, right+l);
		} else { // check if we replace
			int possible_new_right = max(p, old_right+l);
			if(possible_new_right <= right){
				right = possible_new_right;
			}
		}
	}
	cout << counter << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
