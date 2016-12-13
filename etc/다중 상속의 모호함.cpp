
//다중 상속의 모호함
//Program.cpp
 
#include <iostream>
#include <string>
using namespace std;
 
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
};
 
class Student: public Man
{
public:
    Student(string name):Man(name)
    {
    }
};
class BaseballPlayer: public Man
{
public:
    BaseballPlayer(string name):Man(name)
    {
    }
};
class BaseBallPlayerStudent: public Student, public BaseballPlayer
{
public:
    BaseBallPlayerStudent(string name):Student(name), BaseballPlayer(name)
    {
    }
};
 
int main()
{
    //BaseBallPlayerStudent *bbps = new BaseBallPlayerStudent("홍길동");
    //bbps->View();
    //delete bbps;
    return 0;
}
 
