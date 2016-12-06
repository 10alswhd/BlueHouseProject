/*
ID: jason281
LANG: C
TASK: ariprog
*/
//Arithmetic Progressions

//Write a program that finds 
//all arithmetic progressions 
//of length n in the set S of 
//bisquares. The set of bisquares 
//is defined as the set of all 
//integers of the form p2 + q2 
//(where p and q are non-negative integers).
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
void swap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
	return;
}
void sort(int *set,int start,int end)
{
	if(end<=start)
		return;
	int i,pivot_p,pivot_v;
	pivot_v=set[end];
	pivot_p=start;
	for(i=start;i<end;i++)
	{
		if(set[i]>=pivot_v)
			continue;
		else
		{
			swap(&set[pivot_p],&set[i]);
			pivot_p++;
		}
	}
	swap(&set[end],&set[pivot_p]);
	sort(set,start,pivot_p-1);
	sort(set,pivot_p+1,end);
	return;
} 
int search1(int a,int start,int end,int set[])
{
	int mid;
	if(start>=end)
	{
		if(a==set[start])
			return start;
		else if(a==set[end])
			return end;
		else
			return 0;
	}
	else
	{
		mid=(end+start)/2;
		if(a==set[mid])
			return mid;
		else if(a>set[mid])
			return search1(a,mid+1,end,set);
		else
			return search1(a,start,mid-1,set);
	}
}
int search(int a,int n,int set[])
{
	int i;
	for(i=0;i<n;i++)
		if(a==set[i])
			return a;
	return 0;
}
int main()
{
	FILE *fin  = fopen ("ariprog.in", "r");
    FILE *fout = fopen ("ariprog.out", "w");
	int n,m,num,t;
	fscanf(fin,"%d",&m);
	fscanf(fin,"%d",&n);
	num=(n+1)*(n+2)/2;
	int set[num],result[100][2];
	int i,j,k,count=0;
	for(i=0;i<=n;i++)
		for(k=i;k<=n;k++)
		{
			if(search(i*i+k*k,count,set)!=0)
				continue;
			set[count++]=i*i+k*k;
		}
//	fprintf(fout,"%d\n",count);
	sort(set,0,count-1);
	num=count;//nosame(set,0,count-1);
//	for(i=0;i<count;i++)
//		fprintf(fout,"%d\n",set[i]);
	count=0;	
	for(i=1;i<=((m<10)?(2*n*n/(m-1)+1):(2*n*n/(m-1)/4+1));i++)
	{
		for(k=0;k<num;k++)
		{
			t=k;
			for(j=1;j<m;j++)
			{
				if(set[k]+((m<10)?(i*j):(i*j*4))>2*n*n)
					break;
				else if(t=search1(set[k]+((m<10)?(i*j):(i*j*4)),t,num-1,set)==0)
					break;
				else if(j==m-1)
				{
					result[count][0]=set[k];
					result[count++][1]=((m<10)?(i):(4*i));
				}
			}
		}
	}
//	fprintf(fout,"%d\n",count);
	if(count==0)
		fprintf(fout,"NONE\n");
	for(i=0;i<count;i++)
		fprintf(fout,"%d %d\n",result[i][0],result[i][1]);
	return 0;
}
