#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<vector<ll>, vector<ll> IPair;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

vector<IPair> memo;

void f(vector<ll>& len, int index, ll sum1, ll sum2, ll sum3, ll sum4, ll side, ll s1, ll, s2, ll s3, lls4){
	//one side too large
	if(std::max({sum1, sum2, sum3, sum4}) > side){
		return;
	}
	
	if(index >= len.size()/2){
		Ipair pp = Ipair({sum1, sum2, sum3, sum4}, {s1, s2, s3, s4});
		memo.push_back(pp);
		return;
	}
	
	s1 |= 1LL << index;
	
}



void do_testcases(){
	int n; cin >> n;
	ll side = 0;
	memo.clear();
	vector<ll> len(n);
	
	REP(i,n){
		cin >> len[i];
		side += len[i];
	}
	
	side /= 4; //total length divided by 4 is side lenght as all planks need to be used
	
	ll s1, s2, s3, s4;
	s1 = s2 = s3 = s4 = 0;
	
	f(len, 0,0,0,0,0,side, s1, s2, s3, s4);
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
