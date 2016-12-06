#include<bits/stdc++.h>

using namespace std;

vector< vector<int> >graph;
vector<bool>vis;

void dfs(int s){
    vis[s]=true;
    cout<<s<<" ";
    for(int i=0;i<graph[s].size();i++){
        if(!vis[graph[s][i]]){
            dfs(graph[s][i]);
        }
    }
}

void bfs(int s){
    int t;
    queue<int>q;
    q.push(s);
    cout<<s<<" ";
    vis[s]=true;
    while(!q.empty()){
        t=q.front();
        q.pop();
        for(int i=0;i<graph[t].size();i++){
            if(!vis[graph[t][i]]){
                vis[graph[t][i]]=true;
                cout<<graph[t][i]<<" ";
                q.push(graph[t][i]);
            }
        }
    }
}

int main()
{
    int n,m,u,v,i,t,j,a;
    cout<<"Enter the no of vertices..";
    cin>>n;

    vis.resize(n+1);
    graph.resize(n+1);

    cout<<"\nEnter the number of edges...";
    cin>>m;
    cout<<"\nEnter the edges ...\n";
    for(i=1;i<=m;i++){
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Doing DFS Search...( Using Recursion )
    fill_n(vis.begin(),n+1,false);
    cout<<"\nThe DFS Traversal is ... ";
    dfs(1);

    // Doing BFS Search...( Using Queue )
    fill_n(vis.begin(),n+1,false);
    cout<<"\nThe BFS Traversal is ... ";
    bfs(1);

    return 0;
}

