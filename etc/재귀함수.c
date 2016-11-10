#include <stdio.h>
void move(int from, int to)
{
   printf("%d  %d\n", from, to); 
}

void A(int n, int from, int by, int to)
{
   if(n==1)
    move(from, to);// move1
   else
   {
    A(n-1, from, to, by);          // A1
    move(from, to); // move2
    A(n-1, by, from, to);           // A2
    }
}

void main()
{
 A(3,1,2,3);
}
