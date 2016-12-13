#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linkedlist.h"

typedef enum
{
    FROM_LAST=0,FROM_FIRST
}Sortorder;

void Link(Node**,Node**,Node**,Node**,Node**,Node**);
void QuickSort(Node*,Node*,Cmp);
void Sort_part(Node**,Node**,Node*,Node*,Node*,Sortorder,Cmp);
void Swap(void**,void**);
Node* Shift(Node*,int*);

void Add_list(void* new_data,List* use,int kind)
{
    Node* a=(Node*)calloc(1,sizeof(Node));
    a->value=calloc(1,use->datasize);
    memcpy(a->value,new_data,use->datasize);
    if(kind==HEAD)
        Link(&a,&a->last,&a->next,&use->head,&use->head->last,&use->tail);
    else
        Link(&a,&a->next,&a->last,&use->tail,&use->tail->next,&use->head);
}

void Link(Node** use,Node** p_use,Node** op_use,Node** side,Node** p_side, Node** other_side)
{
    *op_use=*side;
    if(*other_side==NULL)
        *other_side=*use;
    if(*side!=NULL)
        *p_side=*use;
    *side=*use;
    *p_use=NULL;
}

Node* Search_list(List* data,Cmp Using,void* key)
{
    Node* use=data->head;
    while(use!=NULL)
    {
        if((*Using)(use->value,key)==0)
            break;
        use=use->next;
    }
    return use;
}

int Delete_list(List* data,Cmp Using,void* key)
{
    Node* use=Search_list(data,*Using,key);
    if(use==NULL)
        return FALSE;
    if(data->head==use)
        data->head=use->next;
    if(data->tail==use)
        data->tail=use->last;
    if(use->next!=NULL)
        use->next->last=use->last;
    if(use->last!=NULL)
        use->last->next=use->next;
    free(use->value);
    free(use);
    return SUCCESS;
}

inline int Edit_list(List* data,Cmp Using,void* key,void Edit(void*))
{
    Node* use=Search_list(data,*Using,key);
    if(use==NULL)
        return FALSE;
    (*Edit)(use->value);
    return SUCCESS;
}

void Check_head_and_tail(List* data)
{
    while(UNLIMITED)
    {
        if(data->head->last!=NULL)
            data->head=data->head->last;
        if(data->tail->next!=NULL)
            data->tail=data->tail->next;
        if(data->head->last==NULL&&data->tail->next==NULL)
            break;
    }
}

void QuickSort(Node* head,Node* tail,Cmp Using)
{
    Node* use=head;
    Node* start=head;
    Node* finish=tail;
    if(head==NULL||tail==NULL||head==tail||tail->next==head)
        return;
    while(UNLIMITED)
    {
        Sort_part(&use,&tail,head,start,finish,FROM_LAST,Using);
        Sort_part(&use,&head,tail,start,finish,FROM_FIRST,Using);
        if(tail==head) break;
    }
    QuickSort(start,use->last,Using);
    QuickSort(use->next,finish,Using);
}


void Sort_part(Node** use,Node** other,Node* other_side,Node* head,Node* tail,Sortorder order,Cmp Using)
{
    int swap=0;
    while(UNLIMITED)
    {
        if(*other==NULL) break;
        swap=Using((*use)->value,(*other)->value);
        if(order==FROM_FIRST&&swap<-1)
        {
            Swap(&(*use)->value,&(*other)->value);
            *use=*other;
            break;
        }
        if(order==FROM_LAST&&swap>1)
        {
            Swap(&(*use)->value,&(*other)->value);
            *use=*other;
            break;
        }
        if(other_side==*other)
            break;
        else if(order==FROM_FIRST) *other=(*other)->next;
        else if(order==FROM_LAST) *other=(*other)->last;
    }
}

inline void Swap(void** use,void** other)
{
    void* temp=*use;
    *use=*other;
    *other=temp;
}

int Insert_list(List* data,int Input(void*))
{
    Node* a=(Node*)calloc(1,sizeof(Node));
    a->value=calloc(1,data->datasize);
    int order=(*Input)(a->value);

    Node* use=data->head;
    use=Shift(use,&order);
    if(order>0)
        return FALSE;
    if(use==NULL)
        Link(&a,&a->next,&a->last,&data->tail,&data->tail->next,&data->head);
    else if(use==data->head)
        Link(&a,&a->last,&a->next,&data->head,&data->head->last,&data->tail);
    else
    {
        a->last=use->last;
        a->next=use;
        use->last->next=a;
        use->last=a;
    }
}

Node* Shift(Node* use,int* order)
{
    while((*order)--&&order!=NULL)
    {
        use=use->next;
    }
    return use;
}
