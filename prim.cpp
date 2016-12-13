//Edge.h
#pragma once
#include <string>
using namespace std;
class Edge
{
    string vt1;
    string vt2;
    int weight;
public:
    Edge(string vt1,string vt2,int height);
    bool Exist(string vt)const;
    bool Exist(string vt1, string vt2)const;
    string Other(string vt)const;
    void View()const;
    int GetWeight()const;
    string GetVt1()const;
    string GetVt2()const;
};
//Edge.cpp
#include "Edge.h"
#include <iostream>
using namespace std;
 
Edge::Edge(string vt1,string vt2,int weight)
{
    this->vt1 = vt1;
    this->vt2 = vt2;
    this->weight = weight;
}
bool Edge::Exist(string vt)const
{
    return (vt1 == vt)||(vt2==vt);
}
bool Edge::Exist(string vt1, string vt2)const
{
    return Exist(vt1) && Exist(vt2);
}
string Edge::Other(string vt)const
{
    if(vt1 == vt)
    {
        return vt2;
    }
    if(vt2 == vt)
    {
        return vt1;
    }
    return "";
}
void Edge::View()const
{
    cout<<"("<<vt1<<","<<vt2<<","<<weight<<")";
}
int Edge::GetWeight()const
{
    return weight;
}
 
string Edge::GetVt1()const
{
    return vt1;
}
string Edge::GetVt2()const
{
    return vt2;
}
//Graph.h
#pragma once
#include "Edge.h"
#include <iostream>
#include <vector>
using namespace std;
typedef vector<string> Vertexs;
typedef Vertexs::iterator VIter;
typedef Vertexs::const_iterator CVIter;
typedef vector<Edge *> Edges;
typedef Edges::iterator EIter;
typedef Edges::const_iterator CEIter;
 
class Graph
{
    Vertexs vertexs;
    Edges edges;
public:
    ~Graph(void);   
    bool AddVertex(string vt);
    bool Exist(string vt)const;
    bool AddEdge(string vt1, string vt2,int weight);//간선 추가
    bool Exist(string vt1,string vt2)const;
    void ViewNeighbors()const;
    void ViewNeighbor(string vt)const;   
    int GetVertexCount()const;
    Edges GetEdges()const;
    string GetFirstVertex()const;
};
//Graph.cpp
#include "Graph.h"
#include <string.h>
#include <algorithm>
 
Graph::~Graph(void)
{
    EIter seek = edges.begin();
    EIter last = edges.end();
    for(  ;seek != last; ++seek)
    {
        delete (*seek);//간선 소멸       
    }   
}
 
bool Graph::AddVertex(string vt)
{
    if(Exist(vt))
    {
        return false;
    }
    vertexs.push_back(vt);
    return true;
}
 
bool Graph::Exist(string vt)const
{
    return find(vertexs.begin(),vertexs.end(),vt) != vertexs.end();
}
 
bool Graph::AddEdge(string vt1, string vt2,int weight)//간선 추가
{
    if(Exist(vt1)&&Exist(vt2))
    {
        if(Exist(vt1,vt2))
        {
            return false;
        }
 
        CEIter seek = edges.begin();
        CEIter last = edges.end();
        for(  ;seek != last; ++seek)
        {
            if((*seek)->GetWeight()>=weight)
            {
                break;
            }
        }   
        edges.insert(seek,new Edge(vt1,vt2,weight));
        return true;
    }
    return false;
}
 
bool Graph::Exist(string vt1,string vt2)const
{
    CEIter seek = edges.begin();
    CEIter last = edges.end();
    for(  ;seek != last; ++seek)
    {
        if((*seek)->Exist(vt1,vt2))
        {
            return true;
        }
    }   
    return false;
}
 
void Graph::ViewNeighbors()const
{
    cout<<"=== 이웃 정점 ==="<<endl;
    CVIter seek = vertexs.begin();
    CVIter last = vertexs.end();
    for(   ;seek != last; ++seek)
    {
        cout<<(*seek)<<"의 이웃: ";
        ViewNeighbor(*seek);//i정점의 이웃 보여주기
    }
    cout<<endl;
}
 
void Graph::ViewNeighbor(string vt)const
{
    CEIter seek = edges.begin();
    CEIter last = edges.end();
    for(  ;seek != last; ++seek)
    {
        if((*seek)->Exist(vt))
        {
            cout<<(*seek)->Other(vt)<<" ";
        }
    }
    cout<<endl;
}
int Graph::GetVertexCount()const
{
    return vertexs.size();
}
Edges Graph::GetEdges()const
{
    return edges;
}
string Graph::GetFirstVertex()const
{
    if(vertexs.size()==0)
    {
        return "";
    }
    return vertexs[0];
}
//Prim.h
#pragma once
#include "Graph.h"
class Prim
{
    Graph *graph;   
    Edges edges;
public:
    Prim(Graph *graph);
    Graph * MakeMSTree();
private:
    bool SelectVertex(Graph *mstree);
    string IsGreedyVertex(Edge *edge,Graph *mstree)const;
};
//Prim.cpp
#include "Prim.h"
Prim::Prim(Graph *graph)
{
    this->graph = graph;
}
Graph *Prim::MakeMSTree()
{
    cout<<"프림 알고리즘 시작"<<endl;
    Graph *mstree = new Graph();
    string start = graph->GetFirstVertex();
    cout<<start<<endl;
    mstree->AddVertex(graph->GetFirstVertex());
    edges = graph->GetEdges();
    int vcnt = graph->GetVertexCount();
    while(mstree->GetVertexCount() < vcnt)
    {
        if(SelectVertex(mstree) == false)
        {
            break;
        }
    }
    if(mstree->GetVertexCount() <vcnt)
    {
        delete mstree;
        cout<<"고립 상태의 영역이 있어서 최소 신장 트리를 만들 수 없습니다."<<endl;
        return 0;       
    }   
    return mstree;
}
 
bool Prim::SelectVertex(Graph *mstree)
{
    EIter seek = edges.begin();
    EIter last = edges.end();
    for(   ;seek != last; ++seek)
    {
        string next_vtx = IsGreedyVertex(*seek,mstree);
        if(next_vtx != "")
        {
            string other =(*seek)->Other(next_vtx);
            int weight = (*seek)->GetWeight();
            cout<<"("<<other<<","<<next_vtx<<":"<<weight<<")"<<endl;
            mstree->AddVertex(next_vtx);
            mstree->AddEdge(next_vtx, other,weight);
            return true;
        }
    }
    return false;
}
 
string Prim::IsGreedyVertex(Edge *edge,Graph *mstree)const
{
    string vtx1 = edge->GetVt1();
    string vtx2 = edge->GetVt2();
    if(mstree->Exist(vtx1))
    {
        if(mstree->Exist(vtx2))
        {
            return "";
        }
        return vtx2;
    }
    if(mstree->Exist(vtx2))
    {
        return vtx1;
    }
    return "";
}
//Program.cpp
#include "Prim.h"
 
int main()
{
    Graph *graph = new Graph();//그래프 동적 생성
    graph->AddVertex("A");
    graph->AddVertex("B");
    graph->AddVertex("C");
    graph->AddVertex("D");
    graph->AddVertex("E");
    graph->AddVertex("F");
    graph->AddVertex("G");
    graph->AddVertex("H");
 
    graph->AddEdge("A","B",5);
    graph->AddEdge("A","D",3);
    graph->AddEdge("A","E",4);
    graph->AddEdge("B","D",3);
    graph->AddEdge("B","H",2);
    graph->AddEdge("C","D",3);
    graph->AddEdge("C","G",4);
    graph->AddEdge("D","H",5);
    graph->AddEdge("D","E",3);
    graph->AddEdge("D","F",3);
    graph->AddEdge("E","F",2);
    graph->AddEdge("F","G",6);
    graph->AddEdge("G","H",3);
    graph->ViewNeighbors();
   
    Prim *prim = new Prim(graph);
    Graph *mstree = prim->MakeMSTree();
    if(mstree)
    {
        cout<<"최소 신장 트리 만들기 성공"<<endl;
        mstree->ViewNeighbors();
        delete mstree;
    }
    delete prim;
    delete graph;
    return 0;
}
 
