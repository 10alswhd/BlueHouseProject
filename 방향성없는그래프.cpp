//Graph.h
#pragma once
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> Neighbors;
class Graph
{
    const int vn;//정점의 개수
    int **matrix;//인접 행렬   
public:
    Graph(int vn);
    ~Graph(void);   
    void AddEdge(int start, int goal);//간선 추가
    void ViewNeighbors()const;
    void ViewNeighbor(int vt)const;
    Neighbors FindNeighbors(int vt);
};
//Graph.cpp
#include "Graph.h"
#include <string.h>
 
Graph::Graph(int vn):vn(vn)
{
    matrix = new int *[vn];//매트릭스 메모리 할당
     for (int i = 0; i < vn; i++)
     {
         matrix[i] = new int[vn];//매트릭스 [i-row] 메모리 할당
         memset(matrix[i], 0, sizeof(int)*vn);//메모리 0으로 초기화
     }
}
 
Graph::~Graph(void)
{
    for (int i = 0; i < vn; i++)
    {
        delete[] matrix[i];//매트릭스 [i-row]  메모리 소멸
    }
    delete[] matrix;//매트릭스 메모리 해제     
}
void Graph::AddEdge(int start, int goal)//간선 추가
{
    matrix[start][goal] = 1;//간선 설정
    matrix[goal][start] = 1;//간선 설정
}
void Graph::ViewNeighbors()const
{
    cout<<"=== 이웃 정점 ==="<<endl;
    for (int i = 0; i < vn; i++)
    {
        cout<<i<<"의 이웃: ";
        ViewNeighbor(i);//i정점의 이웃 보여주기
    }
    cout<<endl;
}
void Graph::ViewNeighbor(int vt)const
{
    for (int i = 0; i < vn; i++)
    {
        if(matrix[vt][i])
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;
}
Neighbors Graph::FindNeighbors(int vt)
{
    Neighbors neighbors;
    for (int i = 0; i < vn; i++)
     {
         if(matrix[vt][i])
         {
             neighbors.push_back(i);
         }
     }
    return neighbors;
}
 


//Program.cpp
#include "Graph.h"
 
int main()
{
    Graph *graph = new Graph(9);//그래프 동적 생성
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
     delete graph;
     return 0;
}
