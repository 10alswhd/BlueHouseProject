#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void display(int a[]);
int cmp(void *a,void *b);
int main(void)
{
	int a[MAX] = {8 ,9 ,7 ,1 ,5 ,4 ,3 , 0, 2, 6 };
	display(a);
	qsort(a,MAX,sizeof(int),cmp);
	display(a);
	int key = 44;
	int *searchResult;
	searchResult = bsearch( &key,a,MAX,sizeof(int),cmp);
	if( searchResult != NULL)
	{
		printf("%d found ",*searchResult);
	}
	else
	{
		printf("Not found %d",key);
	}


	return 0;
}

void display(int a[])
{
	int i =0;
	while(i<MAX)
	{
		printf("%d ",a[i++]);
	}
	printf("\n");
}

int cmp(void *a,void *b)
{
//	if ( *((int *)a) <  *((int *)b)) return -1;
//	if ( *((int *)a) ==  *((int *)b)) return 0;
//	return 1;
	return *((int *)a) -  *((int *)b);
}
