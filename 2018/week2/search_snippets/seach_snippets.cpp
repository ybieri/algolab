#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define REP(i,n) for(int i = 0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i = x; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); ++i)
#define DEBUG(x) cerr << #x << " = " << (x) << endl;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;


void do_testcases(){
	int n; cin >> n;
	vi wordcount(n);
	int totalwords = 0;
	// read in number of occurences per word
	REP(i,n){
		cin >> wordcount[i];
		totalwords += wordcount[i];
	}
	
	vector<ii> wordlist(totalwords); // vector of size n initialized to -1
	int index = 0;
	// read in the n lines
	REP(i,n){
		REP(j, wordcount[i]){
			int pos; cin >> pos;
			wordlist[index] = make_pair(pos, i);
			++index;
		}
	}
	
	//wordlist is an array of <position, word>, e.g (1,a) (3,b) etc.. (a,b are integers but easier to read with characters.	
	sort(ALL(wordlist));

	//checked, sorting works

	vi lastposition(n, INT_MAX);
	int best = INT_MAX;
	int minelementposition = 0;
	int minelementword = wordlist[0].second;
	
	set<int> wordsencountered;
	
	REP(i, wordlist.size()){
		int position = wordlist[i].first; // 0 1 2
		int word = wordlist[i].second; // a  b c
		lastposition[word] = position;
		
		wordsencountered.insert(word);

		//DEBUG(lastposition[0]) DEBUG(lastposition[1])
	
		if (minelementword == word){
			auto it = min_element(ALL(lastposition));
			minelementposition = *it;
			minelementword = distance(begin(lastposition), it);
		}
		
		if(wordsencountered.size() != n) continue;

		//DEBUG(position) DEBUG(word) DEBUG(minelementposition) DEBUG(minelementword)
				
		//DEBUG(position) DEBUG(minelementposition)
		int interval = position-minelementposition+1;
		
		//DEBUG(interval) DEBUG(best)
		best = ( (best<interval) ? best : interval);
		
	}
	
	cout << best << endl;
}



int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return  0;
}
