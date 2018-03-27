//includes
#include <iostream>
#include <vector>
#include <algorithm>
//namespaces
using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

void do_testcases(){
	int n; cin >> n;
	vector<vector<int> > x(n, vector<int>(n));
	vector<vector<int> > s(n, vector<int>(n));

    
	int even_pairs = 0;
    //geet x[i][j]
	REP(i,n){
		REP(j,n){
			cin >> x[i][j];
		}
	}
	//create sums
	REP(i,n){
		int sum = 0;
		REP(j,n){
			sum += x[i][j];
			s[i][j] = sum;
		}
	}
	
	REP(i1,n){
		for(int i2=i1; i2<n; ++i2){
			int even = 0;
			int odd = 0;
			
			REP(j,n){
				int sum = s[j][i2] - (i1  == 0 ? 0 : s[j][i1-1]);
				if(j==0){
					if(sum % 2 == 0) even = 1;
					else odd =1;
				} else {
					if(sum % 2 == 0) {
						even += 1;
					} else {
						int tmp = even;
						even = odd;
						odd = tmp + 1;
					}	
				}
				even_pairs += even;
			}
		
		}
	}
	
	cout << even_pairs << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
}
