#include <iostream>

#include <vector>

#include <queue>



using namespace std;



#define MAX 10004

#define INF 1000000007



typedef pair<int,int> pii;



class Graph{

	int V;



	vector<pii> adj[MAX];



	int src;



	vector<int> dist;





public:



	Graph(int V, int start){

		this->V = V;

		src = start;

		dist.resize(V+1, INF);

	}



	void add_edge(int u, int v, int weight){

		adj[u].push_back(make_pair(weight, v));

		adj[v].push_back(make_pair(weight, u));

	}





	void dijkstra(){

		vector<int> visited(V+1, false);



		int u, v, w;



		priority_queue<pii, vector<pii>, greater<pii> > Q;



		Q.push(make_pair(0,src));



		dist[src] = 0;



		pii p;



		while(!Q.empty()){

			p = Q.top();

			Q.pop();



			u = p.second;



			if(visited[u]==true)

				continue;



			visited[u] = true;



			for(int i=0;i<adj[u].size();i++){

				v = adj[u][i].second;

				w = adj[u][i].first;



				if(dist[v]>dist[u]+w){

					dist[v] = dist[u]+w;

					Q.push(make_pair(dist[v], v));

				}

			}

		}

	}



	void print_distances(){

		for(int i=1;i<=V;i++){

			cout<<dist[i]<<" ";

		}



		cout<<endl;

	}





};



int main(){

	int N, M;

	cin>>N>>M;

	int u, v, weight;



	Graph *graph = new Graph(N,1);



	for(int i=0;i<M;i++){

		cin>>u>>v>>weight;

		graph->add_edge(u, v, weight);	

	}



	graph->dijkstra();



	graph->print_distances();

}
