#include <stdio.h>
#include <math.h>
int f(double n,double c,double t)
{
  if(c*n*(log(n)/log(2.0))<=t)return 1;
  return 0;
}
int main()
{
  int c,t;
  scanf("%d%d",&c,&t );
  double low=0,high=t,n=0;
  while(low<high)
  {
    double n=(high+low)/2;
    if(f(n,c,t)==1)
      low=n;
    else high=ceil(n-1);  // for reducing absolute error
  }
  printf("%.10lf\n", low);
}
