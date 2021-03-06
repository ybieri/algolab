#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
// Namespaces
using namespace boost;
using namespace std;

// BGL Graph definitions
// ===================== 
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;
// Interior Property Maps
typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
		//cout << "adding edge from " << u << " to " << v << endl;
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w;
        capacitymap[reverseE] = 0;
        weightmap[reverseE] = -w;
        revedgemap[e] = reverseE; 
        revedgemap[reverseE] = e; 
    }
};

const int w = 100;

// Main
void do_testcases(){
	
	int n, m, s;
	cin >> n >> m >> s;
	
	//cout << "nms" << n << m << s;
	vector<int> limits(s);
	for(int i=0; i<s; ++i){
		cin >> limits[i];
	}
	
	vector<int> states(m);
	for(int i=0; i<m; ++i){
		cin >> states[i];
		--states[i]; //who the fuck would not ues zero indexing in the first place???
	}
	
	
	Graph G(n+m+s+2);
	// 0- n-1 buyers, n- n+m-1 houses
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
    EdgeWeightMap weightmap = get(edge_weight, G);
    ReverseEdgeMap revedgemap = get(edge_reverse, G);
    ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
    EdgeAdder ea(G, capacitymap, weightmap, revedgemap);

	//Vertex src = add_vertex(G);
	//Vertex target = add_vertex(G);
	int src = n+m+s;
	int target = n+m+s+1;
	
	//cout << n << " " << m << " " << s << endl;
	//cout << src << " " << target << endl;

	for(int i=0; i<n; ++i){
		ea.addEdge(src, i, 1, 0); //src to all buyers. 1/0
	}
	// from source to (0 to n-1)
	
	// add edges from all buyers to all houses
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			int bid; cin >> bid;
			//cout << "bid ij" << bid << " i " << i << " j " << j << endl;
			ea.addEdge(i, n+j, 1, w-bid);
		}
	}
	//from(0, n-1) to (n, n+m-1)
	
	// add edge from 
	for(int i=0; i<m; ++i){
		ea.addEdge(n+i, n+m+states[i], 1, 0);
	}
	
	for(int i=0; i<s; ++i){
		ea.addEdge(n+m+i, target, limits[i], 0);
	}

	
	successive_shortest_path_nonnegative_weights(G, src, target);
    int cost = find_flow_cost(G);
	
	int flow = 0;
    // Iterate over all edges leaving the source to sum up the flow values.
    OutEdgeIt e, eend;
    for(tie(e, eend) = out_edges(vertex(src, G), G); e != eend; ++e) {
        flow += capacitymap[*e] - rescapacitymap[*e];
    }
	
	cout << flow << " " << (-1)*(cost-(w*flow)) << endl;
	
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}

