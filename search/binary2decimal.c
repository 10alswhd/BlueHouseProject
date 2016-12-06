include <stdio.h>
#include <math.h>
int Binary2Decimal(long long n);

int main()
{
    long long n;
    printf("Binary sayi giriniz: ");
    scanf("%lld", &n);
    printf("%lld binary sayisinin Decimal karsiligi = %d ", n, Binary2Decimal(n));
    return 0;
}

int Binary2Decimal(long long n)
{
    int decimal_sayi = 0, i = 0, kalan;
    while (n!=0)
    {
        kalan = n%10;
        n /= 10;
        decimal_sayi += kalan*pow(2,i);
        ++i;
    }
    return decimal_sayi;
}
