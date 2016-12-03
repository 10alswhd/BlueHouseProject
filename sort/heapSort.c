#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
void downheap( int dizi[], int k, int N) 
{
int T=dizi[k-1];
	while ( k<=N/2) 
	{
	int j=k+k;
	if( (j<N) && ( dizi[j-1]<dizi[j] ) ) j++;
		if ( T>=dizi[j-1]) break;
		else 
		{ 
		dizi[k-1]=dizi[j-1]; 
		k= j;
		}
	}
dizi[k-1]=T;
}
void heapsort ()
{
	int dizi[5] = {9,5, 8, 3, 1 };
	int N=5; int x;
	//en buyuk elaman. bul en ba.a al
	for (int k=N/2;k>0;k--) downheap(&dizi[0],k,N);
	// kucukten buyu.e s.ralama icin
		do 
		{
		x=dizi[0]; dizi[0]=dizi[N-1]; dizi[N-1]=x; --N;
		downheap(&dizi[0], 1,N); //en buyuk elaman sona at.l.yor
		} 
		while (N>1);
	 for(int i=0;i<5;i++) printf("%d\n ",dizi[i]);
}
 int main() 
 {
 heapsort();
 }
