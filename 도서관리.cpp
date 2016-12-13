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
//Book.h
#pragma once
#include "ehglobal.h"
class Book
{
    const string isbn;
    int bnum;
    string title;
public:
    Book(string isbn,int bnum,string title);   
    void View()const;
    string GetISBN()const;
};
 
//Book.cpp
#include "Book.h"
 
 
Book:: Book(string isbn,int bnum,string title):isbn(isbn)
{
    this->bnum = bnum;
    this->title = title;
}
void Book::View()const
{
    cout<<isbn<<" ,No."<<bnum<<", 제목:"<<title<<endl;
}
string Book::GetISBN()const
{
    return isbn;
}
 
//Genre.h
#pragma once
#include "Book.h"
#include <vector>
#include <algorithm>
using namespace std;
 
typedef vector<Book *> Books;
typedef Books::iterator BIter;
typedef Books::const_iterator CBIter;
 
class Genre
{
    const int gnum;
    string name;
    Books books;
    static const int max_book;
public:
    Genre(int gnum,string name);
    ~Genre(void);
    void View()const;
    Book *AddBook(string isbn);
    int GetGNum()const;
    void ViewAll()const;
    void FindBook()const;
    string RemoveBook();
};
 
//Genre.cpp
#include "Genre.h"
const int Genre::max_book = 100;
Genre::Genre(int gnum,string name):gnum(gnum)
{
    this->name = name;
    books.resize(max_book,0);
}
Genre::~Genre(void)
{
    for(int index=0; index<max_book;++index)
    {
        if(books[index])
        {
            delete books[index];
        }
    }
}
void Genre::View()const
{
    cout<<"No."<<gnum<<" , 장르 이름:"<<name<<endl;
}
Book *Genre::AddBook(string isbn)
{
    cout<<"장르 내 도서 구분자(1~100):";
    int bnum = ehglobal::getnum();
    if((bnum<1)||(bnum>100))
    {
        cout<<"범위를 벗어난 도서 구분자입니다."<<endl;
        return 0;
    }
    cout<<"도서 제목:";
    string title = ehglobal::getstr();
    books[bnum-1] =new Book(isbn,bnum,title);
    return books[bnum-1];
}
int Genre::GetGNum()const
{
    return gnum;
}
void Genre::ViewAll()const
{
    View();
    for(int index=0; index<max_book;++index)
    {
        if(books[index])
        {
            books[index]->View();
        }
    }
}
void Genre::FindBook()const
{
    cout<<"장르 내 도서 구분자(1~100):";
    int bnum = ehglobal::getnum();
    if((bnum<1)||(bnum>100))
    {
        cout<<"범위를 벗어난 도서 구분자입니다."<<endl;       
        return;
    }   
    if(books[bnum-1])
    {
        books[bnum-1]->View();
    }
    else
    {
        cout<<"없는 도서입니다."<<endl;
    }
}
string Genre::RemoveBook()
{
    cout<<"장르 내 도서 구분자(1~100):";
    int bnum = ehglobal::getnum();
    if((bnum<1)||(bnum>100))
    {
        cout<<"범위를 벗어난 도서 구분자입니다."<<endl;       
        return "";
    }
   
    if(books[bnum-1])
    {
        string isbn = books[bnum-1]->GetISBN();
        delete books[bnum-1];
        books[bnum-1] = 0;
        return isbn;
    }
    cout<<"없는 도서입니다."<<endl;
    return "";
}
//App.h
#pragma once
#include "Genre.h"
#include <list>
#include <map>
using namespace std;
typedef list<Genre *> Genres;
typedef Genres::iterator GIter;
typedef Genres::const_iterator CGIter;
typedef map<string, Book *> BookDic;
typedef BookDic::iterator BDIter;
typedef BookDic::const_iterator CBDIter;
 
class App
{
    Genres genres;
    BookDic bookdic;
    int last_gnum;
public:
    App(void);
    ~App(void);
    void Run();
private:
    int SelectMenu();//메뉴 출력 및 선택   
    void AddGenre(); //장르 추가
    void ListGenre(); //전체 장르 보기
    void AddBook();  //도서 추가
    void RemoveBook(); //도서 삭제
    void FindBookByISBN(); //ISBN으로 도서 검색
    void FindBookAtAGenre(); //특정 장르 선택 후 도서 검색
    void ViewAGenre(); //특정 장르 보기
    void ListBook(); //전체 도서 보기
    void ViewAll(); //전체 보기
    Genre *SelectGenre();//장르 선택
};
//App.cpp
#include "App.h"
App::App(void)
{
    last_gnum = 0;
}
App::~App(void)
{
    //장르 소멸
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        delete genre;
    }
}
 
void App::Run()
{
    int key=NO_DEFINED;
    while((key = SelectMenu())!=ESC)//메뉴 출력 및 선택
    {
        switch(key)
        {
        case F1: AddGenre(); break;//장르 추가
        case F2: ListGenre(); break; //전체 장르 보기
        case F3: AddBook(); break; //도서 추가
        case F4: RemoveBook(); break; //도서 삭제
        case F5: FindBookByISBN(); break; //ISBN으로 도서 검색
        case F6: FindBookAtAGenre(); break; //특정 장르 선택 후 도서 검색
        case F7: ViewAGenre(); break; //특정 장르 보기
        case F8: ListBook(); break; //전체 도서 보기
        case F9: ViewAll(); break; //전체 보기
        default: cout<<"잘못 선택하셨습니다."<<endl; break;
        }
        cout<<"아무 키나 누르세요."<<endl;
        ehglobal::getkey();
    }
}
 
int App::SelectMenu()//메뉴 출력 및 선택   
{
    ehglobal::clrscr();
    cout<<"장르별 도서 관리 프로그램 [ESC]종료"<<endl;
    cout<<"F1: 장르 추가 F2:전체 장르 보기"<<endl;
    cout<<"F3: 도서 추가 F4: 도서 삭제"<<endl;
    cout<<"F5: ISBN으로 도서 검색"<<endl;
    cout<<"F6: 특정 장르 선택 후 도서 검색"<<endl;
    cout<<"F7: 특정 장르 보기"<<endl;
    cout<<"F8: 전체 도서 보기 F9: 전체 보기"<<endl;
    return ehglobal::getkey();
}
void App::AddGenre() //장르 추가
{
    last_gnum++;
    cout<<last_gnum<<"번째 추가할 장르 이름:"<<endl;
    string gname = ehglobal::getstr();
    genres.push_back(new Genre(last_gnum,gname));
}
void App::ListGenre() //전체 장르 보기
{
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        genre->View();
    }
}
void App::AddBook()  //도서 추가
{
    cout<<"추가할 도서의 ISBN:";
    string isbn = ehglobal::getstr();
    if(bookdic[isbn])
    {
        cout<<"이미 있는 도서의 ISBN입니다."<<endl;
        return;
    }
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    Book *book = genre->AddBook(isbn);
    if(book)
    {
        bookdic[isbn] = book;
    }
}
 
Genre *App::SelectGenre()//장르 선택
{
    ListGenre();
    cout<<"선택할 장르 번호:";
    int gnum = ehglobal::getnum();
   
   
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        if(genre->GetGNum() == gnum)
        {
            return genre;
        }
    }
    return 0;
}
 
void App::RemoveBook() //도서 삭제
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    string isbn = genre->RemoveBook();
    bookdic[isbn] = 0;  
}
void App::FindBookByISBN() //ISBN으로 도서 검색
{
    cout<<"검색할 도서의 ISBN:";
    string isbn = ehglobal::getstr();
    if(bookdic[isbn]==0)
    {
        cout<<"없는 도서의 ISBN입니다."<<endl;
        return;
    }
    bookdic[isbn]->View();
}
void App::FindBookAtAGenre() //특정 장르 선택 후 도서 검색
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    genre->FindBook();
}
void App::ViewAGenre() //특정 장르 보기
{
    Genre *genre = SelectGenre();
    if(genre == 0)
    {
        cout<<"잘못 선택하였습니다."<<endl;
        return;
    }
    genre->ViewAll();
}
 
void App::ListBook() //전체 도서 보기
{
    BDIter seek = bookdic.begin();
    BDIter last = bookdic.end();
    Book *book=0;
    for(  ;seek != last; ++seek)
    {
        book = (*seek).second;
        if(book)
        {
            book->View();
        }
    }
}
 
void App::ViewAll() //전체 보기
{
    GIter seek = genres.begin();
    GIter last = genres.end();
    Genre *genre = 0;
    for(   ;seek != last ; ++seek)
    {
        genre = *seek;
        genre->ViewAll();
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
