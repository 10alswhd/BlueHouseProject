//하향 캐스팅
//Program.cpp
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
    }
    string GetName()const
    {
        return name;
    }
    virtual void Play()=0;
};
class Pianist:public Musician
{
public:
    Pianist(string name):Musician(name)
    {
    }
    virtual void Play()
    {
        cout<<GetName()<<" 딩동댕 ♩♪♬"<<endl;
    }
    void Tuning()
    {
        cout<<"도도 레레 미미 파파"<<endl;
    }
};
class Drummer:public Musician
{
public:
    Drummer(string name):Musician(name)
    {
    }
    virtual void Play()
    {
        cout<<GetName()<<" 두두둥~~~"<<endl;
    }
};
 
int main()
{
    Musician *musicians[2];
    musicians[0] = new Pianist("피아노맨");
    musicians[1] = new Drummer("두둥맨");
 
    Pianist *pianist=0;
    for(int i = 0; i<2; i++)
    {
        pianist = dynamic_cast<Pianist *>(musicians[i]);//players[i]가 피아니스트인지 하향 캐스팅
        if(pianist)//피아니스트가 맞다면
        {
            pianist->Tuning();
        }
        musicians[i]->Play();
    }
 
    for(int i=0;i<2;i++)
    {
        delete musicians[i];
    }
    return 0;
}
 
