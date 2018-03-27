#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define FOR(i,x,n) for(int i=x; i<(int)n; ++i)
#define ALL(x) (x).begin(), (x).end()

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;


//binary search. find largest index i s.t. age[path[i]] <= maxage 
int binary(int maxage, const vi& path, const vi&age){
	int l = -1; //largest index so p(l) is false
	int r = path.size()-1; //smallest index where p(r) is true
	
	while(l != r){
		int m = (l+r)/2;
		// age[path[m]] -> age of species at point  m of path
		if(age[path[m]] <= maxage){
			r = m;
		} else { //age > maxage
			l = m+1;
		}
	}
	return path[r];
}



//recursive dfs
void dfs(int u, const vvi& tree, vi& path, const vector<vector<ii>>& query, vi& result, const vi& age){
	//process all queries for node u
	REP(i, query[u].size()){
		// [number of the query red in] = 
		result[query[u][i].second] = binary(query[u][i].first, path, age);
	}
	//continue dfs
	REP(i, tree[u].size()){
		//tree[u][i] -> i-th child of node u
		int v = tree[u][i];
		path.push_back(v);
		dfs(v, tree, path, query, result, age);
	}
	// remove last element
	path.pop_back();
}




void do_testcases(){
	int n,q; cin >> n >> q;
	
	unordered_map<string, int> species_index; //maps species to index
	vector<string> species(n); //maps index to species
	vi age(n);
	
	REP(i,n){
		string name; cin >> name >> age[i];
		species_index[name] = i;
		species[i] = name;
	}
	
	//need root index for dfs:
	int root = max_element(ALL(age))-age.begin();
	
	//read in parent-child relation
	vvi tree(n);
	REP(i,n-1){
		string child, parent;
		cin >> child >> parent;
		//add child to the parents child vector
		tree[species_index[parent]].push_back(species_index[child]);
	}
	
	//read queries
	vector< vector <ii> > query(n);
	//store the maxage and the index when reading so we can sort them in the end when outputting
	REP(i,q){
		string name; cin >> name;
		int maxage; cin >> maxage;
		query[species_index[name]].push_back(make_pair(maxage,i));
	}
		
	//need a path
	vi path; path.push_back(root);
	//vector to store indices of results
	vi result(q);
		
	dfs(root, tree, path, query, result, age);
	
	REP(i,q){
		cout << species[result[i]];
		if(i<q-1) cout << " ";
	}
	cout << endl;	
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
