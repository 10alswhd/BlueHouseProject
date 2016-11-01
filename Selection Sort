#include <stdio.h>

 void selectsort(int x[], int n) 

 {

	  int i, indx, j, large;

	  for(i=0; i<n; i++) 

	  {

		  large = x[i]; indx = i;

		  for(j=i+1; j<n; j++)

			  if (x[j] < large) 

			  { 

			  large = x[j]; indx = j; printf("a=%d \n ",x[j]);

			  }

		  x[indx] = x[i];

		  x[i] = large; 

	  }

 

 }

 int main(void)

  {

  int dizi[8] = {25, 57, 48, 37, 12, 92, 86, 33};

  selectsort( &dizi[0], 8);

  for(int i=0;i<8;i++) printf("%d\n ",dizi[i]);

  return 0;

 }
