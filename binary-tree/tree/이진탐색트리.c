#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node//노드 정의
{
    int data;
    struct Node *lchild;
    struct Node *rchild;
}Node;
 
typedef Node *Tree;//트리 형식명 정의
 
Node *NewNode(int data);//노드 생성
void InitTree(Tree *bst);//트리 초기화
int AddData(Tree *bst, int data); //데이터 보관
void Preorder(Node *sr);//전위 순위 운행
void Inorder(Node *sr);//중위 순위 운행
void Postorder(Node *sr);//후위 순위 운행
void ClearTree(Tree *bst);//트리 해제
int main(void)
{
    Tree tree;
 
    InitTree(&tree);//트리 초기화
 
                    //트리에 자료 보관
    AddData(&tree, 10);
    AddData(&tree, 6);
    AddData(&tree, 9);
    AddData(&tree, 5);
    AddData(&tree, 15);
    AddData(&tree, 25);
    AddData(&tree, 3);
    AddData(&tree, 19);
    AddData(&tree, 14);
 
    //트리에 보관한 자료 확인
    printf("전위 순위 운행:");
    Preorder(tree);
    printf("\n중위 순위 운행:");
    Inorder(tree);
    printf("\n후위 순위 운행:");
    Postorder(tree);
 
    //트리 해제
    ClearTree(&tree);
    printf("\n");
}
Node *NewNode(int data)
{
    Node *now = (Node *)malloc(sizeof(Node));
    now->data = data;
    now->lchild = now->rchild = NULL;
    return now;
}
 
void InitTree(Tree *bst)
{
    *bst = NULL;
}
 
int AddData(Tree *bst, int data)
{
    Node *seek = *bst;
    int gap = 0;
    if (seek == NULL)
    {
        (*bst) = NewNode(data);
        return 1;//보관 성공 반환
    }
    while (1)
    {
        gap = seek->data - data;
        if (gap == 0)//이미 같은 값의 데이터를 보관했음
        {
            return 0;//보관 실패 반환
        }
        if (gap>0)//기존 데이터가 클 때(들어갈 데이터가 작을 때)
        {
            if (seek->lchild)//왼쪽에 자식이 이미 있으면
            {
                seek = seek->lchild;//seek를 왼쪽 자식으로 설정
            }
            else
            {
                seek->lchild = NewNode(data);//왼쪽 자식으로 새로운 노드를 설정
                return 1;//보관 성공 반환
            }
        }
        else//기존 데이터가 작을 때(들어갈 데이터가 클 때)
        {
            if (seek->rchild)//오른쪽에 자식이 이미 있으면
            {
                seek = seek->rchild;//seek를 오른쪽 자식으로 설정
            }
            else
            {
                seek->rchild = NewNode(data);//오른쪽 자식으로 새로운 노드를 설정
                return 1;//보관 성공 반환
            }
        }
 
    }
    return 1;
}
void Preorder(Node *sr)//전위 순위 운행
{
    if (sr)
    {
        printf("%d ", sr->data);
        Preorder(sr->lchild);
        Preorder(sr->rchild);
    }
}
void Inorder(Node *sr)//중위 순위 운행
{
    if (sr)
    {
        Inorder(sr->lchild);
        printf("%d ", sr->data);
        Inorder(sr->rchild);
    }
}
void Postorder(Node *sr)//후위 순위 운행
{
    if (sr)
    {
        Postorder(sr->lchild);
        Postorder(sr->rchild);
        printf("%d ", sr->data);
    }
}
void Dispose(Node *sr);
void ClearTree(Tree *bst)
{
    Dispose(*bst);
    *bst = 0;
}
void Dispose(Node *sr)//후위 순위로 해제
{
    if (sr)
    {
        Dispose(sr->lchild);
        Dispose(sr->rchild);
        free(sr);
    }
}
