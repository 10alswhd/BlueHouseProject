#include <iostream>

#include <stdio.h>

#include <string.h>

#include <vector>

#include <algorithm>



using namespace std;



#define pb(b) push_back(b)

#define len(s) s.length()

#define size(v) v.size()

#define vi vector<int> 

#define vll vector<long long int>

#define vii vector<pair<int,int> >



typedef long long int ll;



class Graph{

	int V;

	int E;



	vii edges;



public:

	Graph(int V, int E){

		this->V = V;

		this->E = E;

	}



	void add_edge(int u, int v){

		edges.pb(make_pair(u,v));

	}



	int find(vii &subsets, int i){

		if(subsets[i].first!=i)

			subsets[i].first = find(subsets, subsets[i].first);

		return subsets[i].first;

	}



	void Union(vii &subsets, int x, int y){

		int _x = find(subsets, x);

		int _y = find(subsets, y);



		if(subsets[_x].second<subsets[_y].second){

			subsets[_x].first = _y;

		}

		else if(subsets[_x].second>subsets[_y].second){

			subsets[_y].first = _x;

		}

		else{

			subsets[_x].first = _y;

			subsets[_y].second += 1;

		}

	}



	int isCyclic(){

		vii subsets(V);



		for(int v=0;v<V;v++){

			subsets[v] = make_pair(v,0);

		}



		for(int i=0;i<E;i++){

			int x = find(subsets, edges[i].first);

			int y = find(subsets, edges[i].second);



			if(x==y)

				return true;



			Union(subsets, x, y);

		}



		return false;

	}



};





int main(){



	Graph *graph = new Graph(3,3);

	graph->add_edge(0,1);

	graph->add_edge(1,2);

	graph->add_edge(0,2);



	if(graph->isCyclic()){

		cout<<"there is a cycle in the graph"<<endl;

	}

	else{

		cout<<"The graph does not contain cycle"<<endl;

	}

	



}
