//EHProcess.h
#pragma once
#include <iostream>
#include <string>
using namespace std;
 
class EHProcess
{
    string pname; //프로그램 이름
    const int tjob; //전체 작업량
    const int cjob; //cpu 점유 시 수행가능 최대 작업량
    int ntjob; //현재 남은 작업량
    int ncjob; //현재 cpu 점유 시 수행가능 최대 작업량
public:
    EHProcess(string pname,int tjob,int cjob);
    void IdleToReady();//Idle 상태에서 Ready 상태로 전이
    int Running();//CPU를 점유하여 실행, 남은 작업량 반환
    void EndProgram(); //프로세스 종료
};

//EHProcess.h
#include "EHProcess.h"
 
EHProcess::EHProcess(string pname,int tjob,int cjob):tjob(tjob),cjob(cjob)
{
    this->pname = pname;
}
void EHProcess::IdleToReady()//Idle 상태에서 Ready 상태로 전이
{
    cout<<pname<<" 시작"<<endl;
    ntjob = tjob; //프로그램 이미지 메모리에 로딩을 표현
}
int EHProcess::Running()//CPU를 점유하여 실행, 남은 작업량 반환
{
    ncjob = cjob; //ncjob에 CPU 사용할 수 있는 시간 대입
 
    //남은 작업량(ntjob)과 CPU 사용할 수 있는 시간(ncjob)이 있다면
    for(  ; ntjob && ncjob ; ntjob--, ncjob--)
    {
        cout<<pname<<" ";//단위 시간 작업 수행을 표현
    }
 
    cout<<endl; //CPU를 반납함을 표현
    return ntjob; //남은 작업량 반환
}
void EHProcess::EndProgram() //프로세스 종료
{
    cout<<pname<<"종료"<<endl; //프로세스 종료를 표현
}
//Scheduler.h
#pragma once
#include <vector>
#include <queue>
using namespace std;
#include "EHProcess.h"
 
typedef vector<EHProcess *> Memory;
typedef queue<EHProcess *> ReadyQueue;
typedef Memory::iterator miter;
 
class Scheduler 
{
    Memory hard_disk; // 하드디스크
    ReadyQueue  rq; //대기 큐
public:
    Scheduler();
    virtual ~Scheduler();
private:
    void Init(); //시뮬레이션 초기화- 프로그램 설치 및 실행 명령
    void Simulation();//시뮬레이션 시작
    void Ending();//시뮬레이션 종료
};
//Scheduler.cpp
#include "Scheduler.h"
 
Scheduler::Scheduler()
{
    Init();
    Simulation();
}
void Scheduler::Init()
{
    //하드디스크에 프로그램 설치를 표현
    hard_disk.push_back(new EHProcess("A",30,5));
    hard_disk.push_back(new EHProcess("B",24,6));
    hard_disk.push_back(new EHProcess("C",25,4));
 
    miter seek = hard_disk.begin();
    miter end = hard_disk.end();
    EHProcess *pro=0;
    //하드디스크에 설치한 프로그램을 실행 명령을 표현
    for( ; seek != end ; ++seek)
    {
        pro = *seek;
        rq.push(pro); //대기 큐에서 기다림
        pro->IdleToReady();//Idle 상태에서 Ready상태로 전이
    }
}
 
Scheduler::~Scheduler()
{
    Ending();
}
void Scheduler::Ending()
{
    miter seek = hard_disk.begin();
    for(   ; seek != hard_disk.end(); ++seek)
    {
        delete (*seek);
    }
}
 
void Scheduler::Simulation()
{
    EHProcess *process = 0;
    int job=0;
    while( !rq.empty() ) //대기 큐가 비어있지 않을 때
    {       
        process = rq.front();//가장 먼저 대기한 프로세스를 꺼냄
        rq.pop();
 
        job = process->Running();//꺼낸 프로세스를 실행
        if(job) //남은 작업이 있다면
        {
            rq.push(process); //대기큐에서 기다림
        }
        else
        {
            process->EndProgram();//프로세스 종료
        }
    }
}
//Program.cpp
#include "Scheduler.h"
int main()
{
    Scheduler *pro = new Scheduler;
    delete pro;
    return 0;
}
