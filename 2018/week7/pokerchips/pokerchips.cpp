#include <bits/stdc++.h>
#include <iostream>

using namespace std;
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define REP(i,n) for(int i=0; i<(int)n; ++i)

//1 to 5 dim int vector
typedef vector<int> 	vi;
typedef vector<vi> 		vvi;
typedef vector<vvi> 	vvvi;
typedef vector<vvvi> 	vvvvi;
typedef vector<vvvvi> 	vvvvvi;


int f(vvi& stacks, vvvvvi& memo, vi& pos, vi& stacksize, int n){
	
	//we already have the value. also ends at 0 0 0 0 0 because we defined that
	if(memo[pos[0]][pos[1]][pos[2]][pos[3]][pos[4]] != -1){
		return memo[pos[0]][pos[1]][pos[2]][pos[3]][pos[4]];
	}
	
	int best = -1;
	
	//for all 32 possibilities how we can remove chips
	FOR(s, 1, 32){//have to at least remove one, staring with 0 would crash
		//
		vi new_pos(5);
		bool valid = true; //is it a valid config?
		int color = -1; //can only remove 1 color at a time
		int counter = 0;
		
		//for all 5 stacks
		REP(i, 5){
			//if element was choosen
			if(s & 1<<i){
				//cannot remove that chip
				if(pos[i] == 0){
					valid = false;
					break;
				}
				
				if(color == -1){
					color = stacks[i][pos[i]-1];
				}else if(color != stacks[i][pos[i]-1]){
					valid = false;
					break;
				}
				
				++counter;
				new_pos[i] = pos[i]-1;
				
			}else{ //element was not choosen
				new_pos[i] = pos[i];
			}
		}
		//is it a valid configuration, e.g. only removed chips from the same color
		if(valid){
			int points = 0;
			if(counter > 1){
				points = pow(2, counter-2);
			}
			// check if this config is better and update accordingly
			best = max(best , points + f(stacks, memo, new_pos, stacksize, n));	
		}
	}
	
	//update value of current top elements to maximum achievable
	memo[pos[0]][pos[1]][pos[2]][pos[3]][pos[4]] = best;
	return best;
	
}



void do_testcases(){
	int n; cin >> n; //number of stacks
	
	//get all stack sizes. rest is 0 if we have less than 5 stacks
	vi stacksize(5, 0);
	vi position(5, 0);
	REP(i,n){
		cin >> stacksize[i];
		//position initally is at top element thus stack size
		position[i] = stacksize[i];
	}
	
	//read in all the chips on the stacks
	vvi stacks(n, vi());
	REP(i,n){
		REP(j,stacksize[i]){
			int c; cin >> c;
			stacks[i].push_back(c);
		}
	}
	//initialize memo
	vvvvvi memo(stacksize[0]+1, vvvvi(stacksize[1]+1, vvvi(stacksize[2]+1, vvi(stacksize[3]+1, vi(stacksize[4]+1, -1)))));
	//base case, all empty
	memo[0][0][0][0][0] = 0;
	cout << f(stacks, memo, position, stacksize, n) << endl;
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
