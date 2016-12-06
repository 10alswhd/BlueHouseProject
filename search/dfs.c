#include<stdio.h>

int vis[10]={0};

void dfs(int arr[][10],int x,int n)
{
	int i;
	printf("%d ",x);
	vis[x]=1;
	for(i=0;i<n;i++)
	{
		if(arr[x][i]==1 && vis[i]!=1 && x!=i)
			dfs(arr,i,n);
	}
}

int main()
{

	int arr[10][10],i,j,n;

	printf("Enter number of nodes\n");
	scanf("%d",&n);


	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&arr[i][j]);
		}
	}

	dfs(arr,0,n);
	printf("\n");
}
