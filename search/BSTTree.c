#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef struct treenode{

    int data;
    struct treenode * left;
    struct treenode * right;
  
}treenode;

typedef struct BST{

    treenode * head;
    int count;
  
}BST;

typedef struct queue{
    
    treenode * list [MAX];
    int front;
    int rear;
    
}queue;

queue * createqueue(){
    
    queue * nodepath;
    nodepath = (queue*)malloc(sizeof(queue));
    nodepath->front = 0;
    nodepath->rear = 0;
    return nodepath;
    
}

void initializequeue(queue * nodepath){
    
    int i;
    nodepath->front = 0;
    nodepath->rear = 0;
    
    for(i=0;i< MAX; i++){
        
        nodepath->list[i] = NULL;
    }
}

void push(queue * nodepath , treenode * root, int front){
    
    nodepath->front = nodepath->front + 1;
    nodepath->list[front] =   root;
    
}

treenode * pop(queue * nodepath , treenode * root, int rear){
    
    root = nodepath->list[rear];
    nodepath->rear = nodepath->rear + 1;
    return root;
}

void display(queue * nodepath, treenode * root){
    
    while(root != NULL){
        
    printf("%d\n", root->data);
    
    if(root->left != NULL){
        
        push(nodepath , root->left, nodepath-> front);
    }
    
    if(root->right != NULL){
        
        push(nodepath , root->right, nodepath->front);
        
    }
    
    root = pop(nodepath , root, nodepath->rear);
    display(nodepath , root);
    
    }
    
    return;
}

BST * createtree(){
  
    BST * bt;
    bt = (BST*)malloc(sizeof(BST));
    bt->head = NULL;
    bt->count = 0;
    return bt;
  
}

void initialize (BST * bt, treenode * root){
    
    bt->head = root;
    bt->count = 1;
}

treenode * createnode(int number){
        
    treenode * newnode;
    newnode = (treenode*)malloc(sizeof(treenode));
    newnode->data = number;
    newnode->right = NULL;
    newnode->left = NULL;
    return newnode;
 
}

 
void insert(treenode * root, treenode * newnode, int number ){
    
    if(root->data > number){
        if(root->left!= NULL){
          insert(root->left, newnode, number);
        }
      
        else{
          root->left = newnode;
        }
    }
  
    else{
        if(root->right!=NULL){
          insert(root->right, newnode, number);
        }
      
        else{
          root->right = newnode;
        }
    }
}

int findnode(treenode * root, treenode * delnode){
        
    while(delnode->right != NULL){
            
            delnode = delnode->right;
            
    }
    
    if(delnode->data < root->data){
        
        root->left = NULL;
    }
    
    else{
        
        root->right = NULL;
    }
    
    return delnode->data;

}

void deletenode(treenode * root, treenode * delnode, int number){
    
    if(delnode->data > number){
        
        root = delnode;
        deletenode(root, delnode->left, number);
        
    }
    
    else if(delnode->data < number){
        
        root = delnode;
        deletenode(root, delnode->right, number);
        
    }
    
    else if(delnode->data == number){
        
        if(delnode->left == NULL && delnode->right == NULL){
            
            if(root->data<number){
                
                root->right = NULL;
            }
            
            else{
                
                root->left = NULL;
                
            }
        }
        
        else if(delnode->right = NULL){
            
            if(root->data<number){
                
                root->right = delnode->left;
                
            }
            
            else{
                
                root->left = delnode->left;
                
            }
        }
        
        else if(delnode->left ==  NULL){
            
            if(root->data<number){
                
                root->right = delnode->right;
            }
            
            else{
                
                root->left = delnode->right;
            }
        }
        
        else{
            
            number = findnode(delnode,delnode->left);
            delnode->data = number;
            
        }
    }
    
    else{
        
        return;
    }
}


int main(){
    
    BST * bt;
    treenode * root, * newnode;
    queue * nodepath;
    nodepath = createqueue();
    bt = createtree();
    root = bt->head;
    root = createnode(16);
    initialize(bt, root);
    initializequeue(nodepath);
    newnode = createnode(10);
    insert(root, newnode, 10);
    newnode = createnode(19);
    insert(root, newnode, 19);
    newnode = createnode(20);
    insert(root, newnode, 20);
    newnode = createnode(8);
    insert(root, newnode, 8);
    newnode = createnode(12);
    insert(root, newnode, 12);
    newnode = createnode(17);
    insert(root, newnode, 17);
    newnode = createnode(18);
    insert(root, newnode, 18);
    deletenode(root, root, 17);
    display(nodepath, root);
    return 0;
    
}
