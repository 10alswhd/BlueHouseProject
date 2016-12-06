#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree
{
        char data;
        struct tree *left,*right;
};

int top = -1;
struct tree *stack[20]; //Creating a stack to store the nodes
struct tree *node;

//Push function

void push(struct tree* node)
{
        stack[++top]=node;
}

//Pop function

struct tree * pop()
{
        return(stack[top--]);
}


/* Displaying all node in order */

void inorder(struct tree *node)
{
        if(node!=NULL)
        {
                inorder(node->left);
                printf("%c",node->data);
                inorder(node->right);
        }
}

/* Checking operator and operands */

int check(char ch)
{
        if(ch=='+'||ch=='-'||ch=='/'||ch=='*')
                return 2;
        else
                return 1;
}

/* Making operand node and pushing into stack */

void operand(char b)
{
        node=(struct tree*)malloc(sizeof(struct tree));
        node->data=b;
        node->left=NULL;
        node->right=NULL;
        push(node);
}

/* making operator node than pop-up two nodes from stack and adding into operator node and finally push node into stack  */

void operators(char a)
{
        node=(struct tree*)malloc(sizeof(struct tree));
        node->data=a;
        node->right=pop();
        node->left=pop();
        push(node);
}

void main()
{
        int i,p,k,ans;
        char s[20];
        printf("Enter the expression in postfix form \n");
        gets(s);
        k=strlen(s);
        for(i=0; s[i]!='\0'; i++)
        {
                p = check(s[i]);
                if(p == 1)
                        operand(s[i]);
                else if(p == 2)
                        operators(s[i]);
        }
        printf("\nThe inorder traversal of the tree is \n");
        inorder(stack[top]);
}

/*
Enter the expression in postfix form:
ab*cd/+
The inorder traversal of the tree is
a*b+c/d
*/
