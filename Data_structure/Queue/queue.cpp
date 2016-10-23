#include<stdio.h>
class Queue
{
private:
    class node
    {
    public:
        int data;
        node *next;
        node()
        {
            next=NULL;
        }
    }*head,*tail;
    int Size=0;
public:
    Queue();
    void Push(int n);
    int Front();
    void Pop();
    int size();
};
Queue::Queue()
{
    head=tail=NULL;
    Size=0;
}
void Queue::Push(int n)
{
    Size++;
    node *temp;
    temp =new node();
    temp->data=n;
    if(head==NULL)
    {
        head=temp;
        tail=temp;
        return;
    }
    tail->next=temp;
    tail=temp;
}
int Queue::Front()
{
    node *temp=head;
    return temp->data;
}
void Queue::Pop()
{
    Size--;
    node *temp=head;
    head=head->next;
    delete(temp);
}
int Queue::size()
{
    return Size;
}
int main()
{
    Queue a;
    a.Push(12);
    a.Push(100);
    a.Push(102);
    printf("front %d\n",a.Front());
    a.Pop();
    printf("front %d\n",a.Front());
    return 0;
}
