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
    Vertexs FindNeighbors(string vt)const;
    Edges FindEdges(string vt)const;
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
 
Vertexs Graph::FindNeighbors(string vt)const
{
    Vertexs neighbors;
    CEIter seek = edges.begin();
    CEIter last = edges.end();
 
    for(  ;seek != last; ++seek)
    {
        if((*seek)->Exist(vt))
        {
            neighbors.push_back((*seek)->Other(vt));
        }
    }   
    return neighbors;
}
 
Edges Graph::FindEdges(string vt)const
{
    Edges neighbors;
    CEIter seek = edges.begin();
    CEIter last = edges.end();
    for(  ;seek != last; ++seek)
    {
        if((*seek)->Exist(vt))
        {
            neighbors.push_back(*seek);
        }
    }   
    return neighbors;
}
//Heuristic.h
#pragma once
#include "Graph.h"
#include <vector>
using namespace std;
 
typedef vector<string> Foots;
typedef Foots::iterator FIter;
typedef Foots::const_iterator CFIter;
 
class Heuristic;
typedef vector<Heuristic *> Heues;
typedef Heues::iterator HIter;
typedef Heues::const_iterator CHIter;
 
class Heuristic
{
    Graph *graph;       
    Foots foots;
    int weight;
public:
    Heuristic(Graph *graph, string start);   
    Heues EnumNext();   
    void View()const;   
    int GetWeight()const;
    string GetLastVertex()const;
private:
    Heuristic(const Heuristic *bheu,string vt,int weight);
};
//Heuristic.cpp
#include "Heuristic.h"
#include <algorithm>
 
Heuristic::Heuristic(Graph *graph,string start)
{
    this->graph = graph;
    foots.push_back(start);
    weight = 0;
}
 
Heues Heuristic::EnumNext()
{
    Heues nheues;
    string last_foot = (*foots.rbegin());
    Edges edges = graph->FindEdges(last_foot);
 
    EIter eseek = edges.begin();
    EIter elast = edges.end();
    for(  ;eseek != elast; ++eseek)
    {
        string other = (*eseek)->Other(last_foot);//간선의 나머지 정점 구하기
        if(find(foots.begin(), foots.end(),other) == foots.end())//방문한 적이 없으면
        {
            Heuristic * nheu = new Heuristic(this,other,(*eseek)->GetWeight());
            HIter hseek = nheues.begin();
            HIter hlast = nheues.end();
            for(  ;hseek != hlast; ++hseek)
            {
                if((*hseek)->GetWeight()>=nheu->GetWeight())
                {
                    break;
                }
            }   
            nheues.insert(hseek,nheu);//*seek를 추가 방문하는 새로운 경험을 생성           
        }
    }   
    return nheues;
}
 
 
 
 
void Heuristic::View()const
{
    cout<<"cost "<<weight<<" :";
    CFIter seek = foots.begin();
    CFIter last = foots.end();
    for(  ;seek != last; ++seek)
    {
        cout<<(*seek)<<" ";
    }
    cout<<endl;
}
 
int Heuristic::GetWeight()const
{
    return weight;
}
 
string Heuristic::GetLastVertex()const
{
    return (*foots.rbegin());
}
 
Heuristic::Heuristic(const Heuristic *bheu,string vt,int weight)
{
    this->graph = bheu->graph;
    foots = bheu->foots;   
    this->weight = bheu->weight + weight;//경로의 비용을 추가
    foots.push_back(vt);//vt를 방문한 행적에 추가
}

//Program.cpp
#include "Heuristic.h"
#include <queue>
using namespace std;
struct HGreater
{
    bool operator()(const Heuristic *h1, const Heuristic *h2) const
    {
        return h1->GetWeight()> h2->GetWeight();
    }
};
 
 
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
    graph->AddVertex("I");
 
    graph->AddEdge("A", "B", 3);//간선 추가
    graph->AddEdge("A", "C", 4);//간선 추가
    graph->AddEdge("B", "C", 4);//간선 추가
    graph->AddEdge("B", "D", 3);//간선 추가
    graph->AddEdge("B", "E", 3);//간선 추가
    graph->AddEdge("C", "D", 3);//간선 추가
    graph->AddEdge("C", "I", 4);//간선 추가
    graph->AddEdge("D", "E", 4);//간선 추가
    graph->AddEdge("D", "F", 6);//간선 추가
    graph->AddEdge("D", "H", 2);//간선 추가
    graph->AddEdge("D", "I", 5);//간선 추가
    graph->AddEdge("E", "F", 5);//간선 추가
    graph->AddEdge("F", "G", 4);//간선 추가
    graph->AddEdge("G", "H", 3);//간선 추가
    graph->AddEdge("H", "I", 5);//간선 추가   
    graph->ViewNeighbors();
 
    priority_queue<Heuristic *,vector<Heuristic *>, HGreater > hq;
    Heues htable;
    Heues all;   
    Heuristic *heu = new Heuristic(graph,"A");//초기 경험 정보를 생성
    hq.push(heu);//큐에 보관
    while(hq.empty() == false) //반복(큐가 비어 있지 않다면)
    {
        heu = hq.top();//큐에서 경험 정보 꺼내옮
        hq.pop();
        all.push_back(heu);
        cout<<"찾는중 ";
        heu->View();
 
        Heues nheues = heu->EnumNext();//큐에서 꺼내온 경험 정보에서 다음 경험 목록 조사       
        HIter seek = nheues.begin();
        HIter last = nheues.end();       
 
        for(  ;seek != last; ++seek)//반복(다음 경험 목록을 순차적으로 반복)
        {
            HIter hseek = htable.begin();
            HIter hlast = htable.end();
 
            string nvt = (*seek)->GetLastVertex();
            bool check = true;
 
            for(   ;hseek != hlast; ++hseek)
            {
                string hvt = (*hseek)->GetLastVertex();
                if(nvt == hvt)
                {
                    if((*seek)->GetWeight()<(*hseek)->GetWeight())
                    {                                               
                        check = false;                       
                    }
                    break;
                }
            }
 
            if(hseek == hlast)
            {
                hq.push(*seek);//큐에 보관
                htable.push_back(*seek);
            }
            else
            {
                if(check == false)
                {
                    htable.erase(hseek);
                    htable.push_back(*seek);
                    hq.push(*seek);
                }  
            }
        }       
    }
 
 
    HIter hseek = htable.begin();
    HIter hlast = htable.end();
    cout<<"A에서의 최단 경로"<<endl;
    for(   ;hseek != hlast; ++hseek)
    {
        (*hseek)->View();
    }
 
    HIter aseek = all.begin();
    HIter alast = all.end();
    for(   ;aseek != alast; ++aseek)
    {
        delete (*aseek);
    }
    delete graph;
    return 0;
}
