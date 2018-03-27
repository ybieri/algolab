#include <vector>
#include <iostream>
using namespace std;
/*buggy*/
#define DEBUG(x) ;//cerr << #x << " = " << (x) << endl;
typedef vector<int> vi;
typedef vector<vector<bool>> vvb;
typedef vector<vi> vvi;

bool f(int i, int h, int k, int n, int I, vi& heights, vvi& memo){
	if((h + heights[i]) % k == I) return true;
	if(i == n-1) return false;
	
	bool b1, b2;
	if(memo[i+1][h] != -1){
		b1 = memo[i+1][h];
	}else{
		b1 = f(i+1, h, k, n, I, heights, memo);
		memo[i+1][h] = b1;
	}
	
	if(memo[i+1][(h+heights[i])%k] != -1){
		b2 = memo[i+1][(h+heights[i])%k];
	}else{
		b2 = f(i+1, (h+heights[i])%k, k, n, I, heights, memo);
		memo[i+1][(h+heights[i])%k] = b2;
	}
	
	return (b1 || b2);
}

void do_testcases(){
	int n, I, k;
	cin >> n >> I >> k;
	vector<int> heights(n);
	for(int i=0; i<n; ++i){
		int height; cin >> height;
		heights[i] = height%k;
	}
	
	vector<vector<int>> memo(n, vector<int>(k, -1));
	
	bool possible = f(0, 0, k, n, I, heights, memo);
	
	
	if(possible) cout << "yes" << endl;
	else cout << "no" << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
