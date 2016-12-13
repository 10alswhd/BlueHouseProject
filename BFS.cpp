
//Edge.h
#pragma once
class Edge
{
    int vt1;
    int vt2;
public:
    Edge(int vt1,int vt2);
    bool Exist(int vt)const;
    bool Exist(int vt1, int vt2)const;
    int Other(int vt)const;
    void View()const;
};
//Edge.cpp
#include "Edge.h"
#include <iostream>
using namespace std;
 
Edge::Edge(int vt1,int vt2)
{
    this->vt1 = vt1;
    this->vt2 = vt2;
}
bool Edge::Exist(int vt)const
{
    return (vt1 == vt)||(vt2==vt);
}
bool Edge::Exist(int vt1, int vt2)const
{
    return Exist(vt1) && Exist(vt2);
}
int Edge::Other(int vt)const
{
    if(vt1 == vt)
    {
        return vt2;
    }
    if(vt2 == vt)
    {
        return vt1;
    }
    return -1;
}
void Edge::View()const
{
    cout<<"("<<vt1<<","<<vt2<<")";
}
//Graph.h
#pragma once
#include "Edge.h"
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> Vertexs;
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
    bool AddVertex(int vt);
    bool Exist(int vt)const;
    bool AddEdge(int vt1, int vt2);//간선 추가
    bool Exist(int vt1,int vt2)const;
    void ViewNeighbors()const;
    void ViewNeighbor(int vt)const;
    Vertexs FindNeighbors(int vt);
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
bool Graph::AddVertex(int vt)
{
    if(Exist(vt))
    {
        return false;
    }
    vertexs.push_back(vt);
    return true;
}
bool Graph::Exist(int vt)const
{
    return find(vertexs.begin(),vertexs.end(),vt) != vertexs.end();
}
bool Graph::AddEdge(int vt1, int vt2)//간선 추가
{
    if(Exist(vt1)&&Exist(vt2))
    {
        if(Exist(vt1,vt2))
        {
            return false;
        }
        edges.push_back(new Edge(vt1,vt2));
        return true;
    }
    return false;
}
bool Graph::Exist(int vt1,int vt2)const
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
void Graph::ViewNeighbor(int vt)const
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
Vertexs Graph::FindNeighbors(int vt)
{
    Vertexs neighbors;
    EIter seek = edges.begin();
    EIter last = edges.end();
    for(  ;seek != last; ++seek)
    {
        if((*seek)->Exist(vt))
        {
            neighbors.push_back((*seek)->Other(vt));
        }
    }   
    return neighbors;
}
//Heuristic.h
#pragma once
#include "Graph.h"
#include <vector>
using namespace std;
typedef vector<int> Foots;
typedef Foots::iterator FIter;
typedef Foots::const_iterator CFIter;
 
class Heuristic;
typedef vector<Heuristic *> Heues;
typedef Heues::iterator HIter;
typedef Heues::const_iterator CHIter;
class Heuristic
{
    Graph *graph;   
    int goal;
    Foots foots;
public:
    Heuristic(Graph *graph, int start,int goal);   
    Heues EnumNext();
    bool IsGoal()const;
    void View()const;   
private:
    Heuristic(const Heuristic *bheu,int vt);
};
//Heuristic.cpp
#include "Heuristic.h"
#include <algorithm>
 
Heuristic::Heuristic(Graph *graph,int start,int goal)
{
    this->graph = graph;
    foots.push_back(start);
    this->goal = goal;
}
Heues Heuristic::EnumNext()
{
    Heues nheues;
    int last_foot = (*foots.rbegin());//가장 최근에 방문한 정점
    Vertexs neighbors = graph->FindNeighbors(last_foot);//마지막 방문 정점의 이웃하는 정점을 구함
    FIter seek = neighbors.begin();
    FIter last = neighbors.end();
    for(  ;seek != last; ++seek)
    {
        if(find(foots.begin(), foots.end(),*seek) == foots.end())//방문한 적이 없으면
        {
            nheues.push_back(new Heuristic(this,*seek));//*seek를 추가 방문하는 새로운 경험을 생성
        }           
    }
    return nheues;
}
bool Heuristic::IsGoal()const
{
    return (*foots.rbegin()) == goal;
}
void Heuristic::View()const
{
    cout<<"Foots: ";
    CFIter seek = foots.begin();
    CFIter last = foots.end();
    for(  ;seek != last; ++seek)
    {
        cout<<(*seek)<<" ";
    }
    cout<<endl;
}
 
Heuristic::Heuristic(const Heuristic *bheu,int vt)
{
    this->graph = bheu->graph;
    foots = bheu->foots;
    this->goal = bheu->goal;
 
    foots.push_back(vt);//vt를 방문한 행적에 추가
}


//Program.cpp
#include "Heuristic.h"
#include <queue>
using namespace std;
int main()
{
    Graph *graph = new Graph();//그래프 동적 생성
    for(int i = 0; i<8; i++)
    {
        graph->AddVertex(i);
    }
    graph->AddEdge(0, 1);//간선 추가
    graph->AddEdge(0, 2);//간선 추가
    graph->AddEdge(1, 2);//간선 추가
    graph->AddEdge(1, 3);//간선 추가
    graph->AddEdge(2, 4);//간선 추가
    graph->AddEdge(3, 6);//간선 추가
    graph->AddEdge(4, 5);//간선 추가
    graph->AddEdge(4, 6);//간선 추가
    graph->AddEdge(4, 7);//간선 추가
    graph->AddEdge(6, 8);//간선 추가
    graph->ViewNeighbors();
   
    queue<Heuristic *> hq;
   
    Heuristic *heu = new Heuristic(graph,0,8);//초기 경험 정보를 생성
    hq.push(heu);//큐에 보관
    while(hq.empty() == false) //반복(큐가 비어 있지 않다면)
    {
        heu = hq.front();//큐에서 경험 정보 꺼내옮
        hq.pop();
        //if(heu->IsGoal())//목적지에 도달하면
        //{
        //    cout<<"===== 솔루션 ";           
        //}
        //else
        //{
            cout<<"찾는중 ";
        //}
        heu->View();
        Heues nheues = heu->EnumNext();//큐에서 꺼내온 경험 정보에서 다음 경험 목록 조사
        HIter seek = nheues.begin();
        HIter last = nheues.end();
        for(  ;seek != last; ++seek)//반복(다음 경험 목록을 순차적으로 반복)
        {
            if((*seek)->IsGoal())//목적지에 도달하면
            {
                cout<<"===== 솔루션 ";           
                (*seek)->View();
                delete (*seek);
            }
            else
            {
                hq.push(*seek);//큐에 보관
            }
        }
        delete heu;
    }
    return 0;
}
