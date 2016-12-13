//스택
#include <iostream>
using namespace std;
 
class Stack
{
    int *buffer;
    const int size;
    int top;
public:
    Stack(int size):size(size)
    {
        top = -1;
        buffer = new int[size];
    }
 
    ~Stack()
    {
        delete[] buffer;
    }
 
    bool Push(int data)
    {
        if(IsFull())
        {
            return false;
        }
        top++;
        buffer[top] = data;
        return true;
    }
 
    int Pop()
    {
        if(IsEmpty())
        {
            return 0;
        }
        int re = buffer[top];
        top--;
        return re;
    }
    bool IsFull()
    {
        return (top+1) == size;
    }
 
    bool IsEmpty()
    {
        return top == -1;
    }
};
 
int main()
{
    Stack st(10);//크기가 10인 스택
 
    st.Push(4); //4
    st.Push(7); //4 7
    st.Push(8); //4 7 8
    st.Push(2); //4 7 8 2
 
    while(st.IsEmpty() == false)
    {
        cout<<st.Pop()<<" ";
    }
    cout<<endl;
    return 0;
}
