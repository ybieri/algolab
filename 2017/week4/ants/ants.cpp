// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <map>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>
// Namespaces
using namespace std;
using namespace boost;


// BGL Graph definitions
// =====================
// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef adjacency_list<vecS, vecS, undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices	
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).	
typedef graph_traits<Graph>::edge_iterator		EdgeIt;		// to iterate over all edges
typedef graph_traits<Graph>::out_edge_iterator		OutEdgeIt;	// to iterate over all outgoing edges of a vertex
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t


void do_testcases(){
	int V, E, s, a, b;
	cin >> V >> E >> s >> a >> b;

	
	Graph G(V);	// creates an empty graph on n vertices
	WeightMap weightmap = get(edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38

		int w, temp;


	for (int i = 0; i < E; ++i) {
		Edge e;	bool success;
		Vertex u, v;
		cin >> u >> v;
		
		tie(e, success) = add_edge(u, v, G);	// Adds edge from u to v. If parallel edges are allowed, success is always true.
		
		w = INT_MAX;
		for(int j=0; j<s; ++j){
			cin >> temp;
			w = min(w, temp);
			//cout << "weight " << w << " temp " << temp << endl;
		}
		
		weightmap[e] = w;			// Otherwise it is false in case of failure when the edge is a duplicate
		assert(source(e, G) == u && target(e, G) == v);	// This shows how to get the vertices of an edge
	}
	//hives
	for(int j=0; j<s; ++j){
	 int h; cin >> h;
	}
	
	// Dijkstra shortest paths
	// =======================
	vector<Vertex> predmap(V);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	dijkstra_shortest_paths(G, a, 															// We MUST provide at least one of the two maps
		predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	// distance map as Named Parameter
	

	cout << distmap[b] << endl;;
		
}

void do_testcases2(){
	int V, E, s, a, b;
	cin >> V >> E >> s >> a >> b;

	//cout << "after reading init" << endl;
	Graph G(V);
	map<Edge,int> Weights[s];

	for (int i = 0; i < E; ++i) {
		Edge e;	bool success;
		Vertex u, v;
		cin >> u >> v;
		tie(e, success) = add_edge(u, v, G);					// Add edge
		assert(source(e, G) == u && target(e, G) == v);	// This shows how to get the vertices of an edge
		for(int j=0; j<s; ++j){
			int w; cin >> w;
			Weights[j][e] = w;
		}
	}

	//cout << "after constructing graph" << endl;

	//hives
	vector<int> hive(s);
	for(int i=0; i<s; ++i){
		int hivestart; 
		cin >> hivestart;
		hive[i] = hivestart;
	}
	//cout << "s " << s  << endl;
	
	
	//create graph with all private networks. Save only lowest weight
    Graph Network(V);
    WeightMap network_weights = get(edge_weight, Network);
	
	// find graph for each species
	for(int species = 0; species < s; ++species){
		map<int, int> visited; //vertices we have visited
		map<int,Edge> current_edges; //edges we want to follow, sorted by their weight
		int positively_visited = 1;
		int start = hive[species];
		
		visited[start] = 1;
		
		// OutEdgeIterators
		// ================
		OutEdgeIt oebeg, oeend;
		for (tie(oebeg, oeend) = out_edges(start, G); oebeg != oeend; ++oebeg) {
			Vertex v = target(*oebeg, G);	// source(*oebeg, G) is guaranteed to be u, even in an undirected graph.
			//cout << "init target " << v << endl;
			Edge e = *oebeg;
			int w = Weights[species][e];
			current_edges[w] = e; // add Edge e to current edges
		}
		//now we have added all outgoing edges.
		
		//select lowest one, check that not source and target visited
		while(current_edges.size() > 0 && positively_visited < V){
			
			int u, v, w;
			map<int, Edge>::iterator it;
			//find edge where u,v have not been visited before
			do{
				//get edge with lowest weight
				it = current_edges.begin();
				w = it->first;
				Edge e = it->second; 
				u = source(e, G);
				v = target(e, G);
				//cout << "edge u, v we look at " << u << " " << v << endl;
		
				int start;
				if(visited[u] && visited[v]){
					current_edges.erase(it);
				}
			}while(visited[u] && visited[v] && it != current_edges.begin());
		
			if(visited[u]){
				start = v;
			}else{
				start = u;
			}
			
			//cout << "next vertex " << start << endl;
			
			// add outgoing edges from (u,v) if target is not already visited
			OutEdgeIt oebeg, oeend;
			for (tie(oebeg, oeend) = out_edges(start, G); oebeg != oeend; ++oebeg) {
				Vertex v = target(*oebeg, G);	// source(*oebeg, G) is guaranteed to be u, even in an undirected graph.
				//cout << "target of adding " << v << endl;
				//cout << "visited " << visited[v] << endl;
				Edge e = *oebeg;
				//check if already visited
				if(visited[v] == 0){
					int wgt = Weights[species][e];
					current_edges[wgt] = e; // add Edge e to current edges
				}
				
			}
			
			visited[start] = 1;
			++positively_visited;
			current_edges.erase(it);
			
			//check if edge already exists and if weight is lower
			Edge addedEdge;
			bool exists;
			tie(addedEdge, exists) = edge(u, v, Network);
			if(!exists){
				tie(addedEdge, tuples::ignore) = add_edge(u, v, Network);
				network_weights[addedEdge] = w;
			}else{
				if(w < network_weights[addedEdge])
					network_weights[addedEdge] = w;
			}
		}//end while for one species
	}//end for all species

	// Dijkstra shortest paths
	// =======================
	vector<Vertex> predmap(V);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	dijkstra_shortest_paths(Network, a, 															// We MUST provide at least one of the two maps
		predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	// distance map as Named Parameter
	

	cout << distmap[b] << endl;;
}

void do_testcases3(){
	int V, E, s, a, b;
	cin >> V >> E >> s >> a >> b;

	Graph G(V);
	WeightMap weightmap = get(edge_weight, G);	// start by defining property maps for all interior properties defined in Lines 37, 38
	map<Edge,int> Weights[s];
	vector<vector<Edge> > weightmapvector(s, vector<Edge>(E));

	for (int i = 0; i < E; ++i) {
		Edge e;	bool success;
		Vertex u, v;
		cin >> u >> v;
		tie(e, success) = add_edge(u, v, G);					// Add edge
		assert(source(e, G) == u && target(e, G) == v);	// This shows how to get the vertices of an edge
		for(int j=0; j<s; ++j){
			int w; cin >> w;
			weightmapvector[j][e] = w;
			Weights[j][e] = w;
		}
	}


	//hives
	vector<int> hive(s);
	for(int i=0; i<s; ++i){
		int hivestart; 
		cin >> hivestart;
		hive[i] = hivestart;
	}
	
	
	//create graph with all private networks. Save only lowest weight
    Graph Network(V);
    WeightMap network_weights = get(edge_weight, Network);
	
	// find graph for each species
	for(int species = 0; species < s; ++species){
		
		
		// Kruskal minimum spanning tree
		// =============================
		vector<Edge>	mst; // We must use this vector to store the MST edges (not as a property map!)
		// We can use the following vectors as Exterior Property Maps if we want to access additional information computed by Union-Find:	
		vector<Vertex>	kruskalpredmap(V);	// Stores predecessors needed for Union-Find (NOT the MST!)
		vector<int>	rankmap(V);		// Stores ranks needed for Union-Find
		kruskal_minimum_spanning_tree(G, back_inserter(mst),
				weight_map(make_iterator_property_map(weightmapvector[species].begin(), get(edge_weight, G))).
				rank_map(make_iterator_property_map(rankmap.begin(), get(vertex_index, G))).
				predecessor_map(make_iterator_property_map(kruskalpredmap.begin(), get(vertex_index, G))));											// old primpredmap gets reset first!	

		EdgeIt ebeg, eend;
		vector<Edge>::iterator	mstbeg, mstend = mst.end();
		for (mstbeg = mst.begin(); mstbeg != mstend; ++mstbeg) {
			Vertex u = source(*mstbeg, G);
			Vertex v = target(*mstbeg, G);
			int w = weightmap[*mstbeg];
			Edge addedEdge;
			bool exists;
			tie(addedEdge, exists) = edge(u, v, Network);
			if(!exists){
				tie(addedEdge, tuples::ignore) = add_edge(u, v, Network);
				network_weights[addedEdge] = w;
			}else{
				if(w < network_weights[addedEdge])
					network_weights[addedEdge] = w;
			}
			
			
		}
	}//end for all species

	// Dijkstra shortest paths
	// =======================
	vector<Vertex> predmap(V);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	vector<int> distmap(V);		// We will use this vector as an Exterior Property Map: Vertex -> Distance to source
	dijkstra_shortest_paths(Network, a, 															// We MUST provide at least one of the two maps
		predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));	// distance map as Named Parameter
	

	cout << distmap[b] << endl;;
}


int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases3();
	return 0;
}
