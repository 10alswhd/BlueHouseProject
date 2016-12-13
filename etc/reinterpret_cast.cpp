

//reinterpret_cast
#include <iostream>
#include <iomanip>
#include <string>
 
using namespace std;
 
int main()
{
   
    float f=-12.625;
    float *pf = &f;
    int *a;
 
    a = reinterpret_cast<int *>(pf);
    cout<<hex<<(*a)<<endl;
    return 0;
}
