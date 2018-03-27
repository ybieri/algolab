//includes
#include <iostream>
#include <vector>
#include <algorithm>
//namespaces
using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

void do_testcases(){
	int n; cin >> n;
	vector<int> x(n);
	vector<int> e(n);
	vector<int> o(n);
    
	int even_pairs = 0;
    
	REP(i,n){
		cin >> x[i];
		if(i==0){
			if(x[i] == 0) {
				e[i] = 1;
			}else{
				o[i] = 1;
			}
		} else {
			if(x[i] == 0) {
				e[i] = e[i-1] + 1;
				o[i] = o[i-1];
			}else{
				e[i] = o[i-1];
				o[i] = e[i-1] + 1;
			}
		}
		even_pairs += e[i];
	}
	
	cout << even_pairs << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
}
