#include <iostream>
#include <vector>

using namespace std;

vector<pair<bool, bool> > switches;
int num_off;
int num_switches;
//for room 0

//i:switch, j:brightness
bool f(int i, int j, vector<vector<int> >& state){ 	 //i:which switch, j=current sum of lights on
	if(j == 0) return true; 				 //subset achieved
	if(i == num_switches-1 || j < 0) return false; 		 // went through all, subtracted too much
	
	bool on, off;
	on  = f(i+1,j-state[i][0], state);  //room 0
	off = f(i+1,j-state[i][1], state);
	
	
	//safe result form computation
	if(on || off) switches[i] = make_pair(on,off);
	if(!on && off) ++num_off;
	
	
	return on || off;
}

void do_testcases(){
	int num_rooms;
	cin >> num_switches >> num_rooms;
	
	switches.reserve(num_switches);
	num_off = 0;
	
	//read in target brightness per room
	vector<int> target_brightness(num_rooms);
	for(int i=0; i<num_rooms; ++i){
		int brightness; cin >> brightness;
		target_brightness[i] = brightness;
	}
	

	vector<vector<int> > state(num_switches, vector<int>(2*num_rooms));
	
	for(int i=0; i<num_switches; ++i){
		for(int j=0; j<2*num_rooms; j+=2){
			int on, off;
			cin >> on >> off;
			state[i][j] = on;
			state[i][j+1] = off;
		}
	}

	//find possible subset sums for the first set. for all check if all other rooms also add up
	//if yes -> number of flips, otherwise "impossible:

	//starting with 0-th switch, weight0
	bool success = f(0, target_brightness[0], state);
	
	if(!success) cout << "impossible one" << endl;
	else{
		//for all rooms check if true,false - on,off adds up to brightness
		int x = 1;
		for(int i=1; i<2*num_rooms; i=+2){
			++x;
			int sum = 0;
			for(int j=0; j<num_switches; ++j){
				if(switches[j].first) sum=+state[j][i];
				else sum=+state[j][i+1];
			}
			if(sum!= target_brightness[x]) cout << "impossible two" << endl;
			return;
		}
		cout << num_off << endl;
	}

}


int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}

