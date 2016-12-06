#include <stdio.h>
#include <math.h>

int main()
{
    int sayi, orijinal_sayi, kalan, sonuc = 0, n = 0 ;

    printf("Bir sayi giriniz: ");
    scanf("%d", &sayi);

    orijinal_sayi = sayi;
    
    while (orijinal_sayi != 0)
    {
        orijinal_sayi /= 10;
        ++n;
    }

    orijinal_sayi = sayi;

    while (orijinal_sayi != 0)
    {
        kalan = orijinal_sayi%10;
        sonuc += pow(kalan, n);
        orijinal_sayi /= 10;
    }

    if(sonuc == sayi)
        printf("%d Armstrong sayidir.", sayi);
    else
        printf("%d  Armstrong sayi degildir.", sayi);

    return 0;
}
