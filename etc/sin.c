#include <stdio.h>
#include <math.h>

 
double Fac(int n);
double SignAngle(int angle)
{
     int i;
     double rad = (angle%180)/180.0;
     double mul=0;
     int sign = 1;

 

     for(i=1 ; i<10 ; i++) //급수를 크게 두지 않아도 오차가 그리 크지 않음을 확인할 수 있다.
     {
         mul = mul + sign *pow(rad,2*i-1)/Fac(2*i-1);             
         sign = -1 * sign;
     }
     return mul;
}

 

double Fac(int n)
{
    double re = 1.0;
    while(n)
    {
        re = re *n;
        n--;
    }
    return re;
}

 

//테스트하는 부분이다.

int main()
{
     
     int x;
     double mul=0;

     for(x=0 ; x<360 ; x=x+10)

     {
         printf("%5.5f %5.5f\n",SignAngle(x),sin((x%180)/180.0));
     }
}

