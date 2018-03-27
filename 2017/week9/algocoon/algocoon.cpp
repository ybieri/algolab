#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

// Boost includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
// Namespaces
using namespace std;
using namespace boost;
// BGL typedefs
typedef adjacency_list_traits<vecS, vecS, directedS>    Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, int,
        property<edge_residual_capacity_t, int,
            property<edge_reverse_t, Traits::edge_descriptor> > > >     Graph;
typedef graph_traits<Graph>::edge_descriptor                    Edge;
typedef graph_traits<Graph>::vertex_descriptor                  Vertex;
typedef graph_traits<Graph>::out_edge_iterator                  OutEdgeIt;
typedef property_map<Graph, edge_capacity_t>::type              EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type     ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type               ReverseEdgeMap;

// Custom Add Edge for flow problems
void addEdge(int from, int to, int capacity, EdgeCapacityMap &capacitymap,
                                              ReverseEdgeMap &revedgemap, Graph &G) {
        Edge e, reverseE;
        bool success;
        tie(e, success)         = add_edge(from, to, G);
        tie(reverseE, success)  = add_edge(to, from, G);
        capacitymap[e]          = capacity;
        capacitymap[reverseE]   = 0;
        revedgemap[e]           = reverseE;
        revedgemap[reverseE]    = e;
}

// Function solving a single testcase
void testcases() {
        int n, m;
        cin >> n >> m;
// Number of figures and limbs

// Build Graph
        Graph G(n);
        EdgeCapacityMap capacitymap = get(edge_capacity, G);
        ReverseEdgeMap revedgemap = get(edge_reverse, G);
        ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
// Read edges
        for (int i = 0; i < m; ++i) {
                int from, to, c;
                cin >> from >> to >> c;
                addEdge(from, to, c, capacitymap, revedgemap, G);
        }
// Find a min cut via maxflow
        int minmaxflow = INT_MAX;
        pair<int, int>  sinksource = make_pair(0,1);
// Vertex i in my group of figures
        for (int i = 0; i < n; ++i) {
                int maxflow = push_relabel_max_flow(G, i, (i+1)%n);
                if (maxflow < minmaxflow) {
                        sinksource = make_pair(i,(i+1)%n);
                        minmaxflow = maxflow;
                }
        }
// Find all figures
        minmaxflow = push_relabel_max_flow(G, sinksource.first, sinksource.second);
        vector<int> vis(n, false);
        vis[sinksource.first] = true;
        std::queue<int> Q;
        Q.push(sinksource.first);
        while (!Q.empty()) {
                const int u = Q.front();
                Q.pop();
                OutEdgeIt ebeg, eend;
                for (tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
                        const int v = target(*ebeg, G);
                        if (rescapacitymap[*ebeg] == 0 || vis[v]) continue;
                        vis[v] = true;
                        Q.push(v);
                }
        }
// Output
        cout << minmaxflow << endl << count(vis.begin(), vis.end(), true);
        for (int i = 0; i < n; ++i) {
                if (vis[i]) cout << " " << i;
        }
        cout << endl;
}


// Function looping over the testcases
int main() {
        ios_base::sync_with_stdio(false);
        int T;  cin >> T;
        for ( ; T > 0; --T)     testcases();
        return 0;
}
