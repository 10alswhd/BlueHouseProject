#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
 
class Job
{
    string name;
    int length;
    int start_time;
    int wait_time;
    int end_time;
public:
    Job(string name,int length)
    {
        this->name = name;
        this->length = length;
        start_time = 0;
        end_time = 0;
        wait_time = 0;
    }   
    bool Do()
    {
        length--;
        cout<<name<<" ,"<<length<<" ";
        if(length>0)
        {
            return true;
        }
        else
        {           
            return false;
        }
    }
    void SetStartTime(int time)
    {
        start_time = time;
        cout<<"<<"<<name<<", "<<length<<" 수행 요청 >>";
    }
    void SetWaitTime(int time)
    {
        wait_time = time - start_time;
    }
    void SetEndTime(int time)
    {
        end_time = time;
        cout<<" "<<name<<"작업 완료 ";
    }
    int GetWaitingTime()const
    {
        return wait_time;
    }
    int GetCompleteTime()const
    {
        return end_time - start_time;
    }
    int GetLength()const
    {
        return length;
    }
    void View()const
    {
        cout<<name<<" 대기시간:"<<wait_time<<" 완료시간:"<<GetCompleteTime()<<endl;
    }
};
 
struct JGreater
{
    bool operator()(const Job *j1, const Job *j2) const
    {
        return j1->GetLength() > j2->GetLength();
    }
};
 
 
class SJFAlgorithm
{
    priority_queue<Job *, vector<Job *>,JGreater>  pq;   
    Job *doingjob;
    int time;
public:
    SJFAlgorithm()
    {
        doingjob=0;
        time = 0;
        cout<<time<<" ";
    }
    void AddJob(Job *job)
    {
        pq.push(job);
        job->SetStartTime(time);       
    }
    void Clock()
    {
        time++;
        cout<<endl<<time<<" ";
        if(doingjob==0)
        {
            if(pq.empty())
            {
                return;
            }
 
            doingjob = pq.top();
            pq.pop();
            doingjob->SetWaitTime(time);
        }
        bool remain = doingjob->Do();
        if(remain == false)
        {
            doingjob->SetEndTime(time);
            doingjob = 0;
        }       
       
    }
    bool IsEnd()const
    {
        return pq.empty() && (doingjob==0);
    }
};
int main()
{
    Job *test_jobs[6];
    test_jobs[0] = new Job("A",5);
    test_jobs[1] = new Job("B",6);
    test_jobs[2] = new Job("C",9);
    test_jobs[3] = new Job("D",8);
    test_jobs[4] = new Job("E",7);
    test_jobs[5] = new Job("F",6);
    SJFAlgorithm *sjf = new SJFAlgorithm();
    sjf->AddJob(test_jobs[0]);
    sjf->Clock();
    sjf->AddJob(test_jobs[1]);
    sjf->Clock();
    sjf->Clock();
    sjf->AddJob(test_jobs[2]);
    sjf->Clock();
    sjf->AddJob(test_jobs[3]);
    sjf->AddJob(test_jobs[4]);
    sjf->Clock();
    sjf->AddJob(test_jobs[5]);
   
    while(sjf->IsEnd() == false)
    {
        sjf->Clock();
    }
    delete sjf;
    cout<<"시뮬레이션 종료"<<endl;
    for(int i = 0; i<6; i++)
    {
        test_jobs[i]->View();
        delete test_jobs[i];
    }
 
    return 0;
}
