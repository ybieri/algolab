#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()
typedef vector<int> vi;

void do_testcasese(){
	int n; cin >> n;
	vi parasols(n);
	//read in parasols
	REP(i,n){
		cin >> parasols[i];
	}
	
	sort(ALL(parasols));
	
	int mdist = 0; int mcount = 0;
	int last = 0;
	
	vi results;
	
	//for each parasol check if he includes more
	REP(i,n){
		//move i and keep last index, if gap too wide move last index one up until gap small enough again
		while(parasols[i] - parasols[last] > 200){
			++last;
		}
		int c = i - last+1; //interval
		//see how far apart
		int sum = parasols[i] + parasols[last];
		int m = sum/2;
		
		//adjust integer rounding
		if(sum <=0 && sum%2 != 0){
			--m;
		}
		//how far away is distance to middle
		int dist = parasols[i] - m;
		
		//better
		if(c > mcount || (c == mcount && dist < mdist)){
			//found better, so forget old best results
			results.clear();
			mdist = dist;
			mcount = c;
			results.push_back(m);
			if(sum % 2 != 0){//also neighbour if odd. integer division rounds down, so +1
				results.push_back(m+1);
			}
		}else if(c==mcount && dist == mdist){
			results.push_back(m);
			if(sum % 2 != 0){ //if uneven both sides are equally good obviously
				results.push_back(m+1);
			}
		}
	}
	cout << mcount << " " << mdist << endl;
	REP(i,results.size()){
		cout << results[i] << " ";
	}
	cout << endl;
	
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcasese();
	return 0;
}
