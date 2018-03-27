#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()
#define mp(x,y) make_pair(x,y)
#define DEBUGP(x) cerr << #x << " = " << (x).first << " " << (x).second << endl;
#define DEBUG(x)  cerr << #x << " = " << (x) << endl;



typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;

inline int EDF(vector<ii>& no_overlap, int min_a, int max_b){
	int a = min_a;
	int c = 0;
	
	for(auto it=no_overlap.begin(); it!=no_overlap.end(); ++it){
		if(it->second > a && it->first < max_b){
			++c;
			a = it->first; //update end
		}
	}
	return c;
}



void do_testcases(){
	int n, m;
	cin >> n >> m; //#jedi, #segments
	
	vector<ii> jedi(n);
	
	map<int,int> intervals;
	
	REP(i,n){
		int a, b; 
		cin >> a >> b;
		--a; --b; //0 based indexing
		
		jedi[i] = mp(b, a); //reverse interval for easier sorting
		
		//so we can in one go detect smalest overlap number
		//scanline: +1 if interval starts, -1 if it ends. sum and find minimum
		++intervals[a];
		--intervals[b];
		
		if(a > b){
			 ++intervals[0];
		 }
	}
	
	int minimum = n;
	int minsize = 0;
	int minlocation = 0;
		
	
	for(auto it=intervals.begin(); it!=intervals.end(); ++it){
		minsize += it->second;
		if(minsize <= 10 && minsize < minimum){
			minimum = minsize;
			minlocation = it->first;
		}
	}
	
	//recenter jedi around minlocation
	vector<ii> overlap;
	vector<ii> no_overlap;
	
	REP(i,n){
		int a = jedi[i].second;
		int b = jedi[i].first;
		
		if(a > minlocation){
			jedi[i].second = a-minlocation;
		}else{
			jedi[i].second = m-minlocation+a; //put it after the "rest is used" (m-minlocation)
		}
		
		if(b > minlocation){
			jedi[i].first = b-minlocation;
		}else{
			jedi[i].first = m-minlocation+b;
		}
		
		if((a <= b && a <= minlocation && minlocation <= b) ||
			(a > b && (a <= minlocation || minlocation <= b))){
			//overlap happened	
			overlap.push_back(jedi[i]);
		}else{
			no_overlap.push_back(jedi[i]);
		}
	}
	
	
	//sorting according to end boundry	
	sort(ALL(no_overlap)); 
	
	int best = EDF(no_overlap, -1, m);
	
	for(auto it=overlap.begin(); it!=overlap.end(); ++it){
		best = std::max(best, EDF(no_overlap, it->first % m, it->second)+1);
	}
	
	cout << best << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;	
}
