#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



void do_testcase(){
	int n, m;
	cin >> n >> m;
	
	//pair of end-begin
	vector<pair<int,int> > jedies(n);
	
	// read in the intervals the jedi do protect
	for(int i=0; i<n; ++i){
		int a, b;
		cin >> a >> b;
		
		if(a<b){
			jedies[i] = {b,a};
		}else{
			jedies[i] = {b+m, a};
		}
	}
	
	// sort the intervals accordng to lowest end
	sort(jedies.begin(), jedies.end());
	
	int best = 0;
	vector <int> as;
	vector <int> bs;
	bool flag = false;
	
	// do edf for each segment
	for(int i=1; i<=m; ++i){	
		int current_end = i;
		int counter = 0;
		for(int j=0; j<n; ++j){
			int b = jedies[j].first;
			int a = jedies[j].second;

			if(b > i+m-1 || (a <= m && b > m)){
				best = max(best, counter);
				flag = true;		
				break;
			}
			if(a >= (current_end%m)){
				// added interval, update end to b
				if(flag){
					as.clear();
					bs.clear();
					flag = false;
				}
				
				++counter;
				as.push_back(a);
				bs.push_back(b);
				current_end = b;
			}
		}
		best = max(best, counter);
	}
	cout << best << endl;
	for(int i = 0; i<as.size(); ++i){
		cout << as[i] << " " << bs[i] << endl;
	}
}



int main(){
	int t; cin >> t;
	while(t--) do_testcase();
	return 0;
}
