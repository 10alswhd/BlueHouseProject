#include<stdio.h>
#include<conio.h>
#include<alloc.h>
struct list
{
 int data;
 struct list *next;
};
typedef struct list node;
node *create(node *p)
{
int no;
node *root;
printf("
enter the no to enter(enter -999 for termination)
");
scanf("%d", &no);
while(no!=-999)
 {
	if(p==NULL)
	{
		p=(node*)malloc(sizeof(node));
		p->data=no;
		root=p;
	}
	else
	{
		p->next=(node*)malloc(sizeof(node));
		p=p->next;
		p->data=no;
	}
	printf("
enter the no to enter
");
	scanf("%d", &no);
 }
 p->next=NULL;
return root;
}
void display(node *p)
{
clrscr();
printf("
");
if(p==NULL)
printf("
you are trying to display empty linked list
");
 while(p!=NULL)
 {
 printf("%d  ",p->data);
 p=p->next;
 }
}
node *insert(node *root,int p)
{
int j,no;
node *q,*r;
q=root;
for(j=1;j<p-1;j++)
q=q->next;
if(q==NULL)
{
   printf("
enter proper position
");
   return root;
}
else
{
q=root;
printf("
enter the no to be inserted
");
scanf("%d", &no);
if(p==1)//insertion at starting of the link list
	{
	r=(node *)malloc(sizeof(node));
	r->data=no;
	r->next=root;
	root=r;
	}
else//elsewhere incl ending
{
	for(j=1;j<p-1;j++)
	q=q->next;
	if(q->next!=NULL)
	{
	r=(node *)malloc(sizeof(node));
	r->data=no;
	r->next=q->next;
	q->next=r;
	}
	else
	{
	r=(node *)malloc(sizeof(node));
	r->data=no;
	q->next=r;
	r->next=NULL;
	}
}   }
return root;
}
node *del(node *root,int no)
{
node *q,*p;
p=root;
	if(root->data==no)
	{
	root=root->next;
	free(p);
	}
	else
	{
while(p->data!=no&&p!=NULL)
 {
 q=p;
 p=p->next;
 }
 if(p==NULL)
 {
 printf("
no entered for deletion doen't exist in link list
");
 return root;
 }
 q->next=p->next;
 free(p);
}
return root;
}
node *rev(node *root)
{
	node *s,*q,*r;
	q=root;
	r=NULL;
	while(q!=NULL)
	{
	s=r;
	r=q;
	q=q->next;
	r->next=s;
	}
	root=r;
return root;
}
void max(node *root)
{
  int max;
  node *p;
  p=root;
  max=p->data;
  while(p!=NULL)
  {
  if(p->data>max)
  max=p->data;
  p=p->next;
  }
  printf("
maximum=%d",max);
}
void min(node *root)
{
  int min;
  node *p;
  p=root;
  min=p->data;
  while(p!=NULL)
  {
  if(p->data<min)
  min=p->data;
  p=p->next;
  }
  printf("
minimum=%d",min);
}

node *search(node *r,int n)
{
	int f=0,i=1,ch;
	node *root;
	root=r;
	while(r!=NULL)
	{
		if(r->data==n)
		{
		f=1;
		printf("
entered no found at node-%d
",i);
		printf("
do you want to replace this element?
1:yes
0:no");
		scanf("%d",&ch);
		   if(ch==1)
		   {
		      printf("
enter no which you want after replacement
");
		      scanf("%d",&r->data);
		   }
		   else
		    break;
		}
		i++;
		r=r->next;
	}
	if(f==0)
	printf("
entered data for searching doesn't exists in linklist
");
return root;
}
int count(node *root)
{
	int c=0;
	node *q;
	q=root;
	clrscr();
	if(q==NULL)
	return 0;
	while(q!=NULL)
	{
	c++;
	q=q->next;
	}
	return c;
}
node *merge(node *p,node *q)
{
	node *r;
	r=p;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	  p->next=q;
	return r;
}
node *sort(node *root)
{       node *p,*q;
	int n,i,j,temp;

	p=root;
	n=count(root);
	for(i=0;i<n-1;i++)
	{
		q=p->next;
		for(j=i+1;j<n;j++)
		{
			if(p->data>q->data)
			{
			   temp=p->data;
			   p->data=q->data;
			   q->data=temp;
			}
			q=q->next;
		}
		p=p->next;
	}
	return root;
}
void main()
{
node *root=NULL,*p,*root1=NULL;
int i,pos,n,ch;
p=root;
clrscr();
do
{
printf("
-----------------------------------------------------------------------------
");
printf("
		 ***enter choice*** 
");
printf("
		<1>:create
		<2>:display
		<3>:insert
		<4>:delete
		<5>:maximum
		<6>:minimum
		<7>:reverse
		<8>:seach and replace
		<9>:count nodes
		<10>:create and merge
		<11>:sorting
		<12>:exit
");
printf("
your choice is------>");
scanf("%d",&ch);
switch(ch)
{
case 1:root=create(p);
	clrscr();
	break;
case 2:printf("
");
	display(root);
	break;
case 3:printf("
enter the position for insertion
");
	scanf("%d", &pos);
	root=insert(root,pos);
	break;
case 4:printf("
enter the no to del
");
	scanf("%d",&n);
	root=del(root,n);
	break;
case 5:max(root);
	break;
case 6:min(root);
	break;
case 7:root=rev(root);
	break;
case 8:printf("
enter the no for searching option
");
	scanf("%d",&n);
	root=search(root,n);
	break;
case 9: clrscr();
	printf("
total no of nodes=%d
",count(root));
	break;
case 10:root1=create(p);
	   clrscr();
	printf("
1:newly created linklist-->previous one
");
	printf("
0:previously created linklist-->new one
");
	scanf("%d",&i);
	if(i==1)
	root=merge(root1,root);
	else if(i==0)
	root=merge(root,root1);
	else
	printf("
wrong choice
");
	break;
case 11:root=sort(root);
	break;
case 12:printf("
		*press enter and exit*
");
	break;
default:printf("
**wrong choice**
");
	break;

}}while(ch!=12);
getch();
}
