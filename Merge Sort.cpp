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
 
 
template <typename data, typename compare>
void merge_sort(data *base, size_t n, compare algo)
{
    if(n<=1)
    {
        return;
    }
    size_t h = n/2;
    size_t lh = n-h;
    merge_sort(base,h,algo);//분할
    merge_sort(base+h, lh, algo);//분할
 
 
    //이 후의 분할한 배열의 내용을 목적에 맞게 정복한다.
    size_t ai = 0;
    size_t bi = h;
    size_t ci = 0;
    data *tbase = new data[n];
 
    while((ai<h)&&(bi<n))
    {
        if(algo(base[ai], base[bi])>0)
        {
            tbase[ci] = base[bi];
            bi++;
        }
        else
        {
            tbase[ci] = base[ai];
            ai++;
        }
        ci++;
    }
 
    while(ai<h)
    {
        tbase[ci] = base[ai];
        ai++;
        ci++;
    }
    while(bi<n)
    {
        tbase[ci] = base[bi];
        bi++;
        ci++;
    }
 
    for(ci=0; ci<n;ci++)
    {
        base[ci] = tbase[ci];
    }
    delete[] tbase;
}
 
#define MAX_DATA 1000
 
int main()
{
    Member *base[MAX_DATA];
    MakeRandomMembers(base,10);
    cout<<"정렬 전"<<endl;
    ViewMembers(base,10);
    merge_sort(base,10,CompareByNum);
    cout<<"번호로 정렬 후"<<endl;
    ViewMembers(base,10);
    merge_sort(base,10,CompareByName);
    cout<<"이름으로 정렬 후"<<endl;
    ViewMembers(base,10);
    RemoveMembers(base,10);
 
    clock_t st,et;
 
    MakeRandomMembers(base,MAX_DATA);
    cout<<"수행 성능 테스트1 자료 개수:"<<MAX_DATA<<endl;
    st = clock();   
    merge_sort(base,MAX_DATA,CompareByName);   
    et=clock();
    cout<<"수행 속도:"<<et-st<<endl;
    RemoveMembers(base,MAX_DATA);
 
    MakeRandomMembers(base,MAX_DATA/10);
    cout<<"수행 성능 테스트2 자료 개수:"<<MAX_DATA/10<<endl;
    st = clock();
    MakeRandomMembers(base,MAX_DATA/10);
    merge_sort(base,MAX_DATA/10,CompareByName);
    et=clock();
    cout<<"수행 속도:"<<et-st<<endl;
    RemoveMembers(base,MAX_DATA/10);
    return 0;
}
