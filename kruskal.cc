#include <iostream>

#include <vector>

#include <algorithm>



using namespace std;



typedef pair<int, pair<int,int> > EDGE;  // <weight, <src, dest> >

typedef pair<int,int> pii;



class Graph{

	int V; // number of nodes;

	int E; // number of edges;



	vector<EDGE> edges;

	vector<EDGE> mst;

	int mst_weight;



public:

	Graph(int V){

		this->V = V;

		E = 0;

		mst_weight = -1; // indicating no mst possible, graph not connected

	}



	void add_edge(int u, int v, int weight){

		edges.push_back(make_pair(weight, make_pair(u,v)));

		E++;

	}



	int find(vector<pii> &subsets, int i){

		if(subsets[i].first != i){

			subsets[i].first = find(subsets, subsets[i].first);

		}



		return subsets[i].first;

	}



	void Union(vector<pii> &subsets, int u, int v){

		int xroot = find(subsets, u);

		int yroot = find(subsets, v);



		if(subsets[xroot].second > subsets[yroot].second){

			subsets[yroot].first = xroot;

		}

		else if(subsets[yroot].second > subsets[xroot].second){

			subsets[xroot].first = yroot;

		}

		else{

			subsets[xroot].first = yroot;

			subsets[yroot].second +=1;

		}

	}



	void kruskal(){

		vector<pii> subsets;

		for(int i=0;i<=V;i++){

			subsets.push_back(make_pair(i,i));

		}



		sort(edges.begin(), edges.end());



		int x, y;

		for(int i=0;i<edges.size();i++){

			int x = find(subsets, edges[i].second.first);

			int y = find(subsets, edges[i].second.second);

			int weight = edges[i].first;



			if(x!=y){

				Union(subsets, x,y);

				mst.push_back(edges[i]);

			}

		}

	}



	void print_mst(){

		kruskal();



		if(mst.size()!=V-1){

			cout<<"graph is not connected"<<endl;

		}

		else{

			mst_weight = 0;

			for(int i=0;i<mst.size();i++){

				cout<<mst[i].second.first<<"--"<<mst[i].second.second<<"   "<<mst[i].first<<endl;

				mst_weight += mst[i].first;

			}



			cout<<"total weight: "<<mst_weight<<endl;

		}

	}







};





int main(){

	int x, y, weight;

	int nodes, edges;



	cin>>nodes>>edges;



	Graph *graph = new Graph(nodes);



	for(int i=0;i<edges;i++){

		cin>>x>>y>>weight;

		graph->add_edge(x,y, weight);

	}



	graph->print_mst();



	return 0;



}
