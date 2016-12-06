#include <iostream>
#include <vector>
#include <list>
#include <queue>          // std::priority_queue
#include <algorithm>
#include<stdlib.h>
using namespace std;

struct pQ
{
	list<int> path;
	int cost;
	bool operator>(const pQ& rhs) const
	{
		return cost > rhs.cost;
	}
};

class mycomparison
{
public:
	bool operator() (pQ p1, pQ p2) const
	{
		//by default comparing the integer values
		return (p1>p2);
	}
};

class Graph
{
	int V;
	vector<int> *adj;
	vector<int> *wgt;
public:
	Graph(int V);
	void addEdge(int v, int w, int wgt);
	void UCF(int s, int t);
	void displayPath(struct pQ f);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<int>[V];
	wgt = new vector<int>[V];
}

void Graph::addEdge(int v, int w, int wt) {
	adj[v].push_back(w);
	wgt[v].push_back(wt);

	//non-directed graph
	// adj[w].push_back(v);
	// wgt[w].push_back(wt);
}

void Graph::UCF(int s, int t)
{
	int current=0, pos=0;
	typedef priority_queue<pQ,vector<pQ>,mycomparison> mypq_type;
	mypq_type pq;

	pQ vstart;

	vstart.path.push_back(s);
	vstart.cost = 0;

	vector<int>::iterator i;
	pq.push(vstart);

	while(!pq.empty())
	{
		pQ currentPQ, tempPQ;
		current = pq.top().path.back();
		currentPQ = pq.top();
		// cout<<current<<" "<<currentPQ.cost<<endl;
		pq.pop();
		if(current == t)
		{
			cout<<"found"<<endl;
			displayPath(currentPQ);
			exit(0);
		}
		else{
			for (i = adj[current].begin(); i != adj[current].end(); ++i)
			{
				tempPQ = currentPQ;
				tempPQ.path.push_back(*i);
				pos = find(adj[current].begin(), adj[current].end(), *i) - adj[current].begin();
				tempPQ.cost += wgt[current].at(pos);
				pq.push(tempPQ);
			}
		}
	}
}

void Graph::displayPath(struct pQ p)
{
  list<int>::iterator i;
	cout<<"Path: ";
  for (i = p.path.begin(); i != p.path.end(); ++i)
  {
    cout<<"->"<<*i;
  }
	cout<<endl;
  cout<<"Pathlength: "<<p.cost;
}

int main()
{
	int n,e, a, b, c;
	int vstart = 0, vend = 0;
	cout<<"No. of vertices:";
	cin>>n;
	cout<<"No. of edges:";
	cin>>e;
	Graph g(6);
	cout<<"Enter the list of edges in the format : v1 v2 weight:";
	for(int i = 0; i<e; i++)
	{
		cin>>a>>b>>c;
		g.addEdge(a, b, c);
	}
	cout<<"Enter the start vertex:";
	cin>>vstart;
	cout<<"Enter the end vertex:";
	cin>>vend;

	g.UCF(vstart, vend);
	return 0;
}


/*
g.addEdge(0, 1, 1);
g.addEdge(0, 5, 12);
g.addEdge(1, 2, 3);
g.addEdge(1, 3, 1);
g.addEdge(2, 4, 3);
g.addEdge(3, 4, 1);
g.addEdge(3, 5, 2);
g.addEdge(4, 5, 3);
*/
