// Includes
// ========
// STL includes
#include <iostream>
#include <bits/stdc++.h>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
using namespace std;
using namespace boost;

#define REP(i,n) for(int i=0; i<(int)n; ++i);
#define DEBUG(x) cerr << #x << " = " << (x) << endl;


// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices	
		boost::property<boost::edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef boost::graph_traits<Graph>::edge_descriptor				Edge;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<Graph>::vertex_descriptor			Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef boost::graph_traits<Graph>::edge_iterator				EdgeIt;		// to iterate over all edges
typedef boost::graph_traits<Graph>::out_edge_iterator			OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef boost::property_map<Graph, boost::edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


//##########################################



// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >	Graph2;
// Interior Property Maps
typedef	boost::property_map<Graph2, boost::edge_capacity_t>::type		EdgeCapacityMap;
typedef	boost::property_map<Graph2, boost::edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	boost::property_map<Graph2, boost::edge_reverse_t>::type		ReverseEdgeMap;
typedef	boost::graph_traits<Graph2>::vertex_descriptor			Vertex2;
typedef	boost::graph_traits<Graph2>::edge_descriptor			Edge2;
typedef	boost::graph_traits<Graph2>::edge_iterator			EdgeIt2;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph2 &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph2 & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge2 e, rev_e;
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
void testcases() {
	int V, E, s, f;
	cin >> V >> E >> s >> f;
	
	//Dijkstra
	Graph G(V);
	WeightMap weightmap = get(edge_weight, G);

	//Flow
	Graph2 GG(V);
	EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, GG);
	ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, GG);
	ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, GG);
	EdgeAdder eaG(GG, capacitymap, revedgemap);

	
	//read in edges
	map<Edge, int> edgecapacitymap;
	for (int i = 0; i < E; ++i) {
		int u, v, c, w;
		cin >> u >> v >> c >> w;
		Edge e;	bool success;
		
		tie(e, success) = add_edge(u, v, G);	
		weightmap[e] = w;		
		assert(source(e, G) == u && target(e, G) == v);
		edgecapacitymap[e] = c;
	}

	// Dijkstra shortest paths
	// =======================
	vector<Vertex> predmap(V);	
	
	vector<int> distmap(V);		
	dijkstra_shortest_paths(G, s, 
		predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	
		distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	
	
	vector<int> distmap2(V);		
	dijkstra_shortest_paths(G, f, 
		distance_map(make_iterator_property_map(distmap2.begin(), get(vertex_index, G))));
		
	assert(distmap[f] == distmap2[s]);
	
	//target not reachable. stupid corner case
	if(distmap[f] == 0 || distmap[f] == INT32_MAX){
		cout << 0 << endl;
		return;
	}
	
	// EdgeIterators
	// =============
	EdgeIt ebeg, eend;
	for (tie(ebeg, eend) = edges(G); ebeg != eend; ++ebeg) {	
		Vertex u = source(*ebeg, G);
		Vertex v = target(*ebeg, G);
		
		int capacity = edgecapacitymap[*ebeg];
		int len = weightmap[*ebeg];
		//cannot use predmap because edge can have multiple predecessors.
		//so we use distance map. we add the edge if distance(u) + length + distance2(v) == distance(f) 	
		//edge in shortest path, add to flow graph
		if(distmap[u] + len + distmap2[v] == distmap[f]){
			eaG.addEdge(u, v, capacity);
		}else if(distmap[v] + len + distmap2[u] == distmap[f]){
			eaG.addEdge(v, u, capacity);
		}
	}
	
	long flow = push_relabel_max_flow(GG, s, f);

	cout << flow << endl;
	
	
}

// Main function looping over the testcases
int main() {
	ios_base::sync_with_stdio(false); 
	int T;	cin >> T;
	while(T--)	testcases();
	return 0;
}
