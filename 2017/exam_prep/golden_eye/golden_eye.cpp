
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <boost/graph/adjacency_list.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <boost/graph/connected_components.hpp>
using namespace std;
using namespace boost;
using namespace CGAL;
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




typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;



#define REP(i,n) for(int i=0; i<(int)n; ++i)
#define DEBUG(x) //cout << #x << " = " << x << endl


void do_testcases(){
	double n, m; double power; // jammers, missions, power
	cin >> n >> m >> power;
	
	map<Point, double> jammers;
	vector<Point> jam(n);
	REP(i, n){ 
		Point p; cin >> p;
		jammers[p] = i;
		jam[i] = p;
	}
	
	vector<pair<Point,Point> > missions(m);
	
	REP(i,m){
		Point u, v; cin >> u >> v;
		missions[i] = make_pair(u,v);
	}
	
	
	// construct triangulation
	Triangulation t;
	t.insert(jam.begin(), jam.end());

	vector<double> start_dist_to_nearest_jammer(m);
	vector<double>   end_dist_to_nearest_jammer(m);
	vector<Point> start_nearest_jammer(m);
	vector<Point> end_nearest_jammer(m);

	//get nearest jammer for every mission start/end point
	REP(i,m){
		Point sp = t.nearest_vertex(missions[i].first)->point();
		Point ep = t.nearest_vertex(missions[i].second)->point();
		start_nearest_jammer[i] = sp;
		end_nearest_jammer[i] = ep;
		start_dist_to_nearest_jammer[i] = CGAL::squared_distance(sp, missions[i].first);
		end_dist_to_nearest_jammer[i] = CGAL::squared_distance(ep, missions[i].second);
	}


	// get all possible intersections between jammers n^2
	vector<double> possible_powers;
	REP(i,n){
		REP(j,n){
			possible_powers.push_back(CGAL::squared_distance(jam[i], jam[j]));
		}
	}
	REP(i,m){
		possible_powers.push_back(4*start_dist_to_nearest_jammer[i]);
		possible_powers.push_back(4*end_dist_to_nearest_jammer[i]);
	}
	possible_powers.push_back(power);
	sort(possible_powers.begin(), possible_powers.end());
	
	
	vector<double> sqdistEMST;
	vector<Point> sqdist_p1;
	vector<Point> sqdist_p2;
	for(Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
		Point p1 = e->first->vertex((e->second + 1) % 3)->point();
		Point p2 = e->first->vertex((e->second + 2) % 3)->point();
		sqdist_p1.push_back(p1);
		sqdist_p2.push_back(p2);
		sqdistEMST.push_back(CGAL::squared_distance(p1, p2));
	}
	int powerindex;
	REP(i, possible_powers.size()){
		if(possible_powers[i] == power){
			powerindex = i; break;
		}
	}
	
	
	//1 ====================
	Graph G(n);
	// put all edges that are shorter than power in the graph
	REP(i,sqdistEMST.size()){
		if(sqdistEMST[i] <= power){
			add_edge(jammers[sqdist_p1[i]], jammers[sqdist_p2[i]], G);
		}
	}

	vector<int> componentmap(n);
	int initcounter = 0;
	int ncc = connected_components(G, make_iterator_property_map(componentmap.begin(), get(vertex_index, G))); 
	REP(i,m){
		if(start_dist_to_nearest_jammer[i] > (power/4) || end_dist_to_nearest_jammer[i] > (power/4)){
			cout << "n"; continue;
		}	
		if(componentmap[jammers[start_nearest_jammer[i]]] == componentmap[jammers[end_nearest_jammer[i]]]){ 
			cout << "y";  
			++initcounter;
		}
		else cout << "n";
	}
	cout << endl;
	// ==================== 1	
	// 2 ====================
	
	int l;
	if(initcounter < m) l = powerindex;
	else l = 0;
	
	int r=possible_powers.size();
	while(l!=r){
		int middle = l+(r-l)/2;

		Graph G(n);
		// put all edges that are shorter than power in the graph
		REP(i,sqdistEMST.size()){
			if(sqdistEMST[i] <= possible_powers[middle]){
				add_edge(jammers[sqdist_p1[i]], jammers[sqdist_p2[i]], G);
			}
		}

		vector<int> componentmap(n);
		int counter = 0;
		int ncc = connected_components(G, make_iterator_property_map(componentmap.begin(), get(vertex_index, G))); 
		REP(i,m){
			if(start_dist_to_nearest_jammer[i] > (possible_powers[middle]/4) || end_dist_to_nearest_jammer[i] > (possible_powers[middle]/4)){
				continue;
			}	
			if(componentmap[jammers[start_nearest_jammer[i]]] == componentmap[jammers[end_nearest_jammer[i]]]){
				 ++counter;
			}
		}		
		if(counter == m)
			r=middle;
		else
			l=middle+1;
	}
	cout << possible_powers[l] << endl;
	// ==================== 2
	// 3 ====================


	r = powerindex;
	l=0;
	
	while(l!=r){
		int middle = l+(r-l)/2;
		
		Graph G(n);
		// put all edges that are shorter than power in the graph
		REP(i,sqdistEMST.size()){
			if(sqdistEMST[i] <= possible_powers[middle]){
				add_edge(jammers[sqdist_p1[i]], jammers[sqdist_p2[i]], G);
			}
		}

		vector<int> componentmap(n);
		int counter = 0;
		int ncc = connected_components(G, make_iterator_property_map(componentmap.begin(), get(vertex_index, G))); 
		REP(i,m){
			if(start_dist_to_nearest_jammer[i] > (possible_powers[middle]/4) || end_dist_to_nearest_jammer[i] > (possible_powers[middle]/4)){
				continue;
			}	
			if(componentmap[jammers[start_nearest_jammer[i]]] == componentmap[jammers[end_nearest_jammer[i]]]){
				 ++counter;
			}
		}		
		if(counter == initcounter)
			r=middle;
		else
			l=middle+1;
	}
		
	cout << possible_powers[l] << endl;
	// ==================== 3
}


int main(){
	ios_base::sync_with_stdio(false);
	cout << fixed << setprecision(0);
	int t; cin >> t;
	while(t--) do_testcases();
	return 0;
}
