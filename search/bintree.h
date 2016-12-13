#ifndef __BINTREE_H__
#define __BINTREE_H__

/* left>right unbalanced tree */
typedef struct bintree_t {
    struct bintree_t *left;
    struct bintree_t *right;
    int               node;
} bintree_t;


bintree_t *newBT(int i);
int Bsearch(bintree_t *t, int i);
void Binsert(bintree_t *t, int i);
void Bdelete(bintree_t *t);


#endif  /* __BINTREE_H__ */
