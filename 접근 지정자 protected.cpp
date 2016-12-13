//접근 지정자 protected
#include <iostream>
#include <string>
using namespace std;
 
class Musician
{   
    string name;
public:
    Musician(string name)
    {
        this->name = name;
        cout<<"음악가 생성자"<<endl;
    }
    ~Musician()
    {
        cout<<"음악가 소멸자"<<endl;
    }
    void Play()
    {
        cout<<"딩동댕"<<endl;
    }
    void View()
    {
        cout<<"이름:"<<name<<endl;
    }
protected: //형식 내부와 파생 클래스 내부에서 접근 가능
    string GetName()const//이름 접근저
    {
        return name;
    }
};
 
class Pianist:
    public Musician //Musician 클래스를 기반으로 파생한 Pianist 클래스 정의
{
public:
    Pianist(string name):Musician(name) //기반 클래스 생성자 초기화
    {
        cout<<"피아니스트 생성자"<<endl;
    }
    ~Pianist()
    {
        cout<<"피아니스트 소멸자"<<endl;
    }
    void Tuning()
    {
        //기반 클래스에 protected로 접근 지정한 GetName을 호출
        cout<<GetName()<<" 조율하다."<<endl;
    }
};
 
int main()
{
    Pianist *pianist = new Pianist("홍길동");
    pianist->View();
    pianist->Tuning();
    pianist->Play();
    delete pianist;
    return 0;
}
 
