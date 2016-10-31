#include <iostream>

#include <vector>

#include <queue>



using namespace std;



#define MAX 10000



typedef pair<int,int> pii;

// first = disc_time of the node.

// second = min_time to reach the node



class Graph{

	int V;

	vector<int> adj[MAX];

	vector<int> ap;



	void dfs(int u, vector<pii> &tme, vector<int> &seen, vector<int> &parent);



public:



	Graph(int V){

		this->V = V;

		ap.resize(V+1, false);

	}



	void add_edge(int u, int v){

		adj[u].push_back(v);

		adj[v].push_back(u);

	}



	// articulation point finder

	void AP(){

		vector<pii> tme(V+1);

		vector<int> seen(V+1, false);

		vector<int> parent(V+1, -1);



		for(int i=1;i<=V;i++){

			if(seen[i]==false){

				dfs(i, tme, seen, parent);

			}

		}



		for(int i=1;i<=V;i++){

			if(ap[i]==true)

				cout<<i<<" ";

		}

		cout<<endl;



	}



	

};





void Graph::dfs(int u, vector<pii> &tme, vector<int> &seen, vector<int> &parent){

	static int tick = 0;

	tick++;

	tme[u].first = tick;

	tme[u].second = tick;



	int v;



	seen[u] = true;



	int children = 0;



	for(int i=0;i<adj[u].size();i++){

		v = adj[u][i];



		if(seen[v]==false){

			children++;

			parent[v] = u;

			dfs(v, tme, seen, parent);



			tme[u].second = min(tme[u].second, tme[v].second);



			if(parent[u]==-1 && children>=2){

				ap[u] = true;

			}



			if(parent[u]!=-1 && tme[v].second >= tme[u].first){

				ap[u] = true;

			}



		}

		else if(v!=parent[u]){

			tme[u].second = min(tme[v].first, tme[u].second);

		}

	}		

}





int main(){

	Graph *graph = new Graph(5);



	graph->add_edge(2,1);

	graph->add_edge(1,3);

	graph->add_edge(3,1);

	graph->add_edge(1,4);

	graph->add_edge(4,5);



	graph->AP();





}
