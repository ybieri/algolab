#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
// Namespaces
using namespace std;
using namespace boost;


// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;


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
		//cout << "u, v " << from << " " << to << endl;
		Edge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}
};

// Functions
// =========
// Function for an individual testcase
void do_testcases() {
	int n,m,k,c;
	cin >> n >> m >> k >> c;
		
	int x = n*m;
		
	Graph G(2*x);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder ea(G, capacitymap, revedgemap);

	int source = add_vertex(G);
	int target = add_vertex(G);

	for(int i=0; i<x; ++i){
		ea.addEdge(i, i+x, c); //in out with max vertex visits c.
	}
	
	for(int i=0; i<x; ++i){
		if(i == 0){
			ea.addEdge(i+x, target, 2);
			ea.addEdge(i+x, i+1, 1);
			ea.addEdge(i+x, i+m, 1);
			continue;
		}
		if(i == m-1){
			ea.addEdge(i+x, target, 2);
			ea.addEdge(i+x, i-1, 1);
			ea.addEdge(i+x, i+m, 1);
			continue;
		}
		if(i == m*(n-1)){
			ea.addEdge(i+x, target, 2);
			ea.addEdge(i+x, i+1, 1);
			ea.addEdge(i+x, i-m, 1);
			continue;
		}
		if(i == x-1){
			ea.addEdge(i+x, target, 2);
			ea.addEdge(i+x, i-1, 1);
			ea.addEdge(i+x, i-m, 1);
			continue;
		}
		
		if(i<m){ // top row
			ea.addEdge(i+x, target, 1);
			ea.addEdge(i+x, i-1, 1);
			ea.addEdge(i+x, i+1, 1);
			ea.addEdge(i+x, i+m, 1);
			continue;
		}
		if(i > (m* (n-1))){ // bottom row
			ea.addEdge(i+x, target, 1);
			ea.addEdge(i+x, i-1, 1);
			ea.addEdge(i+x, i+1, 1);
			ea.addEdge(i+x, i-m, 1);
			continue;
		}
		
		if(i%m == 0){ // left side
			ea.addEdge(i+x, target, 1);
			ea.addEdge(i+x, i+m, 1);
			ea.addEdge(i+x, i+1, 1);
			ea.addEdge(i+x, i-m, 1);
			continue;
		}
		
		if(i%m == (m-1)){ // right side
			ea.addEdge(i+x, target, 1);
			ea.addEdge(i+x, i+m, 1);
			ea.addEdge(i+x, i-1, 1);
			ea.addEdge(i+x, i-m, 1);
			continue;
		}
		
		// rest
		ea.addEdge(i+x, i+m, 1); //one lower
		ea.addEdge(i+x, i-m, 1); //one higher
		ea.addEdge(i+x, i+1, 1); //one right
		ea.addEdge(i+x, i-1, 1); //one left
	}
	
	for(int i=0; i<k; ++i){
		int x, y; cin >> x >> y; //column, row
		ea.addEdge(source, x*m + y, 1);
	}
	
	
	long flow = push_relabel_max_flow(G, source, target);
	cout << flow << endl;
}

// Main function to loop over the testcases
int main() {
	ios_base::sync_with_stdio(false);
	int t;	cin >> t;
	while(t--) do_testcases();
	return 0;
}

