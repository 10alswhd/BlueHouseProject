//Heuristic.h
#pragma once
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> Bucket;
typedef Bucket::iterator BIter;
typedef Bucket::const_iterator CBIter;
 
class Heuristic;
typedef vector<Heuristic *> Heues;
typedef Heues::iterator HIter;
typedef Heues::const_iterator CHIter;
 
class Heuristic
{
    Bucket original;
    Bucket out;
public:
    Heuristic(Bucket bucket);
    Heues EnumNext();
    void View()const;
    bool IsEmpty()const;
private:
    Heuristic(const Heuristic *bheu,int ball);
};
//Heuristic.cpp
#include "Heuristic.h"
 
Heuristic::Heuristic(Bucket bucket)
{
    original = bucket;
}
Heues Heuristic::EnumNext()
{
    Heues heues;
    BIter seek = original.begin();
    BIter last = original.end();
    for(  ;seek != last ; ++seek)
    {
        //하나의 공을 꺼낸 경험 정보를 생성하여 보관
        heues.push_back(new Heuristic(this,*seek));
    }
    return heues;
}
 
void Heuristic::View()const
{
    CBIter seek = out.begin();
    CBIter last = out.end();
    for(  ;seek != last ; ++seek)
    {
        cout<<(*seek)<<" ";
    }
    cout<<endl;
}
 
bool Heuristic::IsEmpty()const
{
    return original.empty(); //바구니가 비었는지 판별
}
 
Heuristic::Heuristic(const Heuristic *bheu,int ball)
{
    out = bheu->out;
    original = bheu->original;
    BIter seek = original.begin();
    BIter last = original.end();
 
    for(  ;seek != last; ++seek)
    {
        if((*seek)==ball) //seek위치의 공과 ball이 같으면
        {
            original.erase(seek);//공을 꺼냄
            out.push_back(ball);//꺼낸 바구니에 보관           
            break;
        }       
    }
}


//Program.cpp
#include "Heuristic.h"
#include <stack>
using namespace std;
 
int main()
{
    stack<Heuristic *> hs;
 
    Bucket bucket;
    for(int i = 0; i<10;i++)
    {
        bucket.push_back(i);
    }
 
   
    Heuristic *heu = new Heuristic(bucket);//hs.push(0~9까지 공을 보관한 초기 경험 정보를 생성
    hs.push(heu);//스택에 보관
    while(hs.empty() == false) //반복(스택이 비어 있지 않다면)
    {
        heu = hs.top();//스택에서 경험 정보 꺼내옮
        hs.pop();
 
        Heues nheues = heu->EnumNext();//스택에서 꺼내온 경험 정보에서 다음 경험 목록 조사
        HIter seek = nheues.begin();
        HIter last = nheues.end();
        for(  ;seek != last; ++seek)//반복(다음 경험 목록을 순차적으로 반복)
        {
            if((*seek)->IsEmpty())//바구니에 공이 비면
            {
                (*seek)->View();//결과 출력
                delete (*seek);
            }
            else//그렇지 않다면
            {
                hs.push(*seek);//스택에 보관
            }
        }
        delete heu;
    }
    return 0;
} 
