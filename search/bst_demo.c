/**
 * Binary search tree, a C implementation.
 *
 * I hope it could be a bit more efficient ;)
 *
 * @blackball
 */
#include <stdlib.h>

/* for futher use */
#define Malloc(sz)  malloc(sz)
#define Free(p ,sz) free(p)

#define _C(n) bst_##n

#ifdef __cplusplus
#define EXTERN_BEGIN extern "C" {
#define EXTERN_END   }
#else
#define EXTERN_BEGIN 
#define EXTERN_END   
#endif

EXTERN_BEGIN

#define T int /* node type */
typedef struct
{
  T v;
  /* Rational operator will return
   * 0 for false, and 1 for true, we 
   * could use this for a little
   * optimization.
   */
  struct node *link[2];
} node;

#define _Init(n, d)                             \
  (n) = (node*)Malloc(sizeof(node));            \
  (n)->v = d;                                   \
  (n)->link[0] = (n)->link[1] = NULL


void _C(insert)( node **root, T v )
{
  node *rt   = *root, *prev = NULL;
  
  if ( !rt ) /* tree is empty */
  {
    _Init(*root, v);
  }
  else
  {
    for ( ; rt; rt = rt->link[ v > rt->v ] )
    {
      /* if exists, do nothing */
      if ( v == rt->v ) return;
      prev = rt;
    }
    _Init(rt, v);
    prev->link[ v > prev->v ] = rt;
  }
}

node* _C(serach)( node **root, T v )
{
  node *rt = *root, *out = NULL;
  while ( rt )
  {
    if ( v == rt->v )
    {
      out = rt;
      break;
    }
    /* step down to proper child tree */
    rt = rt->link[ v > rt->v ];
  }
  return out;
}

void _C(remove)( node **root, T v )
{
  int pos;
  node *curr = *root, *prev = *root, *ptr = NULL;

  /* search v */
  
  for ( ; curr; curr = curr->link[ v > curr->v ] )
  {
    /* if exists */
    if ( v == curr->v ) break;
    
    prev = curr;
  }

  /* not exists */
  if ( !curr ) return ;

  /*
   * NULL  && NULL  --> 0 :leaf
   * !NULL && NULL  --> 1 :only left
   * NULL  && !NULL --> 2 :only right
   * !NULL && !NULL --> 3 :both
   */
  pos = (curr->link[0] != NULL) + ((curr->link[1] != NULL ) << 1);

  ptr = curr;
  switch ( pos )
  {
    case 0:
    case 1:
    case 2:
      if (curr == *root) /* it's the root node */
      {
        (*root) = curr->link[pos > 1];
      }
      else
      {
        prev->link[v > prev->v] = curr->link[pos > 1];
      }
      break;
      
    case 3:
      /* find inorder predecessor */
      ptr = curr->link[0];
      while (ptr->link[1])
      {
        ptr = ptr->link[1];
      }
      curr->v = ptr->v;
  }

  Free(ptr, sizeof(node));
  ptr = NULL;
}

void _C(destroy)(node **root)
{
  node *rt = *root;

  if (rt)
  {
    _C(destroy)(&(rt->link[0]));
    _C(destroy)(&(rt->link[1]));
    Free(rt, sizeof(node));
    rt = NULL;
  }
}

EXTERN_END

#undef _Init
#undef _C
