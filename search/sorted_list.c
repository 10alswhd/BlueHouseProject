#include <stdlib.h>

typedef struct _t_node t_node;
struct _t_node {
    int id;
    struct _t_node* next;
};


t_node* makeNode(int id);
void freeNode(t_node* node);

static int addList(t_node* node);
static t_node* search(int id);


static t_node* s_head;
static t_node* s_tail;


t_node* makeNode(int id)
{
    t_node* node = (t_node*)malloc(sizeof(t_node));
    node->id = id;
    node->next = NULL;

    return node;
}

void freeNode(t_node* node)
{
    free(node);
}

static int addList(t_node* node)
{
    if(!node)
        return -1;

    if(!s_head) {
        s_head = s_tail = node;
        node->next = NULL;
        return 0;
    }

    t_node* prev = NULL;
    t_node* tmp = s_head;

    s_tail->next = node;
    s_tail = node;
    s_tail->next = NULL;


    return 0;

}

static t_node* search(int id)
{
    t_node* tmp = s_head;
    while(tmp) {
        if( tmp->id ==  id)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

static int delList(t_node* node)
{
    if(!node)
        return -1;

    t_node* prev =NULL;
    t_node* tmp = s_head;
    while(tmp) {
        if( tmp->id  == node->id ) {
            if( tmp == s_head ) {
                s_head = s_head->next;
            } else if ( tmp == s_tail ) {
                s_tail = tmp;
                s_tail->next = NULL;
            } else {
                prev->next = tmp->next;
            }
            goto DELETE_TARGET;
        }

       prev = tmp;
       tmp = tmp->next;
    }

    return -1;

DELETE_TARGET:
    freeNode(tmp);
    return 0;
}
