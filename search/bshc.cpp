/*
 *=========================*
 *                         *
 *           NOTE          *
 *                         *
 *==========================
 先排序，然后insert的时候，直接接到最右子节点那里，否则测试数据鬼畜的时候，直接退化为N^2！
 */
/*
 描述
 Read the statement of problem G for the definitions concerning trees. In the following we define the basic terminology of heaps. A heap is a tree whose internal nodes have each assigned a priority (a number) such that the priority of each internal node is less than the priority of its parent. As a consequence, the root has the greatest priority in the tree, which is one of the reasons why heaps can be used for the implementation of priority queues and for sorting.
 
 A binary tree in which each internal node has both a label and a priority, and which is both a binary search tree with respect to the labels and a heap with respect to the priorities, is called a treap. Your task is, given a set of label-priority-pairs, with unique labels and unique priorities, to construct a treap containing this data.
 输入
 The input contains several test cases. Every test case starts with an integer n. You may assume that 1<=n<=50000. Then follow n pairs of strings and numbers l1/p1,...,ln/pn denoting the label and priority of each node. The strings are non-empty and composed of lower-case letters, and the numbers are non-negative integers. The last test case is followed by a zero.
 输出
 For each test case output on a single line a treap that contains the specified nodes. A treap is printed as (< left sub-treap >< label >/< priority >< right sub-treap >). The sub-treaps are printed recursively, and omitted if leafs.
 */




#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct node
{
    int priority;
    char lable[8];
    node* right;
    node* left;
    node* parent;
};

int scale;
node storage[50010];

bool mycompare(node a, node b)
{
    if (strcmp(a.lable, b.lable) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void left_rotate(node* now, node** root_ptr)
{
    node* formal_parent = now -> parent;
    formal_parent -> right = now -> left;
    if (formal_parent -> right)
    {
        formal_parent -> right -> parent = formal_parent;
    }
    now -> parent = formal_parent -> parent;
    if (now -> parent)
    {
        if (now -> parent -> left && now -> parent -> left == formal_parent)
        {
            now -> parent -> left = now;
        }
        else
        {
            now -> parent -> right = now;
        }
    }
    else
    {
        *root_ptr = now;
    }
    now -> left = formal_parent;
    formal_parent -> parent = now;
}

void right_rotate(node* now, node** root_ptr)
{
    node* formal_parent = now -> parent;
    formal_parent -> left = now -> right;
    if (formal_parent -> left)
    {
        formal_parent -> left -> parent = formal_parent;
    }
    now -> parent = formal_parent -> parent;
    if (now -> parent)
    {
        if (now -> parent -> left && now -> parent -> left == formal_parent)
        {
            now -> parent -> left = now;
        }
        else
        {
            now -> parent -> right = now;
        }
    }
    else
    {
        *root_ptr = now;
    }
    now -> right = formal_parent;
    formal_parent -> parent = now;
}

void insert(node* root, node* now, node** root_ptr)
{
    /*
    node* search = root;
    // insert following BST rules
    for (;;)
    {
        if (strcmp(now -> lable, search -> lable) > 0)
        {
            // to right node
            if (search -> right == NULL)
            {
                search -> right = now;
                now -> parent = search;
                break;
            }
            else
            {
                search = search -> right;
            }
        }
        else
        {
            // to left node
            if (search -> left == NULL)
            {
                search -> left = now;
                now -> parent = search;
                break;
            }
            else
            {
                search = search -> left;
            }
        }
    }
     */
    now -> parent = now - 1;
    (now - 1) -> right = now;
    // reorder following maximum heap rules
    while (now -> parent && now -> parent -> priority < now -> priority)
    {
        if (now -> parent -> left == now)
        {
            right_rotate(now, root_ptr);
        }
        else
        {
            left_rotate(now, root_ptr);
        }
    }
}

void traverse(node* root)
{
    // (< left sub-treap >< label >/< priority >< right sub-treap >)
    printf("(");
    if (root -> left)
    {
        traverse(root -> left);
    }
    printf("%s/%d", root -> lable, root -> priority);
    if (root -> right)
    {
        traverse(root -> right);
    }
    printf(")");
}

int main()
{
    for (;;)
    {
        scanf("%d", &scale);
        if (scale == 0)
        {
            break;
        }
        //storage = new node[scale];
        for (int i = 0; i < scale; i++)
        {
            scanf("%*[ ]%[^/]/%d", storage[i].lable, &(storage[i].priority));
            storage[i].left = NULL;
            storage[i].right = NULL;
            storage[i].parent = NULL;
            
        }
        sort(storage, storage + scale, mycompare);
        node* root;
        root = storage;
        
        for (int i = 1; i < scale; i++)
        {
            insert(root, storage + i, &root);
        }
        
        traverse(root);
        printf("\n");
        
        //delete []storage;
    }
}
