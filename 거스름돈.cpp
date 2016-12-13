#include <iostream>
using namespace std;
 
enum MType
{
    One=1, Five=5, Ten=10, Fifty=50,Hun=100,FHun=500,
    Thous=1000,FTh=5000, TenTh=10000,FTenTh=50000
};
 
 
class Calculator
{
    static const MType mtypes[10];
    MType money;
    int value;
    int remain;
    int marr[10];
public:
    Calculator(MType money, int value)
    {
        this->money = money;
        this->value = value;
        remain = money - value;
    }
    void Calulate()
    {
        cout<<"가격:"<<value<<", 받은 돈:"<<money<<", 거슬러 줄 돈:"<<remain<<endl;
        for(int i=0; i<10; i++)
        {
            marr[i] =CountChange(mtypes[i]);
            if(marr[i])
            {
                cout<<mtypes[i]<<"원 권:"<<marr[i]<<"개, 남은 돈:"<<remain<<endl;
            }
        }
       
    }
private:
    int CountChange(MType howmuch)
    {
        int cnt = 0;
        while(remain>=howmuch)
        {
            remain -= howmuch;
            cnt++;
        }
        return cnt;
    }
};
 
const MType Calculator::mtypes[10]={FTenTh,TenTh,FTh,Thous,FHun,Hun,Fifty,Ten,Five,One};
 
 
int main()
{
    Calculator calculator(TenTh,1723);
    calculator.Calulate();
    return 0;
}
 
 
