//common.h (정렬 알고리즘에 공통으로 사용할 내용)
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;
 
class Member
{
    string name;
    int num;
public:
    Member(string name,int num)
    {
        this->name = name;
        this->num = num;
    }
    string GetName()const
    {
        return name;
    }
    int GetNum()const
    {
        return num;
    }
    void View()const
    {
        cout<<setw(10)<<setfill('0')<<num<<","<<name<<endl;
    }
};
 
int CompareByNum(Member *m1, Member *m2)
{
    int n1 = m1->GetNum();
    int n2 = m2->GetNum();
    return  n1 - n2;
}
int CompareByName(Member *m1, Member *m2)
{
    string n1 = m1->GetName();
    string n2 = m2->GetName();
    return  n1.compare(n2);
}
 
void MakeRandomMembers(Member **pbase, size_t n)
{
    for(size_t i=0; i<n; i++)
    {
        int num = rand()*rand();
        char buf[256];
        sprintf_s(buf,sizeof(buf),"이름%010d",rand()*rand());
        pbase[i] = new Member(buf,num);
    }
}
 
void RemoveMembers(Member **pbase, size_t n)
{
    for(size_t i=0; i<n; i++)
    {       
        delete pbase[i];
    }
}
 
void ViewMembers(Member **pbase, size_t n)
{
    for(size_t i=0;i<n; i++)
    {
        pbase[i]->View();
    }
}
 
  


//Program.cpp
#include "common.h"
 
#define LCHILD(me)   (2*me +1)
#define RCHILD(me)  (LCHILD(me)+1)
#define PARENT(me)  ((me-1)/2)
 
 
 
template <typename data, typename compare>
void heap_sort(data *base, size_t n, compare algo)
{      
    //초기 힙 구성 시작
    for( size_t i =1 ; i<n; i++)
    {       
        int j=i;
        while(j>0)//루트가 아니면 반복
        {           
            int pa = PARENT(j);//부모 인덱스를 구하기
            if( algo(base[j], base[pa]) >0 ) //부모보다 크면
            {
                swap(base[j],base[pa]);//부모와 교환
                j = pa;
            }
            else
            {
                break;
            }           
        }
    }
    //초기 힙 구성 끝
    swap(base[0],base[n-1]);//루트와 마지막 자손 교환
    n--;
    size_t me;
    size_t lc;
    size_t rc;
    while(n>1)//반복: n이 1보다 크면
    {
        //힙 구성 시작
        me = 0;
        while(1)
        {                       
            lc = LCHILD(me);
            rc = RCHILD(me);
            if(lc>=n)//자식이 없음
            {
                break;
            }
            if(rc == n)//왼쪽 자식만 있음
            {
                if(algo(base[me], base[lc])<0)
                {
                    swap(base[me],base[lc]);
                }
                break;
            }
            //둘 다 있을 때
            int bc = lc;
            if(algo(base[lc], base[rc])<0)
            {
                bc = rc;
            }
            if(algo(base[bc],base[me])>0)
            {
                swap(base[bc],base[me]);
                me = bc;
            }
            else
            {
                break;
            }
 
        }
        //힙 구성 끝
        swap(base[0],base[n-1]);//루트와 마지막 자손 교환
        n--;
    }       
}
 
#define MAX_DATA 1000
 
int main()
{
    Member *base[MAX_DATA];
    MakeRandomMembers(base,10);
    cout<<"정렬 전"<<endl;
    ViewMembers(base,10);
    heap_sort(base,10,CompareByNum);
    cout<<"번호로 정렬 후"<<endl;
    ViewMembers(base,10);
    heap_sort(base,10,CompareByName);
    cout<<"이름으로 정렬 후"<<endl;
    ViewMembers(base,10);
    RemoveMembers(base,10);
 
    clock_t st,et;
 
    MakeRandomMembers(base,MAX_DATA);
    cout<<"수행 성능 테스트1 자료 개수:"<<MAX_DATA<<endl;
    st = clock();   
    heap_sort(base,MAX_DATA,CompareByName);   
    et=clock();
    cout<<"수행 속도:"<<et-st<<endl;
    RemoveMembers(base,MAX_DATA);
 
    MakeRandomMembers(base,MAX_DATA/10);
    cout<<"수행 성능 테스트2 자료 개수:"<<MAX_DATA/10<<endl;
    st = clock();
    MakeRandomMembers(base,MAX_DATA/10);
    heap_sort(base,MAX_DATA/10,CompareByName);
    et=clock();
    cout<<"수행 속도:"<<et-st<<endl;
    RemoveMembers(base,MAX_DATA/10);
    return 0;
}
