//인터페이스 다중 상속
//Program.cpp
 
#include <iostream>
#include <string>
using namespace std;
 
#define interface struct
 
interface IPlay
{
    virtual void Play()=0;
};
 
interface IStudy
{
    virtual void Study()=0;
};
 
class Man
{
    string name;
public:
    Man(string name)
    {
        this->name = name;
    }
    void View()
    {
        cout<<"이름은 "<<name<<"입니다."<<endl;
    }
    string GetName()
    {
        return name;
    }
};
 
class Student:public Man, public IStudy
{
public:
    Student(string name):Man(name)
    {
    }
    virtual void Study()
    {
        cout<<GetName()<<" 공부하다."<<endl;
    }
};
 
class BaseBallPlayer:public Man, public IPlay
{
public:
    BaseBallPlayer(string name):Man(name)
    {
    }
    virtual void Play()
    {
        cout<<GetName()<<" 운동하다."<<endl;
    }
};
 
class BaseBallPlayerStudent:public Man, public IStudy, public IPlay
{
public:
    BaseBallPlayerStudent(string name):Man(name)
    {
    }
    virtual void Play()
    {
        cout<<GetName()<<" 운동하다."<<endl;
    }
    virtual void Study()
    {
        cout<<GetName()<<" 공부하다."<<endl;
    }
};
 
 
int main()
{
    BaseBallPlayerStudent *bbps = new BaseBallPlayerStudent("홍길동");
    bbps->View();
    bbps->Play();
    bbps->Study();
    delete bbps;
    return 0;
}
