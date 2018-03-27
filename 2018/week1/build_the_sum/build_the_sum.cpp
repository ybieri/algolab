//includes
#include <iostream>
#include <algorithm>
#include <vector>

//namespaces
using namespace std;
//defs
#define REP(i,n) for(int i=0; i<(int)n; ++i)


void do_testcases(){
	int m; cin >> m;
	float f = 0.0;
	REP(i, m){
		float temp; cin >> temp;
		f += temp;
	}
	cout << f << endl;
}

int main(){
	ios_base::sync_with_stdio(false); // if you use cin/cout. Do not mix cin/cout with scanf/printf calls!
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}


