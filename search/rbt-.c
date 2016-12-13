#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"


#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

struct rbt_node {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

static rbt left_rotate(rbt r) {
    rbt temp = r;
    r = r->right;
    temp->right = r->left;
    r->left = temp;
    return r;
}

static rbt right_rotate(rbt r) {
    rbt temp = r;
    r = r->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}

static rbt rbt_fix(rbt r) {
  if(IS_RED(r->left)){
    if(IS_RED(r->left->left)){
      if(IS_RED(r->right)){
        r->colour = RED;
        r->left->colour = BLACK;
        r->right->colour = BLACK;
      }else if(IS_BLACK(r->right)){
        r=right_rotate(r);
        r->colour = BLACK;
        r->right->colour = RED;
      }
    } else if (IS_RED(r->left->right)) {
      if(IS_RED(r->right)){
        r->colour=RED;
        r->left->colour = BLACK;
        r->right->colour = BLACK;
      }else if(IS_BLACK(r->right)){
        r->left = left_rotate(r->left);
        r = right_rotate(r);
        r->colour = BLACK;
        r->right->colour = RED;
      }
    }
  } else if(IS_RED(r->right)) {
    if (IS_RED(r->right->left)) {
      if (IS_RED(r->left)) {
        r->colour = RED;
        r->left->colour = BLACK;
        r->right->colour = BLACK;
      } else if (IS_BLACK(r->left)) {
        r->right = right_rotate(r->right);
        r = left_rotate(r);
        r->colour = BLACK;
        r->right->colour = RED;
      }
    }else if (IS_RED(r->right->right)) {
       if (IS_RED(r->left)){
          r->colour = RED;
          r->left->colour= BLACK;
          r->right->colour = BLACK;
       }
       else if (IS_RED(r->right)) {
          r = left_rotate(r);
          r->colour = BLACK;
          r->left->colour = RED;
       }
    }
 }
 return r;
}


rbt rbt_delete(rbt b, char *str) {
  /*If finding key to delete doesn't exist return tree un modified*/
  if(0 == rbt_search(b, str)) {
    return b;
  } else if (strcmp(str, b->key) == 0){
    /*if string exists in the current node then splice it out */
    /*three cases where we splice out a node*/
    if( b->left == NULL && b->right == NULL) { /*1. node is a leaf:*/
       free(b->key); /*free the key*/
       free(b);      /*free the node*/
       b = NULL;     /*set the node to NULL*/
    } else if (b->left == NULL && b->right != NULL ) {
      free(b->key);
      free(b);
      b = b->right;
    } else if (b->left != NULL && b->right == NULL ) {
      free(b->key);
      free(b);
      b = b->left;
    } else { /*Node has two children so we find success in right left most subtree*/
      rbt successor = b->right;
      while (successor->left != NULL) {
        successor = successor->left;
      }
      b->key = successor->key; /*swap keys*/
      b = rbt_delete(b, successor->key); /*delete key from right subtree*/
    }
  } else if (strcmp(str, b->key) < 0) {
    b->left = rbt_delete(b->left, str);
  } else if (strcmp(str, b->key) > 0) {
    b->right = rbt_delete(b->right, str);
  }
  return b;
}

void rbt_inorder(rbt b, void f(char *str)) {
  if(NULL == b){ /*Base case to stop recursion*/
    return;
  }
  rbt_inorder(b->left, f);  /*inorder traverse left subtree*/
  f(b->key);                /*apply the function to the key*/
  if (IS_RED(b)) {
    f("=> RED \n");
  } else if (IS_BLACK(b)) {
    f("=> BLACK \n");
  }
  rbt_inorder(b->right, f); /*inorder traverse right subtree*/
}

rbt rbt_insert(rbt b, char *str) {
  /*
  if tree is empty allocate memory and copy in the key and return result
  else a key already exists
  */
  if (b == NULL) {
    b = emalloc(sizeof *b);
    b->key = emalloc((strlen(str) + 1) * sizeof  str[0]);
    b->colour = RED;
    strcpy(b->key, str);
    return b;
  }
  else if (strcmp(str, b->key) == 0) { /*if key is same then do nothing as duplicates aren't aloud*/
  }
  else if (strcmp(str, b->key) < 0) { /*if inserting key is smaller then insert into left subtree.*/
    b->left = rbt_insert(b->left, str);
  }
  else if (strcmp(str, b->key) > 0) {
    b->right = rbt_insert(b->right, str);
  }
  b = rbt_fix(b);
  return b;
}

rbt rbt_new() {
  return NULL;
}

void rbt_preorder(rbt b, void f(char *str)) {
  if (NULL == b) {
    return;
  }
  f(b->key);
  if (IS_RED(b)) {
    f("=> RED \n");
  } else if (IS_BLACK(b)) {
    f("=> BLACK \n");
  }
  rbt_preorder(b->left, f);
  rbt_preorder(b->right, f);
}

int rbt_search(rbt b, char *str) {
  /*if key tree is null return 0*/
  if (NULL == b) {
    return 0;
  }
  /*if the key in the current node is our key then return 1*/
  if (strcmp(b->key, str) == 0) {
    return 1;
  }
  /*if nodes key is to big return result of searching left subtree*/
  if(strcmp(str, b->key) < 0) {
    return rbt_search(b->left, str);
  }
  /*if nodes key is to small return result of searching righ subtree*/
  if(strcmp(str, b->key) > 0) {
    return rbt_search(b->right, str);
  }
  return 0;
}
