#include <CppUTest/TestHarness.h>

extern "C"{
typedef struct _t_node t_node;
struct _t_node {
    int id;
    struct _t_node* next;
};
#include <stdlib.h>
}

static t_node* s_head =  NULL;
static t_node* s_tail =  NULL;

TEST_GROUP(ListTestGroup)
{
    void setup()
    {
        s_head = NULL;
        s_tail = NULL;
    };

    void teardown()
    {
    };
};


static int addList(void);
static void delList(int id);

static int addList(void)
{
    t_node* node = (t_node*)malloc(sizeof(t_node));
    if( !s_head ) {
        s_head = s_tail = node; 
        node->id = 0;
        node->next = NULL;
        return  node->id;
    }

    int id = 0;
    for( id = 0; id < 10000; id++) {
        t_node* prev = NULL;
        t_node* tmp = s_head;

        while(tmp) {
            if( tmp->id == id)
                break;

            if( tmp->id > id) {
                if( tmp == s_head ) {
                    node->next = s_head;
                    s_head = node;
                    node->id = id;
                } else {
                    prev->next = node;
                    node->next = tmp;
                    node->id = id;
                }
                goto FOUND;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if( !tmp ) {
            node->id = id;
            s_tail->next = node;
            s_tail = node;
            s_tail->next = NULL;
            goto FOUND;
        }
    }

    return -1;
    
FOUND:
    return node->id;
}

static void delList(int id)
{
    if ( id < 0 )
        return;

    t_node* prev = NULL;
    t_node* tmp = s_head;
    while(tmp) {
        if(tmp->id == id){
            if( tmp == s_head ) {
                s_head = s_head->next;
            } else if ( tmp == s_tail ) {
                s_tail = prev;
                s_tail->next = NULL;
            } else {
                prev->next = tmp->next;
            }
            tmp->next=NULL;
            free(tmp);
            break;
        }

        prev = tmp;
        tmp = tmp->next;
    }
}





TEST(ListTestGroup, makeNodeAndFree)
{
    int result = -1;

    POINTERS_EQUAL(NULL, s_head);
    POINTERS_EQUAL(NULL, s_tail);

    result = addList();
    CHECK_EQUAL(0, result);
    CHECK_EQUAL(0, s_head->id);
    CHECK_EQUAL(0, s_tail->id);

    result = addList();
    CHECK_EQUAL(1, result);
    delList(1);

    POINTERS_EQUAL(NULL, s_head->next);
    

    result = addList();
    CHECK_EQUAL(1, result);

    delList(1);


    delList(0);
}

TEST(ListTestGroup, list)
{
    int result = -1;
    POINTERS_EQUAL(NULL, s_head);
    POINTERS_EQUAL(NULL, s_tail);

    result = addList();
    CHECK_EQUAL(0, result);
    CHECK_EQUAL(0, s_head->id);
    CHECK_EQUAL(0, s_tail->id);

    result = addList();
    CHECK_EQUAL(1, result);
    CHECK_EQUAL(0, s_head->id);
    CHECK_EQUAL(1, s_tail->id);

    delList(0);
    CHECK_EQUAL(1, s_head->id);
    CHECK_EQUAL(1, s_tail->id);

    result = addList();
    CHECK_EQUAL(0, result);
    delList(0);

    delList(1);
}

TEST(ListTestGroup, list2)
{
    int result = -1;
    POINTERS_EQUAL(NULL, s_head);
    POINTERS_EQUAL(NULL, s_tail);

    result = addList();
    CHECK_EQUAL(0, result);
    CHECK_EQUAL(0, s_head->id);
    CHECK_EQUAL(0, s_tail->id);

    result = addList();
    CHECK_EQUAL(1, result);

    result = addList();
    CHECK_EQUAL(2, result);

    result = addList();
    CHECK_EQUAL(3, result);

    result = addList();
    CHECK_EQUAL(4, result);

    delList(2);

    result = addList();
    CHECK_EQUAL(2, result);


    delList(1);
    delList(0);
    delList(3);
    delList(4);

    delList(2);
}
