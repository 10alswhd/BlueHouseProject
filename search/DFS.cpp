#include<bits/stdc++.h>

using namespace std;

vector< vector<int> >graph;
vector<bool>vis;

void dfsvisit(int s){
    vis[s]=true;
    cout<<s<<" ";
    for(int i=0;i<graph[s].size();i++){
        if(!vis[graph[s][i]]){
            dfsvisit(graph[s][i]);
        }
    }
}

int main()
{
    int n,i,t,j,a;
    cout<<"Enter the no of vertices..";
    cin>>n;

    vis.resize(n+1);
    graph.resize(n+1);


    for(i=1;i<=n;i++){
        cout<<"\nEnter the no of adjacent vertexes to the vertex "<<i<<endl;
        cin>>t;
        cout<<"\nEnter the vertices..";
        for(j=1;j<=t;j++){
            cin>>a;
            graph[i].push_back(a);
        }
    }


    // Doing DFS Search...( Using Recursion )
    fill_n(vis.begin(),n+1,false);
    cout<<"\nThe DFS Traversal done implicitly is ... ";
    for(i=1;i<=n;i++){
        if(!vis[i]){
            dfsvisit(i);
        }
    }

    return 0;
}
