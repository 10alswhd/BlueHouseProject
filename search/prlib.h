#ifndef PRLIB_H_INCLUDED
#define PRLIB_H_INCLUDED
//isPrime returns its integer argument if the argument is a prime,or 0 in case it 's not a prime.
int isPrime(int n)
{
   int i, count = 0;

   for(i = 2; i < n; i++)

      if(n % i )
        count += 1;
   if(count == n - 2)
        return (n);
   else
    return (0) ;
}

int combo1(int p1,int p2)
{

    int sum= p1 + p2 - 1 ;
    int i;
    if(isPrime(sum))
        return (1) ;
    else
        return (0) ;

}

#endif // PRLIB_H_INCLUDED //telling if a number is prime or not.(also includes a combo1 function).
