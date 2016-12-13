//무효화2
#include <string>
#include <iostream>
using namespace std;
class Programmer
{
public:
    void Programming()
    {
        cout<<"생각하면서 코딩을 한다."<<endl;
    }
    void Programming(int tcnt)
    {
        cout<<tcnt<<"시간 ";
        Programming();
    }
};
class EHProgrammer:public Programmer
{
public:
    void Programming(string title)//기반 형식의 Programming 메서드를 무효화시킴
    {
        cout<<"프로젝트명:"<<title<<endl;
        cout<<"생각한 것을 문서화하고 이를 보면서 코딩을 한다."<<endl;
    }
};
int main()
{
    EHProgrammer *ehp = new EHProgrammer();
    //ehp->Programming(); 기반 클래스에 같은 이름의 메서드를 무효화하여 호출할 수 없음
    ehp->Programming("도서 관리 프로그램");
    delete ehp;
    return 0;
}
