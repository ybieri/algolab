#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

typedef vector<int> vi;
typedef vector<vi> vvi;




void do_testcases(){
	int k, n ,q;
	cin >> k >> n >> q;
	
	//ignore
	REP(i,k){
		int a, b;
		cin >> a >> b;		
	}
	
	unordered_map<string,int> matrix;
	
	// fill matrix
	REP(i,n){
		string s;
		REP(j,k){
			int tmp; cin >> tmp;
			s+=to_string(tmp);
		}
		int res; cin >> res;
		matrix[s] = res;
	}
	
	// do for all queries
	REP(i,q){
		string s;
		REP(j,k){
			int tmp; cin >> tmp;
			s+=to_string(tmp);
		}
	
		if(matrix.find(s) == matrix.end()){
			cout << -1 << endl;
		}else{
			cout << matrix[s] << endl;
		}
	}		
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;	
}
