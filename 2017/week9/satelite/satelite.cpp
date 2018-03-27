#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>

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
		//cout << "adding edge from to " << from << " " << to << endl;
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





void bfs(int src, vector<bool>& visited, Graph& G){
	// BFS to find vertex set S
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	visited[src] = true; // Mark the source as visited
	Q.push(src);
	while(!Q.empty()){
		int u = Q.front();
		visited[u] = true;
		Q.pop();
		OutEdgeIt ebeg, eend;
		for(tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = target(*ebeg, G);
			//cout << "out edge v is " << v << endl;
			// follow directed edges and add non visited vertices
			if(!visited[v]) 
				Q.push(v);
		}
	}
}


void do_testcases() {
	int g, s, l;
	cin >> g >> s >> l;
	// build Graph
	Graph G(g+s);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder ea(G, capacitymap, revedgemap);

	Vertex src = add_vertex(G);
	Vertex trg = add_vertex(G);

    Graph GR(g+s); //residual graph
    Vertex gr_src = add_vertex(GR);
	Vertex gr_trg = add_vertex(GR);
	
	vector<pair<int, int> > edgesG;

	//add edges from source to all ground stations
	for(int i=0; i<g; ++i){
		ea.addEdge(src, i, 1);
		edgesG.push_back(make_pair(src, i));
	}
	//add edges from all satelites to target/sink
	for(int i=0; i<s; ++i){
		ea.addEdge(g+i, trg, 1);
		edgesG.push_back(make_pair(g+i, trg));
	}
	//add all edges between ground and satelites
	
	for(int i=0; i<l; ++i){
		int u, v; cin >> u >> v;
		ea.addEdge(u, g+v, 1);
		edgesG.push_back(make_pair(u, g+v));
	}

	long flow = push_relabel_max_flow(G, src, trg);

	for(int i=0; i<edgesG.size(); ++i){
		int u = edgesG[i].first;
		int v = edgesG[i].second;	
		Edge e; bool b;
		tie(e, b) = edge(u, v, G);
		if(rescapacitymap[e] == 0)
			add_edge(v, u, GR);
		else
			add_edge(u, v, GR);
	} 
    

	vector<bool> visited(g+s+2, false); // visited flags
		
	bfs(gr_src, visited, GR);

	vector<int> visited_sats;
	vector<int> visited_grounds;

	for(int i=0; i<s; ++i){
		if(visited[g+i])
			visited_sats.push_back(i);
	}
	
	for(int i=0; i<g; ++i){
		if(!visited[i])
			visited_grounds.push_back(i);
	}

	cout << visited_grounds.size() << " " << visited_sats.size() << endl;
	
	for(int i=0; i<visited_grounds.size(); ++i)
		cout << visited_grounds[i] << " ";
	for(int i=0; i<visited_sats.size(); ++i)
		cout << visited_sats[i] << " ";

}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}

