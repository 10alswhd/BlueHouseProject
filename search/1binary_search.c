#include <stdio.h>
int binarySearch(int dizi[], int l, int r, int x)
{
   if (r >= l)
   {
        int mid = l + (r - l)/2;
        if (dizi[mid] == x)  return mid;
        if (dizi[mid] > x)   return binarySearch(dizi, l, mid-1, x);
        return binarySearch(dizi, mid+1, r, x);
   }
   return -1;
}
 
int main()
{  
   
   
   int dizi[] = { 82,96,65,63,65,6,
	94,90,69,31,34,8,52,61,73,0,17,
	46,36,95,93,96,21,16,57,59,70,
	31,39,34,13,9,55,32,99,72,57,
	72,98,43,91,90,84,5,36,30,63,
	14,37,86,25,3,100,61,24,44,
	74,56,44,60,18,81,82,49,76,
	40,73,15,51,67,15,6,34,45,76,
	13,90,22,38,42,97,18,88,55,32,
	90,54,46,81,36,97,56,77,68,21,
	83,87,4,61,27};
   
   int aranan=0; int n = sizeof(dizi)/ sizeof(dizi[0]);
   
   printf("Aradığınız elemanı giriniz: "); scanf("%d",&aranan); 
   
   int sonuc = binarySearch(dizi, 0, n-1, aranan);
   if (sonuc == -1)
   		printf("\nAranan eleman bulunamadi");
   else
   		printf("\nEleman bulundu. indis: %d", sonuc);
   return 0;
}
