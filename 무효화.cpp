
//무효화
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
};
class EHProgrammer:public Programmer
{
public:
    void Programming()//기반 형식의 Programming 메서드를 무효화시킴
    {
        cout<<"생각한 것을 문서화하고 이를 보면서 코딩을 한다."<<endl;
    }
};
 
int main()
{
    EHProgrammer *ehp = new EHProgrammer();
    ehp->Programming();   
    delete ehp;
    return 0;
}
