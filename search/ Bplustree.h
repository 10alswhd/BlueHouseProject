#ifndef __BPLUSTREE_H__
#define __BPLUSTREE_H__

#define LENGTH 3                   /* the length of each node */

/* from Wikipedia -- B+ tree */
/* If nodes of the B+ tree are organised as arrays of elements, then it may take a considerable time to insert or delete an element as half of the array will need to be shifted on average. To overcome this problem elements inside a node can be organized in a binary tree or a B+ tree instead of an array. */

/* note */
/* the leaves of the B+ trees don't have a link to another leaf */




/* record */
typedef struct {
    int key;
    char *rec_value;
} record_t;


/* B+ tree */
typedef struct Bplustree_t {
    struct bintree_t *keynode; /* keys are managed as a binary tree */
    struct Bplustree_t *child[LENGTH]; /* child trees */
    struct record_t *records[LENGTH]; /* records */
} Bplustree_t;




record_t *newREC(char *rec_val);
Bplustree_t *newBPtree(void);
Bplustree_t BPinsert(Bplustree_t *tree, record_t *r);
char *BPselect(Bplustree_t *tree, int key);          /* return rec_value */
void BPdelete(Bplustree_t *tree, int key);


#endif  /* __BPLUSTREE_H__ */
