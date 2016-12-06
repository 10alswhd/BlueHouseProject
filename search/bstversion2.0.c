#include <stdio.h>
#include <malloc.h>
struct bt
{
    int data;
    struct bt *left;
    struct bt *right;
};
//creation of bst
struct bt* create(struct bt *h)
{
    struct bt *p,*q;
    int side,y=1;
    h=(struct bt *)malloc(sizeof(struct bt));
    scanf("%d",&h->data);
    h->left=NULL;
    h->right=NULL;
    while(y)
    {
        p=h;
        struct bt *t=(struct bt *)malloc(sizeof(struct bt));
        printf("enter value to be added ");
        scanf("%d",&t->data);
        t->left=NULL;
        t->right=NULL;
        while(p!=NULL)
        {
            q=p;
            if(t->data < p->data)
            {
                p=p->left;
            }
            else
            {
                 p=p->right;
            }
        }
        if(t->data <= q->data)
        {
            q->left=t;
        }
        else
        {
            q->right=t;
        }
        printf("1 to cont: ");
        scanf("%d",&y);
    }
    return h;
}
//inorder traversal
void inorder(struct bt *h)
{
    if(h == NULL)
    {
      return;
    }
   
    inorder(h->left);
     printf("%d\n",h->data);
    inorder(h->right);
}
//finds the kth smallest no
void smallest(struct bt *h,int k,int count)
{
    if(h == NULL)
    {
      return;
    }
   
    smallest(h->left,k,count);
    count++;
    if(count==k)
     printf("%d\n",h->data);

 
    smallest(h->right,k,count);
}

//my way of finding no of leaf nodes
/*void leaf(struct bt* h)
{
    if(h==NULL)
    {
      return;
    }
   leaf(h->left);
   if(h->left==NULL&&h->right==NULL)
    printf("7\n");
leaf(h->right);
}*/
//this is for no of leaf nodes but how it works 
unsigned int getLeafCount(struct bt* node)
{
  if(node == NULL)       
    return 0;
  if(node->left == NULL && node->right==NULL)      
    return 1;            
  else
    return getLeafCount(node->left)+
           getLeafCount(node->right);      
}
//searching a value in bst but its also giving wrong output for some values
int search(struct bt *h ,int n)
{    
     struct bt *p,*q;
     p=h;
      do
        {
            q=p;
            if(n <= p->data)
            {
                p=p->left;
            }
            else
            {
                 p=p->right;
            }
        }while(p!=NULL);
        if(n == q->data)
        {
            return 1;
        }
        else
        {
            return -1;
        }

} 
//this checks whether thhe tree is bst or not
void isBST(struct bt* root)
{
    static struct bt *prev = NULL;
     
    if (root)
    {
        return isBST(root->left);
    
        if (prev != NULL && root->data <= prev->data)
          printf("no");
 
        prev = root;
 
        return isBST(root->right);
    }
 
    printf("yes its a bst\n");
}

int main()
{
    struct bt *head,*m;
   m= head=create(head);
    inorder(head);
    printf("enter the value u wanna search\n");
    int t;
    scanf("%d",&t);
    int p;
    p=search(head,t);
    printf("%d",p);
    isBST(head);
    int count=0;
    printf("enter the kth smallest value u wanna search\n");
    int k;
    scanf("%d",&k);
    smallest(head,k,count);
      printf("Leaf count of the tree is %d", getLeafCount(m));
   

    return 0;
}
