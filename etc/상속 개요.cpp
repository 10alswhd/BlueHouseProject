//상속 개요
#include <iostream>
#include <string>
using namespace std;
 
class Musician
{   
public:
    void Play()
    {
        cout<<"딩동댕"<<endl;
    }
};
 
class Pianist:
    public Musician //Musician 클래스를 기반으로 파생한 Pianist 클래스 정의
{
 
};
 
int main()
{
    Pianist *pianist = new Pianist();
    pianist->Play();
    delete pianist;
    return 0;
}
 
