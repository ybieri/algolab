#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()

typedef vector<int> vi;
typedef vector<vi> vvi;

void do_testcases(){
	int n, k; cin >> n >> k;
	int p;
	
	set<int> lighter;
	set<int> heavier;
	set<int> equal;
	set<int> coins;
	//add all possible coins
	REP(i,n){ 
		coins.insert(i+1);
	}
	
	REP(i,k){
		cin >> p; //num coins per pan
		vi leftPan(p);
		vi rightPan(p);
		
		REP(j,p){
			cin >> leftPan[j];
		}
		REP(j,p){
			cin >> rightPan[j];
		}
		char sign; cin >> sign;
		set<int> diff;
		set<int> unequal; 
		set<int> intersection;

		switch(sign) {
			case '=' : 
				equal.insert(ALL(leftPan));
				equal.insert(ALL(rightPan));
				//remove equal coins from coins
				set_difference(ALL(coins), ALL(equal), inserter(diff, diff.begin()));
				coins = diff;
				diff.clear();
				break;
			case '<' : 
				lighter.insert(ALL(leftPan));
				heavier.insert(ALL(rightPan));
				//possible coins can only be coins mentioned in a < or > statement
				unequal.insert(ALL(leftPan)); unequal.insert(ALL(rightPan));
				set_intersection(ALL(coins), ALL(unequal), inserter(intersection, intersection.begin()));
				coins = intersection;
				unequal.clear();
				intersection.clear();
				break;
			case '>' :
				lighter.insert(ALL(rightPan));
				heavier.insert(ALL(leftPan));

				//possible coins can only be coins mentioned in a < or > statement
				unequal.insert(ALL(leftPan)); unequal.insert(ALL(rightPan));
				set_intersection(ALL(coins), ALL(unequal), inserter(intersection, intersection.begin()));
				coins = intersection;
				unequal.clear();
				intersection.clear();
				break;
		}
		
	}
	
	
	//get goins that are ligher and heaviers -> intersection
    set<int> inter;
    set_intersection(ALL(lighter), ALL(heavier), inserter(inter,inter.begin()));
		
	vi result;
	set_difference(ALL(coins), ALL(inter), inserter(result, result.begin()));
    
    //check for equations with 
    vi lightMinusEqual;
	set_difference(ALL(lighter), ALL(equal), inserter(lightMinusEqual, lightMinusEqual.begin()));
    vi heavyMinusEqual;
	set_difference(ALL(heavier), ALL(equal), inserter(heavyMinusEqual, heavyMinusEqual.begin()));
    
    if(result.size() == 1){
		cout << result[0] << endl;
	} else if(lightMinusEqual.size() == 1){
		cout << lightMinusEqual[0] << endl;
	} else if (heavyMinusEqual.size() == 1){
		cout << heavyMinusEqual[0] << endl;
	} else {
		cout << 0 << endl;
	}

}



int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
