//ehglobal.h
#pragma once
#pragma warning(disable:4996)
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;
using std::ostream;
using std::endl;
#include <conio.h>
#include <windows.h>
enum keydata
{
    NO_DEFINED,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,ESC
};
 
//공통적으로 사용할 정적 메서드를 캡슐화한 클래스
class ehglobal
{
public:
    static void clrscr();//화면을 지우는 메서드
    static void timeflow(int millisecond); //원하는 시간동안 지연시키는 메서드
    static int getnum();//정수를 입력받는 메서드
    static string getstr();//문자열을 입력받는 메서드
    static int getkey();//기능 키를 입력받는 메서드
private:
    ehglobal(void){ }//개체를 생성하지 못하게 하기 위해 private으로 접근 지정
    ~ehglobal(void){}
};
//ehglobal.cpp
#include "ehglobal.h"
 
void ehglobal::clrscr()//화면을 지우는 메서드
{
    system("cls");
}
 
void ehglobal::timeflow(int millisecond) //원하는 시간동안 지연시키는 메서드
{
    Sleep(millisecond);
}
 
int ehglobal::getnum()//정수를 입력받는 메서드
{
    int num;
    char buf[255+1];
    cin.getline(buf,255);
    cin.clear();
    sscanf(buf,"%d",&num);
    return num;
}
 
 
string ehglobal::getstr()//문자열을 입력받는 메서드
{
    char buf[255+1];
    cin.getline(buf,255);
    cin.clear();
    return buf;
}
 
int ehglobal::getkey()//기능 키를 입력받는 메서드
{
    int key = getch();
 
    if(key == 27) //ESC를 누를 때의 key 값이 27임
    {
        return ESC;
    }
    if(key == 0) //기능 키를 눌렀을 때는 getch의 반환값이 0임
    {
        //어떤 기능 키를 눌렀는지 확인하려면 getch를 다시 호출해야 함
        //사용자에게 다시 키를 입력받는 것은 아님
        key = getch();
        switch(key) //입력한 키에 따라 약속된 값 반환
        {
        case 59: return F1;    case 60: return F2;
        case 61: return F3;    case 62: return F4;
        case 63: return F5;    case 64: return F6;
        case 65: return F7;    case 66: return F8;
        case 67: return F9;    case 68: return F10;
        }
    }
    return NO_DEFINED; //열거되지 않은 키를 눌렀을 때
}
//Member.h
#pragma once
#include "ehglobal.h"
class Member
{
    const string id;
    string name;
public:
    Member(string id,string name);
    string GetID()const;
    string GetName()const;
    void View()const;
};
 
//Member.cpp
#include "Member.h"
Member::Member(string id,string name):id(id)
{
    this->name = name;
}
string Member::GetID()const
{
    return id;
}
string Member::GetName()const
{
    return name;
}
void Member::View()const
{
    cout<<"아이디:"<<id<<" 이름:"<<name<<endl;
}
 
//App.h
#pragma once
#include "ehglobal.h"
#include "Member.h"
#include <map>
#include <algorithm>
using std::map;
using std::pair;
typedef map<string, Member *> MDic;
class App
{
    MDic mdic;
public:   
    void Run();
    ~App();
private:
    int SelectMenu();
    void AddMember(); //회원 추가
    void RemoveMember();//회원 삭제
    void FindMember(); //회원 검색   
    void ListAll()const; //전체 보기
};
 
//App.cpp
#include "App.h"
typedef MDic::iterator MIter;
typedef MDic::const_iterator CMIter;
void App::Run()
{
    int key=NO_DEFINED;
    while((key = SelectMenu())!=ESC)
    {
        switch(key)
        {
        case F1: AddMember(); break;
        case F2: RemoveMember(); break;
        case F3: FindMember(); break;
        case F4: ListAll(); break;       
        default: cout<<"잘못 선택하셨습니다."<<endl; break;
        }
        cout<<"아무 키나 누르세요."<<endl;
        ehglobal::getkey();
    }
}
int App::SelectMenu()
{
    ehglobal::clrscr();//콘솔 화면을 지우기
    cout<<"회원 관리 프로그램 [ESC]: 종료"<<endl;
    cout<<"F1: 회원 추가 F2: 회원 삭제 F3: 회원 검색 F4: 전체 보기"<<endl;
    return ehglobal::getkey();//사용자가 입력한 기능 키 반환
}
void App::AddMember() //회원 추가
{   
    cout<<"추가할 회원 아이디를 입력하세요."<<endl;
    string id = ehglobal::getstr();   
    if(mdic[id])
    {
        cout<<"이미 존재하는 아이디입니다."<<endl;
        return;
    }
    cout<<"회원 이름을 입력하세요."<<endl;
    string name = ehglobal::getstr();   
    mdic[id]=new Member(id,name);   
}
 
void App::RemoveMember()//회원 삭제
{
    cout<<"삭제할 회원 아이디를 입력하세요."<<endl;
    string id = ehglobal::getstr();
   
    Member *member = mdic[id];
    if(member==0)   
    {
        cout<<"존재하지 않는 아이디입니다."<<endl;
        return;
    }   
    delete member;
    mdic[id]=0;
    cout<<"삭제하였습니다."<<endl;
}
 
void App::FindMember() //회원 검색   
{
    cout<<"검색할 회원 아이디를 입력하세요."<<endl;
    string id = ehglobal::getstr();   
    Member *member = mdic[id];
    if(member==0)
    {
        cout<<"존재하지 않는 아이디입니다."<<endl;
        return;
    }   
    member->View();   
}
void App::ListAll()const //전체 보기
{
    CMIter seek = mdic.begin();
    CMIter end = mdic.end();
    Member *member = 0;   
    //반복자를 사용하여 차례대로 회원의 정보를 출력
    for(  ; seek != end ; ++seek)
    {       
        member = (*seek).second; //pair의 second는 보관한 회원 개체
        if(member)
        {
            member->View();
        }
    }
}
App::~App()
{
    MIter seek = mdic.begin();
    MIter end = mdic.end();
    Member *member = 0;
    for(  ; seek != end ; ++seek)
    {
        member = (*seek).second; //pair의 second는 보관한 회원 개체
        if(member)
        {
            delete member;
        }
    }
}


//Program.cpp
#include "App.h"
int main()
{
    App *app = new App();
    app->Run();
    delete app;
    return 0;
}
