#include <stdio.h> 
#include <stdlib.h>

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void selectionSort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				swap(a[i], a[j]);
			}
		}
	}
}

int main()
{
	int list[30],i;
	for (i = 0; i < 30; i++)
		list[i] = rand();
	printf("ORIGINAL LIST:\n\n");
	for (i = 0; i < 30; i++)
		printf("%d\n",list[i]);
	selectionSort(list, 30);
	printf("\nSORTED LIST:\n\n");
	for (i = 0; i < 30; i++)
		printf("%d\n", list[i]);
	return 0;
}
