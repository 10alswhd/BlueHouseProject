#include <iostream>

#include <vector>

#include <queue>



using namespace std;



#define MAX 100004



typedef pair<int,int> pii;

typedef pair<int, pair<int,int> > EDGE;







class Graph{

	int V;



	vector<pii> adj[MAX];



public:



	Graph(int V){

		this->V = V;

	}



	void add_edge(int u, int v, int weight){

		adj[u].push_back(make_pair(weight, v));

		adj[v].push_back(make_pair(weight, u));

	}



	int prims(int start){



		priority_queue<pii, vector<pii>, greater<pii> > Q;



		vector<int> visited(V+1, false);



		pii p;



		int u, v, cost;

		int minCost = 0;



		Q.push(make_pair(0, start));



		while(!Q.empty()){

			p = Q.top();

			Q.pop();



			u = p.second;



			if(visited[u]==true)

				continue;



			visited[u] = true;



			minCost += p.first;



			for(int i=0;i<adj[u].size();i++){

				v = adj[u][i].second;

				if(visited[v]==false)

					Q.push(adj[u][i]);

			}

		}





		return minCost;

	}







};





int main(){

	int nodes, edges, x, y;

	int weight, minCost;



	cin>>nodes>>edges;



	Graph *graph = new Graph(nodes);



	for(int i=0;i<edges;i++){

		cin>>x>>y>>weight;

		graph->add_edge(x,y, weight);

	}



	minCost = graph->prims(1);



	cout<<minCost<<endl;



	return 0;

}
