
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/connected_components.hpp>
// Namespaces
using namespace std;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int) n; ++i)
#define DEBUG(x) cout << #x << " = " << x << endl

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> UGraph;
			
			
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
	int rooms, corridors, sweepers;
	cin >> rooms >> corridors >> sweepers;
	
	
	UGraph UG(rooms);
		
	Graph G(rooms);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder ea(G, capacitymap, revedgemap);
	int source = add_vertex(G);
	int target = add_vertex(G);
	
	
	vector<int> start(rooms, 0);
	vector<int> exit(rooms, 0);
	REP(i, sweepers){ 
		int s; cin >> s;
		++start[s];
	}
	REP(i, sweepers){
		int e; cin >> e;
		++exit[e];
	}
		
	vector<int> degree(rooms, 0);	
	REP(i, corridors){
		int u; int v; cin >> u; cin >> v;
		++degree[u]; ++degree[v];
		ea.addEdge(u, v, 1);
		ea.addEdge(v, u ,1);
		add_edge(u,v,UG);
	}
	
	REP(i, rooms){
		if(start[i] > 0) ea.addEdge(source, i, start[i]);
		if(exit[i] > 0)  ea.addEdge(i, target, exit[i]);
	}
	
	// Connected components
	// ====================
	vector<int> componentmap(rooms);	
	int ncc = connected_components(UG, make_iterator_property_map(componentmap.begin(), get(vertex_index, G))); 
	vector<int> componentsize(ncc);
	
	vector<bool> hassweeper(ncc, false);
	if(ncc > 1){
		REP(i, rooms){
			if(degree[i] == 0){
				hassweeper[componentmap[i]] = true;
			}
			if(start[i] > 0){
				hassweeper[componentmap[i]] = true;
			}
		}
		REP(i, ncc){
			if(!hassweeper[i]){
				cout << "no" << endl;
				return;
			}
		}
	}
	
	

	long flow = push_relabel_max_flow(G, source, target);
	if(flow < sweepers){
		cout << "no" << endl;
		return;
	}else{
		REP(i, rooms){
			if((degree[i] + start[i] + exit[i]) % 2 == 1){
				cout << "no" << endl;
				return;
			}
		}
		cout << "yes" << endl;
	}
}

// Main function to loop over the testcases
int main() {
	ios_base::sync_with_stdio(false);
	int t;	cin >> t;
	while(t--)	do_testcases();
	return 0;
}

