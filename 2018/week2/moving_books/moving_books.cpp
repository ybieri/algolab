#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(x) cerr << #x << " = " << (x) << endl;
#define make_pair(x,y) mp(x,y)

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;


void do_testcases(){
	int n, m; //#friends, #boxes
	cin >> n >> m;
	
	//read strenghts
	vi s(n);
	REP(i,n){
		cin >> s[i];
	}
	
	//read weights
	multiset<int> ws;
	int w;
	REP(i,m){
		cin >> w;
		ws.insert(w);
	}
	
	sort(ALL(s), std::greater<int>() );

	// check if larges strenghts is less than heaviest box
	if(*max_element(ALL(s)) < *max_element(ALL(ws))){
		cout << "impossible" << endl;
	} else {
		int counter = 0;
		while(!ws.empty()){
			++counter; //need at least one more to run
			//go over all and check if they can carry a box
			REP(i,n){
				auto it = ws.upper_bound(s[i]);
				if(it == ws.begin()){ //strenghts is weaker than lightest box
					break;
				}else{
				  --it;
				  ws.erase(it);	
				}
			}
		}
		cout << 3*counter-1 << endl; //-1 because they can be downstairs in the end	
	}
	
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
