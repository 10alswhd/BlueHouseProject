#include <stdio.h>
#include <stdlib.h>
#define MAX 1000001

int search[MAX]={0};

void swap(int*,int*);
int n(int, int);


int main(void)
{
	int first = 1;
	int i, j;
	n(1,MAX );
	while(scanf("%d %d",&i ,&j)!=EOF)
	{
		if(i == 0 || j ==0)
			exit(0);
		if(first == 1)
		{
			printf("%d %d ",i ,j);
			first = 0;
		}
		else
			printf("\n%d %d ",i ,j);
		swap(&i,&j);
		printf("%d",n(i,j));
	}
	return 0;
}

void swap(int *a, int*b)
{
	int temp;

	if(*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

int n(int a, int b)
{
	int max;
	int i; /*INDEX*/
	long long int j; /*n*/

	max = 0;
	for(i=a;i<=b;i++)
	{
		if(search[i] == 0)
		{
			search[i] = 1;
			j = (long long int)i;
			while(j != 1)
			{
				if(j % 2 == 1)
					j = 3*j+1;
				else
					j = j / 2;
				if(j < MAX-1 )
				{
					if(search[j]!=0)
					{
						search[i]+=search[j];
						break;
					}
				}
				search[i]++;
			}
		}

		if(search[i] > max)
			max = search[i];
	}

	return max;
}
