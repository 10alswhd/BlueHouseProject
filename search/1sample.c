#include <stdlib.h>

typedef struct _t_node t_node;
struct _t_node {
    int id;
    struct _t_node* next;
};


t_node* makeNode(int id);
void freeNode(t_node* node);

static int delList(t_node* node);
static int addListWithSort(t_node* node);
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

static int addListWithSort(t_node* node)
{
    if(!node)
        return -1;

    if(!s_head) {
        s_head = node;
        return 0;
    }

    t_node* prev = NULL;
    t_node* tmp = s_head;

    while(tmp) {
        if( tmp->id > node->id) {
            if( tmp == s_head ) {
                node->next = s_head;
                s_head = node;
            } else {
                prev->next = node;
                node->next = tmp;
            }
            break; 
        }
        prev = tmp;
        tmp = tmp->next;
    }

    if(!tmp) {
        prev->next = node;
        s_tail = node;
    }

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
            } else if ( tmp->next == NULL ) {
                s_tail = tmp;
                s_tail->next = NULL;
            } else {
                prev->next = tmp->next;
            }
            freeNode(tmp);
            return 0;
        }

       prev = tmp;
       tmp = tmp->next;
    }

    return -1;
}
