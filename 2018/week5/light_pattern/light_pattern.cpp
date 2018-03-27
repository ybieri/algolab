#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) ; //cerr << #x << " = " << (x) << endl;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;


int diff(int groupindex, bool swapped, vb& pattern, vb& light){
	
	int counter = 0;
	int k = pattern.size();

	REP(i, k){
		if(pattern[i] !=  light[k*groupindex+i]){
			++counter;
		}
	}
	//if not swapped we return counter, if swapped we return all the others (k-counter)
	return (!swapped ? counter : k-counter);
}

int to_int(bool swapped){
	return (!swapped ? 0 : 1);
}

// recursively comppute otimal solution, populate memo
int f(int i, bool swapped, vvi& memo, vb& pattern, vb& light){	
		
	//base case
	if(i<0){
		return 0;
	}
		
	int j = to_int(swapped);
	
	if(memo[j][i] != -1){
		return memo[j][i];
	}
	
	// either we swap all individually or 
	// swap all (1) and the rest individually
	int a, b;
	a = diff(i, swapped, pattern, light) + f(i-1, swapped, memo, pattern, light);
	b = 1 + diff(i, !swapped, pattern, light) + f(i-1, !swapped, memo, pattern, light);
	memo[j][i] = min(a, b);
	
	return memo[j][i];
}



//setup for each individual testcase
void do_testcases(){
	int n, k, x;
	//light lenghts, pattern length, pattern
	cin >> n >> k >> x;
	
	int numgroup = n/k;
	
	//read in initial state
	vector<bool> light(n);
	REP(i,n){
		int onoff; cin >> onoff;
		light[i] = onoff == 1;
	}
	//change from bit encoded to vector of bools
	vector<bool> pattern(k);
	REP(i,k){
		pattern[k-1-i] = (x >> i) & 0x1;
	}
	
	//groups calculated. 2 for true and false
	vvi memo(2, vi(numgroup, -1));

	cout << f(numgroup-1, false, memo, pattern, light) << endl;	
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
