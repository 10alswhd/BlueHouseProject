

//static_cast
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
    void View()const
    {
        cout<<"이름:"<<name<<endl;
    }
};
 
class Student:public Man
{
    int num;
    string name;
public:
    Student(int num, string name):Man(name)
    {
        this->num = num;
        this->name = name;
    }
    void View()const
    {
        cout<<"번호:"<<num<<"이름:"<<name<<endl;
    }
    void Study()
    {
        cout<<name<<" 공부하다."<<endl;
    }
};
 
 
int main()
{
    Man *man = new Student(30,"홍길동");
    Student *stu = static_cast<Student *>(man);
    stu->Study();
    delete man;
    return 0;
}
 
 
