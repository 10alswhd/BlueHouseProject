#include <iostream>

#include <vector>



using namespace std;



#define MAX 10004



typedef pair<int,int> pii;





class Graph{

	int V;

	vector<int> adj[MAX];

	vector<pii> bridges;



	void dfs(int u, vector<int> &parent, vector<pii> &times, vector<int> &visited);



public:

	Graph(int V){

		this->V = V;

	}



	void add_edge(int u, int v){

		adj[u].push_back(v);

		adj[v].push_back(u);

	}



	void find_bridges(){

		vector<int> visited(V+1, false);

		vector<pii> times(V+1);

		vector<int> parent(V+1, -1);



		for(int i=1;i<=V;i++){

			if(visited[i]==false){

				dfs(i, parent, times, visited);

			}

		}

	}



	void print_bridges(){

		if(bridges.size()==0){

			cout<<"No bridges"<<endl;

		}

		else{

			for(int i=0;i<bridges.size();i++){

				cout<<bridges[i].first<<"<--->"<<bridges[i].second<<endl;

			}

		}

	}



};



void Graph::dfs(int u, vector<int> &parent, vector<pii> &times, vector<int> &visited){

	static int tick = 0;

	tick++;

	times[u].first = tick;  // discovery time

	times[u].second = tick;  // min time



	visited[u] = true;



	for(int i=0;i<adj[u].size();i++){

		int v = adj[u][i];



		if(visited[v]==false){

			parent[v] = u;

			dfs(v, parent, times, visited);



			times[u].second = min(times[u].second, times[v].second);



			if(times[v].second > times[u].first){ // if min time to reach v is greater that the dicovery time of u

				bridges.push_back(make_pair(u, v));



			}

		}

		else if(v!=parent[u]){

			times[u].second = min(times[u].second, times[v].first); 

		}

	}

}





int main(){

	Graph *graph = new Graph(5);



	graph->add_edge(2,1);

	graph->add_edge(1,3);

	graph->add_edge(3,2);

	graph->add_edge(1,4);

	graph->add_edge(4,5);



	graph->find_bridges();



	graph->print_bridges();

}
