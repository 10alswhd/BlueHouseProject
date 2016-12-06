#include<stdio.h>
#include<stdlib.h>
typedef struct node {
    int val;
    struct node *next;
}List;

int Length(List *head)
{
    int len=0;
    List *current = head;
    while(current!=NULL)
    {
        len++;
        current=current->next;
    }
    return len;
}

struct node *BuildOneTwoThree()
{
    int i=3;
    List *temp=NULL,*head;
    while(i>0)
    {
        head = (List *)malloc(sizeof(struct node));
        head->next = temp;
        head->val = i;
        temp = head;
        i--;
    }
    return head;
}
Raw
 prog01.c
#include<stdio.h>
#include<ctype.h>
#include "linkedlist.c"
int Count(List *head, int searchFor);
int main(int argc,char **argv)
{
    int searchFor = 2,count;
    List *myList = BuildOneTwoThree();
    if(argc == 2)
    {
        searchFor = atoi(argv[1]);
    }
    count = Count(myList,searchFor);
    printf("The Count of %d is %d\n",searchFor,count);
    return 0;
}
int Count(List *head, int searchFor)
{
    List *current = head;
    int count = 0;
    while(current!=NULL)
    {
        if(current->val == searchFor)
            count++;
        current=current->next;
    }
    return count;
}
Raw
 prog02.c
#include<stdio.h>
#include<ctype.h>
#include "linkedlist.c"
int getNth(List *head, int index);
int main(int argc, char **argv)
{
    int index = 2,val;
    if(argc == 2)
    {
        index = atoi(argv[1]);
    }
    List *myList = BuildOneTwoThree();
    val = getNth(myList,index);
    printf("Value at %d is %d\n",index,val);
}
int getNth(List *head, int index)
{
    List *current = head;
    int i=0;
    while(current != NULL && i<index)
    {
        current = current->next;
        i++;
    }
    if(i==index)
    {
        return current->val;
    }
    else
    {
        fprintf(stderr,"List index outside the range\n");
        exit(0);
    }
}
