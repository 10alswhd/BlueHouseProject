#include<stdio.h>
#include<stdlib.h>
#include<string.h>

	
typedef struct node
{
	char a[50];
	struct node *link;
}
*NODE;
	
#define MALLOC(p,n,type)\
	p=(type*)malloc(n*sizeof(type));\

void display(NODE first)
{
	NODE temp=first;
	
	if(temp==NULL)
	{
		printf("\nThe linked list is empty\n");
	}
	else
	{
		while(temp!=NULL)
		{
			printf("\n%s\n",temp->a);
			temp=temp->link;
		}
	}
}

NODE insert(char x[50], NODE first)
{
	NODE temp;
	NODE cur = first;
	
	int k=0;
	
	MALLOC(temp,1,struct node);
	
	while(x[k]!='\0')
	{
		(temp->a[k])=x[k];
		k++;
	}
	
	temp->a[k]='\0';
	
	temp->link=NULL;
	
	if(first==NULL)
		return temp;
	else
	{
		while(cur->link!=NULL)
			cur=cur->link;
			
		cur->link=temp;
		
		return first;
	}
}

int search(char x[50], NODE first)
{
	NODE temp=first;
	
	
	
	
	if(temp==NULL)
	{
		printf("\nList is empty\n");
		return -1;
	}
	else
	{
		do
		{
			if(strcmp(temp->a,x)==0)
				return 1;
			else
			{
				temp=temp->link;
			}
		}
		while(temp!=NULL);
		
		return -1;
	}
}
		
		
		
	
				
				
			
			

int main()
{
	NODE a = NULL;
	NODE b = NULL;
	NODE c = NULL;
	NODE d = NULL;
	
	char x[50];
	
	int ans=0;
	
	
	
	a=insert("jan",a);
	a=insert("feb",a);
	a=insert("mar",a);
	
	b=insert("apr",b);
	b=insert("may",b);
	b=insert("jun",b);
	
	c=insert("jul",c);
	c=insert("aug",c);
	c=insert("sep",c);
	
	d=insert("oct",d);
	d=insert("nov",d);
	d=insert("dec",d);
	
	printf("\nEnter month to search for\n");
	scanf("%s",x);
	
	do
	{
		ans=search(x,a);
		
		if(ans==1)
		{
			printf("\nFound\n");
			display(a);
			break;
		}
		
		
			ans=search(x,b);
		
			if(ans==1)
			{
				printf("\nFound\n");
				display(b);
				break;
			}
		
		
			ans=search(x,c);
		
			if(ans==1)
			{
				printf("\nFound\n");
				display(c);
				break;
			}
		
			ans = search(x,d);
		
			if(ans==1)
			{	
				printf("\nFound\n");
				display(d);
				break;
			}
		
		
	}
	while(ans==0);
	
	if(ans==-1)
	printf("\nNot found\n");
	
}
