//원형 큐
#include <iostream>
using namespace std;
 
class Queue
{
    int *buffer;
    const int size;
    int front;
    int rear;
 
public:
    Queue(int size):size(size)
    {       
        buffer = new int[size];
        front = rear = 0;
    }
    ~Queue()
    {
        delete[] buffer;
    }
 
    bool Put(int data)
    {
        if(IsFull())
        {
            return false;
        }
        buffer[rear] = data;
        rear = Next(rear);
        return true;
    }
    int Get()
    {
        if(IsEmpty())
        {
            return 0;
        }
        int re = buffer[front];
        front = Next(front);
        return re;
    }
    bool IsFull()
    {
        return Next(rear) == front;
    }
    bool IsEmpty()
    {
        return front == rear;
    }
private:
    int Next(int now)
    {
        return (now+1)%size;
    }
};
 
int main()
{
    Queue q(10);//크기가 10인 큐
 
    q.Put(4); //4
    q.Put(7); //4 7
    q.Put(8); //4 7 8
    q.Put(2); //4 7 8 2
 
    while(q.IsEmpty() == false)
    {
        cout<<q.Get()<<" ";
    }
    cout<<endl;
    return 0;
