#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;
typedef vector<int> v1;
typedef vector<v1> v2;
typedef vector<v2> v3;
typedef vector<v3> v4;
typedef vector<v4> v5;


int round(v2& stacks, v5& table, v1& top_element){
	
	if(table[top_element[0]][top_element[1]][top_element[2]][top_element[3]][top_element[4]] == -1){
		int maxval = -1;
		//form all sets 2^5 = 32
		for(int i=0; i<32; ++i){
			bool valid = true;
			int color = -1;
			int removed = 0;
			v1 new_top(5, 0);
			// go throug all stacks
			for(int j=0; j<5; ++j){
				if(i>>j&1){ //current stack has a 1. we take an element from it
					if(top_element[j] == 0){
						valid = false;
						break;
					}
					
					if(color == -1){
						//cout <<"color -1" << endl;
						color = stacks[j][top_element[j]-1];
					}else if(color != stacks[j][top_element[j]-1]){
						//cout << "color neq" << endl;
						valid = false;
						break;
					}
					++removed;
					new_top[j] = top_element[j] - 1;
				}else{
					new_top[j] = top_element[j];
				}
			}
			if(top_element == new_top){
			}else{
				int point = 0;
				if(removed > 1){
					point = pow(2, removed-2);
				}
				int maxpts = point + round(stacks, table, new_top);
				maxval = std::max(maxval, maxpts);
			}
		}
		table[top_element[0]][top_element[1]][top_element[2]][top_element[3]][top_element[4]] = maxval;

	}
	return table[top_element[0]][top_element[1]][top_element[2]][top_element[3]][top_element[4]];

}


void do_testcases(){
	int n; cin >> n; // num stacks
	vector<int> stacksize(5, 0);
	vector<int> top_elem(5, 0);
	for(int i=0; i<n; ++i){
		cin >> stacksize[i];
		top_elem[i] = stacksize[i];
	}
	
	v2 stacks;
	stacks.reserve(n);
	for(int i=0; i<n; ++i){
		stacks.push_back(vector<int>(stacksize[i], -1));
		for(int j=0; j<stacksize[i]; ++j){
			cin >> stacks[i][j];
		}
	}
	v5 table(stacksize[0]+1, v4(stacksize[1]+1, v3(stacksize[2]+1, v2(stacksize[3]+1, v1(stacksize[4]+1, -1)))));
	
	table[0][0][0][0][0] = 0;
	cout << round(stacks, table, top_elem) << endl	;
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
