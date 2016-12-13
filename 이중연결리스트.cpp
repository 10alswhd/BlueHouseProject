//이중 연결리스트
#include <iostream>
using namespace std;
 
class DoubledLinkedList
{
    struct Node
    {
        int data;
        Node *prev;
        Node *next;
 
        Node(int data=0)
        {
            this->data = data;
            prev = next = 0;
        }
    };
 
    Node *head;
    Node *tail;
public:
     class Iterator//연결 리스트에 보관한 데이터를 탐색하기 위한 반복자
    {
        Node *node;//현재 노드의 위치 정보
 
    public:
        friend class DoubledLinkedList;//연결리스트에서는 모든 멤버에 접근 권한 부여
 
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
 
    DoubledLinkedList()
    {
        head = new Node();//더미 노드 생성
        tail = new Node();//더미 노드 생성
        head->next = tail;
        tail->prev = head;
    }
 
    ~DoubledLinkedList()
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
       
        HangNode(node,tail);
    }
    void PushFront(int data)
    {
        Node *node = new Node(data);
        HangNode(node,head->next);
    }
    void Insert(Iterator iter,int data)
    {
        Node *node = new Node(data);
        HangNode(node,iter.node);
    }
 
    Iterator Begin()//탐색에 사용할 시작 반복자
    {
        Iterator iter(head->next);
        return iter;
    }
    Iterator End() //탐색에 사용할 마지막 반복자
    {
        Iterator iter(tail);
        return iter;
    }
    bool Erase(int data)
    {               
        Node *pos=0;
        for(pos = head->next; pos !=tail ; pos = pos->next)
        {
            if(pos->data == data)
            {
                break;
            }           
        }
 
        if(pos==tail)
        {
            return false;
        }       
 
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
       
        delete pos;
        return true;
    }
    bool Exist(int data)
    {       
        Node *seek=0;
        for(seek = head->next; seek !=tail ; seek = seek->next)
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
        for(seek = head->next; seek !=tail ; seek = seek->next)
        {
            cout<<seek->data<<" ";
        }
        cout<<endl;
    }
 
    private:
    void HangNode(Node *now,Node *pos)
    {
        now->prev = pos->prev;
        now->next = pos;
        pos->prev->next = now;
        pos->prev = now;
    }
};
 
typedef class DoubledLinkedList DList;
int main()
{
    DList dl;
    dl.PushBack(3);//3
    dl.PushBack(5);//3 5
    dl.PushBack(8);//3 5 8
    dl.PushBack(2);//3 5 8 2
    dl.PushBack(9);//3 5 8 2 9
    dl.PushBack(7);//3 5 8 2 9 7
    dl.PushFront(1);//1 3 5 8 2 9 7
    dl.ViewAll();
    dl.Erase(8);//1 3 5 2 9 7
    dl.ViewAll();
 
    DList::Iterator seek = dl.Begin();
    DList::Iterator last = dl.End();
    for(   ;seek != last; seek.MoveNext())
    {
        if(seek.GetData()==5)
        {
            break;
        }
    }
 
    dl.Insert(seek,6);//1 3 6 5 2 9 7
    dl.ViewAll();
    return 0;
}
