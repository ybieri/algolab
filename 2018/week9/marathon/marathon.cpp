// Includes
// ========
// STL includes
#include <iostream>
#include <bits/stdc++.h>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace boost;
using namespace std;

#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) ;// cerr << #x << " = " << (x) << endl;


// BGL Graph definitions
// ===================== 
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, Traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > Graph; // new!
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type      EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t >::type       EdgeWeightMap; // new!
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type       ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    Edge addEdge(int u, int v, long c, long w) {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w; // new!
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w; // new
        revedgemap[e] = rev_e; 
        revedgemap[rev_e] = e;
        return e;
    }
};

void do_testcases(){
    
    int n,m,s,f; cin >> n >> m >> s >> f;
    
    // Create Graph and Maps
    Graph G(n+1);
    EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
    EdgeWeightMap weightmap = boost::get(boost::edge_weight, G);
    ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
    ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);
    
    //special source vertex in front of s
    Vertex src = n;
    Vertex trg = f;
    
    //special vertex to source, weight 1, cost 0
    Edge srcEdge = eaG.addEdge(src, s, 1 , 0);
    
    REP(i,m){
		int a,b,c,d;
		cin >> a >> b >> c >> d;
		eaG.addEdge(a,b,c,d);
		eaG.addEdge(b,a,c,d);
	}
    
  
    // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights
    successive_shortest_path_nonnegative_weights(G, src, trg);
    long shortest_path = find_flow_cost(G);
    
    DEBUG(shortest_path)
    
    //binary search for max flow/runners with distance/cost = shortest path
    long l = 1;
    long r = 1;
    
    //exponential search
    while(true){
		r*=2;
		capacitymap[srcEdge] = r;
		OutEdgeIt e, eend;
		successive_shortest_path_nonnegative_weights(G, src, trg);
		long cost = find_flow_cost(G);
		long s_flow = 0;
		for(tie(e, eend) = out_edges(vertex(src,G), G); e != eend; ++e) {
			s_flow += capacitymap[*e] - rescapacitymap[*e];
		}
		if(shortest_path * s_flow != cost || r > s_flow){ //cost/capacity is larger than shortest path then we have a non shortest path
			break;
		}
	}
	
	DEBUG(r)
	while(l <= r){
		long m = l + (r-l)/2;
		DEBUG(l)
		DEBUG(r)
		DEBUG(m)
		capacitymap[srcEdge] = m;
		OutEdgeIt e, eend;
		successive_shortest_path_nonnegative_weights(G, src, trg);
		long cost = find_flow_cost(G);
		DEBUG(cost)
		long s_flow = 0;
		for(tie(e, eend) = out_edges(vertex(src,G), G); e != eend; ++e) {
			s_flow += capacitymap[*e] - rescapacitymap[*e];
		}
		DEBUG(s_flow)
		if(shortest_path * s_flow == cost && m <= s_flow){ //flow is still ok
			l = m+1;
		}else{
			r = m-1;
		}			
   }
   
   cout << l-1 << endl;
    
    
}

int main(){
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
