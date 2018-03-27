#include <vector>
#include <iostream>
using namespace std;
void do_testcases(){
	int n, I, k;
	cin >> n >> I >> k;
	vector<int> heights(n);
	for(int i=0; i<n; ++i){
		int height; cin >> height;
		heights[i] = height%k;
	}
	vector<vector<bool> > T(n, vector<bool>(k, false));
	// inital sums you can reach
	for(int i=0; i<n; ++i) T[i][heights[i]] = true;
	for(int i=1; i<n; ++i)
		for(int j=0; j<k; ++j)
			T[i][j] = T[i-1][j] || T[i-1][(k+j-heights[i])%k];
	if(T[n-1][k-1])	cout << "yes" << endl;
	else cout << "no" << endl;
}
int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
