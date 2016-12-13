#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
struct node
{
int d;
struct node *n,*p;
}*h,*t,*q,*tmp,*r;
int c=0;
void create()
{
tmp=(struct node*)malloc(sizeof(struct node));
tmp->p=tmp->n=NULL;
printf("\nenter the data:");
scanf("%d",&tmp->d);
c++;
}
void insb()
{
if(h==NULL)
{
create();
t=h=tmp;
}
else
{
create();
tmp->n=h;
h->p=tmp;
h=tmp;
}
}
void inse()
{
if(h==NULL)
{
create();
t=h=tmp;
}
else
{
create();
t->n=tmp;
tmp->p=t;
t=tmp;
}
}
void ins()
{
int pos,i=2;
printf("\nenter position:");
scanf("%d",&pos);
q=h;
if((h==NULL)&&(pos==1))
{
create();
h=t=tmp;
return;
}
else
{
while(i<pos)
{
q=q->n;
i++;
}
create();
tmp->p=q;
tmp->n=q->n;
q->n->p=tmp;
q->n=tmp;
}
}
void del()
{
int i=1,pos;
printf("\nenter the position:");
scanf("%d",&pos);
q=h;
if(h==NULL)
{
printf("\nlist is empty!!!");
return;
}
else
{
while(i<pos)
{
q=q->n;
i++;
}
if(q->n==NULL)
{
if(i==1)
{
printf("\nnode deleted!");
free(q);
q=h=NULL;
return;
}
else
{
q->p->n=NULL;
free(q);
return;
}
}
q->n->p=q->p;
if(i!=1)
q->p->n=q->n;
if(i==1)
h=q->n;
free(q);
}
c--;
}
void dispend()
{
printf("\nreverse order of the list:");
q=t;
while(q->p!=NULL)
{
printf("\t%d",q->d);
q=q->p;
}
printf("\t%d",q->d);
}
void dispbeg()
{
q=h;
if(q==NULL)
{
printf("\nlist empty!!!");
return;
}
printf("\nlist elements from beginning:");
while(q->n!=NULL)
{
printf("\t%d",q->d);
q=q->n;
}
printf("\t%d",q->d);
}
void searchbeg()
{
int data,c=0;
q=h;
if(q==NULL)
{
printf("\nlist is empty!!!");
return;
}
printf("\nenter element to be searched:");
scanf("%d",&data);
while(q!=NULL)
{
if(q->d==data)
{
printf("\nelement %d is present in position %d!",data,c+1);
return;
}
else
q=q->n;
c++;
}
printf("\nelement not found!!!");
}
void searchend()
{
int data,c=0;
q=t;
if(q==NULL)
{
printf("\nlist is empty!!!");
return;
}
printf("\nenter element to be searched:");
scanf("%d",&data);
while(q!=NULL)
{
if(q->d==data)
{
printf("\nelement %d is present in position %d!",data,c+1);
return;
}
else
q=q->p;
c++;
}
printf("\nelement not found!!!");
}
void main()
{
int ch;
clrscr();
printf("\n  doubly linked list!!!");
h=t=tmp=NULL;
while(ch!=9)
{
printf("\nmenu:\n1.insert at beginning\n2.insert at end\n3.insert at any position\n4.delete\n5.display from beginning\n6.display from end\n7.search from beginning\n8.search from end\n9.exit\nenter your choice:");
scanf("%d",&ch);
switch(ch)
{
case 1:insb();break;
case 2:inse();break;
case 3:ins();break;
case 4:del();break;
case 5:dispbeg();break;
case 6:dispend();break;
case 7:searchbeg();break;
case 8:searchend();break;
case 9:exit(0);break;
default:printf("\ninvalid entry!!!");
}
}
getch();
}
