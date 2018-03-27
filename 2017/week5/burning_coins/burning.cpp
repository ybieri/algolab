#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> W;



int f(int i, int j, vector<vector<int> >& memo){
	int result;
	int coins_left = j-i;
	
	if(coins_left == 1){
		result = max(W[i],W[j]);
		memo[i][j] = result;
		return result;
	}else if(coins_left == 2){
		if(W[i]>W[j]){
			if(W[i+1]>W[j]){
				result = W[i] + W[j];
			}else{
				result = W[i] + W[i+1];
			}
		}else{
			if(W[i]>W[i+1]){
				result = W[j] + W[i+1];
			}else{
				result = W[j] + W[i];
			}
		}
		return result;
	}
	
	if(memo[i][j] == -1){
		if(i == j)result = W[i];
		else result = max(W[i] + min(f(i+2,j, memo), f(i+1, j-1, memo)) , W[j] + min(f(i+1, j-1, memo), f(i, j-2, memo)));
		memo[i][j] = result;
	}else{
		result = memo[i][j];
	}
	return result;
}


void do_testcases(){
	cin >> n;
	W.reserve(n);
	vector<vector<int> > memo(n, vector<int>(n));
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			memo[i][j] = -1;
		}
	}

	for(int i=0; i<n; ++i){
		int w; cin >> w;
		W[i] = w;
	}

	int res = f(0, n-1, memo);
	cout << res << endl;
}


int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
