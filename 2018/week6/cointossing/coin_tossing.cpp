// Includes
// ========
// STL includes
#include <iostream>
#include <bits/stdc++.h>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
// Namespaces
using namespace std;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i)

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	boost::property_map<Graph, boost::edge_capacity_t>::type		EdgeCapacityMap;
typedef	boost::property_map<Graph, boost::edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	boost::property_map<Graph, boost::edge_reverse_t>::type		ReverseEdgeMap;
typedef	boost::graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	boost::graph_traits<Graph>::edge_descriptor			Edge;
typedef	boost::graph_traits<Graph>::edge_iterator			EdgeIt;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, rev_e;
		bool success;
		boost::tie(e, success) = boost::add_edge(from, to, G);
		boost::tie(rev_e, success) = boost::add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[rev_e] = 0; // reverse edge has no capacity!
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};


// Functions
// =========
// Function for an individual testcase
void testcases() {
	int n,m; cin >> n >> m;
	
	Graph G(n+m);

	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);
	
	REP(i,m){
		int a,b,c;
		cin >> a >> b >> c;
		//edge from match i to player a
		if(c==1){
			eaG.addEdge(i, m+a, 1);
		} else if (c==2){
			eaG.addEdge(i, m+b, 1);
		} else{//could be either
			eaG.addEdge(i, m+a, 1);
			eaG.addEdge(i, m+b, 1);
		}
	}
	
	Vertex src = boost::add_vertex(G);
	Vertex trg = boost::add_vertex(G);
	
	//add 1 point to each match
	REP(i,m){
		eaG.addEdge(src, i, 1);
	}
	
	// read in points of each player. add edge to target
	int totalscore = 0;
	REP(i,n){
		int s; cin >> s;
		totalscore += s;
		eaG.addEdge(m+i, trg, s);
	}
	
	//if those idiots did not even check that the scoreboards sums up to m (only a problem if sum is larger than m)
	if(totalscore != m){
		cout << "no" << endl;
		return;
	}

	long flow = boost::push_relabel_max_flow(G, src, trg);

	if(flow == m){
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}

// Main function to loop over the testcases
int main() {
	std::ios_base::sync_with_stdio(false);
	int T;	cin >> T;
	for (; T > 0; --T)	testcases();
	return 0;
}
