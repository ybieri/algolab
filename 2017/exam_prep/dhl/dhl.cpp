#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;

//~ int f(int ai, int bi, vector<int>& a_vec, vector<int>& b_vec, vector<vector<int> >& memo, int n){
	//~ int minval = INT_MAX;
	//~ //cout << "ai, bi, n" << ai << " " << bi << " " << n<<endl;
	//~ for(int i = ai; i<n; ++i){
		//~ for(int j = bi; j<n; ++j){
			
			//~ int ls = -1, rs = -1;
			//~ if(ai == 0){
				//~ ls = (a_vec[i]);
				//~ cout << "ai == 0" << endl;
			//~ }
			//~ if(bi == 0){
				//~ rs = (b_vec[j]);
				//~ cout << "bi == 0" << endl;
			//~ }
			//~ if(ls == -1)
				//~ ls = (a_vec[i] - a_vec[ai]);
			//~ if(rs == -1)
				//~ rs = (b_vec[j] - b_vec[bi]);
			//~ cout << "ls, rs "<< ls  << " "<< rs << endl;
			//~ int mn;
			
			//~ if(j == n-1){
				//~ cout << "j==n-1" << endl;
				//~ ls = (a_vec[n-1] - a_vec[ai]);
				//~ memo[i][j] == ls*rs;
				//~ mn = memo[i][j];

			//~ } else if(i == n-1){
				//~ cout << "i==n-1" << endl;
				//~ rs = (b_vec[n-1] - b_vec[bi]); 
				//~ memo[i][j] == ls*rs;
				//~ mn = memo[i][j];
			//~ } else if(memo[i][j] == -1){
				//~ cout << "i,j " << i << " " << j << endl;
				//~ memo [i][j] = f(i+1, j+1, a_vec, b_vec, memo, n);
				//~ cout << "memo " << memo[i][j] << endl;
				//~ mn = ls * rs + memo[i][j];
			//~ }
			
			//~ cout << "mn " << mn << endl;
			//~ minval = std::min(minval, mn);
		//~ }
	//~ }
	//~ return minval;
//~ }

int f(int ai, int bi, vector<int>& a_vec, vector<int>& b_vec, vector<vector<int> >& memo, int n){
	if(ai == (n-1) && bi == (n-1)){
		return b_vec[n-1] * a_vec[n-1];
	}else if(bi == (n-1)){
		return (b_vec[n-1]-b_vec[n-2]) * (a_vec[n-1] - a_vec[ai]);
	} else if(ai == (n-1)){
		return (a_vec[n-1]-a_vec[n-2]) * (b_vec[n-1] - b_vec[bi]);
	} else {
		int minval = INT_MAX;
		for(int i=ai+1; i<n; ++i){
			for(int j=bi+1; j<n; ++j){
				minval = std::min(minval,(a_vec[i] - a_vec[ai]) * (b_vec[bi] - b_vec[j]) + f(i+1, j+1, a_vec, b_vec, memo, n));
				if(minval <0)
					cout << i << " " << j << endl;
			}
		}
		return minval;
	}
}






void do_testcases(){
	int n; cin >>n;
	vector<int> a_vec(n);
	vector<int> b_vec(n);
	vector<int> a(n);
	vector<int> b(n);
	
	vector<vector<int> > memo(n, vector<int>(n, -1));
	
	for(int i=0; i<n; ++i){
		int x;
		cin >> x;
		a[i] = x-1;
	}
	for(int i=0; i<n; ++i){
		int y;
		cin >> y;
		b[i] = y-1;
	}
	a_vec[0] = a[0];b_vec[0] = b[0];
	
	
	for(int i=1; i<n; ++i){
		a_vec[i] = a_vec[i-1] + a[i];
		b_vec[i] = b_vec[i-1] + b[i];
	}
	memo[n-1][n-1] = a_vec[n-1] * b_vec[n-1];

	cout << f(0,0, a_vec, b_vec, memo, n) << endl;
}
 


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >>t;
	while(t--) do_testcases();
	return 0;	
}
