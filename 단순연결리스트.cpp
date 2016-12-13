//단순 연결리스트
#include <iostream>
using namespace std;
class SimpleLinkedList
{
    struct Node //단순 연결리스트의 노드
    {
        int data;
        Node *next;
        Node(int data=0)
        {
            this->data = data;
            next = 0;
        }
    };
    Node *head; //연결리스트 맨 앞 노드의 위치 정보
    Node *tail;   //연결리스트 맨 뒤 노드의 위치 정보
public:
    class Iterator//연결 리스트에 보관한 데이터를 탐색하기 위한 반복자
    {
        Node *node;//현재 노드의 위치 정보
    public:
        friend class SimpleLinkedList;//연결리스트에서는 모든 멤버에 접근 권한 부여
        Iterator(Node *node=0)
        {
            this->node = node;
        }
        int GetData()const //현재 노드에 보관한 자료 접근자
        {
            if(node==0)//현재 노드가 없을 때
            {
                throw "유효한 노드를 가리키고 있지 않습니다.";
            }
            return node->data;
        }
        bool MoveNext()//다음 노드의 위치로 이동
        {
            if(node->next)//다음 노드가 있을 때
            {
                node = node->next;//다음 노드 위치 정보로 변경
                return true;
            }
            return false;
        }
        bool operator==(const Iterator &iter)//같은지 판별
        {
            return node == iter.node;
        }
        bool operator!=(const Iterator &iter)//다른지 판변
        {
            return node != iter.node;
        }
    };
    SimpleLinkedList()
    {
        head = 0;
        tail = 0;
    }
 
    ~SimpleLinkedList()
    {
        Node *prev=0;
        while(head !=0)
        {           
            prev = head;
            head = head->next;
            delete prev;
        }
    }
 
    void PushBack(int data)
    {
        Node *node = new Node(data);
        if(head==0)//비어있을 때
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }
    void PushFront(int data)
    {
        Node *node = new Node(data);
        if(head==0)//비어있을 때
        {
            head = tail = node;
        }
        else
        {
            node->next = head;
            head = node;
        }
    }
    void InsertNext(Iterator iter,int data)
    {
        Node *node = new Node(data);
        Node *prev = iter.node;
        if(prev==0)//이전 노드가 없을 때
        {
            if(head)//연결리스트에 보관한 자료가 있을 때
            {               
                prev->next = head;
                head = prev;
            }
            else//연결리스트에 보관한 자료가 없을 때
            {
                head = tail = node;
            }            
        }
        else//이전 노드가 있을 때
        {
            node->next = prev->next;
            prev->next = node;
            if(prev == tail)//이전 노드가 tail일 때
            {
                tail = node;
            }
        }
    }
 
    Iterator Begin()//탐색에 사용할 시작 반복자
    {
        Iterator iter(head);
        return iter;
    }
 
    Iterator End() //탐색에 사용할 마지막 반복자
    {
        Iterator iter(0);
        return iter;
    }
   
    bool Erase(int data)
    {       
        Node *prev=0;
        Node *seek=0;
        for(seek = head; seek !=0 ; seek = seek->next)
        {
            if(seek->data == data)//찾는 데이터가 있을 때
            {
                break;
            }
            prev = seek;
        }
 
        if(seek==0)//찾는 데이터가 없을 때
        {
            return false;
        }       
        if(prev)//이전 노드가 있을 때
        {
            prev->next = seek->next;
        }
        else//이전 노드가 없을 때
        {
            head = seek->next;
        }
        if(seek == tail)//지워야 할 노드가 맨 마지막 노드일 때
        {
            tail = prev;
        }
 
        delete seek;
        return true;
    }
 
    bool Exist(int data)
    {       
        Node *seek=0;
        for(seek = head; seek !=0 ; seek = seek->next)
        {
            if(seek->data == data)
            {
                return true;
            }
        }
        return false;
    }
 
    void ViewAll()const
    {       
        Node *seek=0;
        for(seek = head; seek !=0 ; seek = seek->next)
        {
            cout<<seek->data<<" ";           
        }
        cout<<endl;
    }
};
 
typedef class SimpleLinkedList SList;
int main()
{
    SList sl;
    sl.PushBack(3);//3
    sl.PushBack(5);//3 5
    sl.PushBack(8);//3 5 8
    sl.PushBack(2);//3 5 8 2
    sl.PushBack(9);//3 5 8 2 9
    sl.PushBack(7);//3 5 8 2 9 7
    sl.PushFront(1);//1 3 5 8 2 9 7
    sl.ViewAll();
    sl.Erase(8);//1 3 5 2 9 7
    sl.ViewAll();
 
    SList::Iterator seek = sl.Begin();
    SList::Iterator last = sl.End();
    for(   ;seek != last; seek.MoveNext())
    {
        if(seek.GetData()==5)
        {
            break;
        }
    }
 
    sl.InsertNext(seek,6);//1 3 5 6 2 9 7
    sl.ViewAll();
    return 0;
}
