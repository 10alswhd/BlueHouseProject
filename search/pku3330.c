#include<stdio.h>

int gcd(int m, int n)
{
  return m % n == 0 ? n : gcd(n, m % n);
}

int min(int a, int b)
{
  return a > b ? b : a;
}

int max(int a, int b)
{
  return a < b ? b : a;
}

typedef int id;

typedef struct __rational_number {
  int num, den;
} rational;

void rational_reduction(rational *r)
{
  int g = gcd(r->num, r->den);
  r->num /= g;
  r->num /= g;
}

int rational_cmp(rational p, rational q)
{
  int l = p.den * q.den / gcd(p.den, q.den);
  int pn = p.num * l / p.den;
  int qn = q.num * l / q.den;
  return pn - qn;
}

typedef struct __structure {
  id left, right;
} structure;

int structure_cmp(structure p, structure q)
{
  if(p.left != q.left)
    return p.left < q.left ? -1 : 1;
  if(p.right != q.right)
    return p.right < q.right ? -1 : 1;
  return 0;
}

typedef struct __binary_tree_map_structure {
  structure key;
  id value;
  struct __binary_tree_map_structure *left, *right;
} map;

int map_size;
map map_heap[4096];
map *structs_map;

map *map_insert(map **mp, structure tr, id val)
{
  if(*mp == NULL) {
    (*mp) = &map_heap[map_size++];
    (*mp)->value = val;
    (*mp)->left = (*mp)->right = NULL;
    (*mp)->key = tr;
    return *mp;
  } else {
    int c = structure_cmp((*mp)->key, tr);
    map *p;
    if(c > 0) {
      p = map_insert(&((*mp)->right), tr, val);
      if(p != NULL) (*mp)->right = p;
    } else if(c < 0) {
      p = map_insert(&((*mp)->left), tr, val);
      if(p != NULL) (*mp)->left = p;
    }
    return NULL;
  }
}

id map_search(map *mp, structure tr)
{
  if(mp == NULL) {
    return -1;
  } else {
    int c = structure_cmp(mp->key, tr);
    if(c == 0) {
      return mp->value;
    } else if(c > 0) {
      return map_search(mp->right, tr);
    } else {
      return map_search(mp->left, tr);
    }
  }
}

struct __set_int_node {
  int key;
  struct __set_int_node *left, *right;
};

typedef struct __binary_tree_set_int {
  struct __set_int_node *root;
  struct __set_int_node set_heap[256];
  int set_size;
} set;

struct __set_int_node *__set_insert(set *st, struct __set_int_node **node, int key)
{
  if(*node == NULL) {
    *node = &(st->set_heap[st->set_size++]);
    (*node)->key = key;
    (*node)->left = (*node)->right = NULL;
    return *node;
  } else {
    struct __set_int_node *r;
    if((*node)->key == key) return NULL;
    if((*node)->key < key) {
      r = __set_insert(st, &((*node)->right), key);
      if(r != NULL) (*node)->right = r;
    } else {
      r = __set_insert(st, &((*node)->left), key);
      if(r != NULL) (*node)->left = r;
    }
    return NULL;
  }
}

void set_insert(set *st, int key)
{
  __set_insert(st, &(st->root), key);
}

int __set_search(set *st, struct __set_int_node *node, int key)
{
  if(node == NULL) {
    return -1;
  } else {
    if(node->key == key) return 1;
    if(node->key < key) {
      return __set_search(st, node->right, key);
    } else {
      return __set_search(st, node->left, key);
    }
  }
}

int set_search(set *st, int key)
{
  return __set_search(st, st->root, key);
}

void __set_merge(set *dst, struct __set_int_node *node)
{
  if(node == NULL) return;
  set_insert(dst, node->key);
  __set_merge(dst, node->right);
  __set_merge(dst, node->left);
}

void set_merge(set *dst, set *src)
{
  __set_merge(dst, src->root);
}

void __set_similarity(set *tr, struct __set_int_node *p, set *left, set *right, int *n)
{
  int el, er;
  if(p == NULL) return;
  el = set_search(left, p->key);
  er = set_search(right, p->key);
  if(el == 1 && er == 1) *n += 1;
  __set_similarity(tr, p->right, left, right, n);
  __set_similarity(tr, p->left, left, right, n);
}

rational set_similarity(set *tr, set *left, set *right)
{
  int n = 0;
  rational ret;
  __set_similarity(tr, tr->root, left, right, &n);
  ret.num = n;
  ret.den = tr->set_size;
  return ret;
}

typedef struct __node {
  struct __node *left, *right;
  rational similarity;
  set structs;
  id struct_id;
} tr_node;

int node_count;
tr_node node_heap[256];

void node_init(tr_node *node, tr_node *left, tr_node *right)
{
  node->left = left;
  node->right = right;
  if(left == NULL) {
    node->struct_id = 0;
    node->structs.root = NULL;
    node->structs.set_size = 0;
    set_insert(&node->structs, 0);
    node->similarity.num = 0;
    node->similarity.den = 1;
  } else {
    id p;
    structure tr;
    tr.left = min(left->struct_id, right->struct_id);
    tr.right = max(left->struct_id, right->struct_id);
    p = map_search(structs_map, tr);
    if(p == -1) {
      node->struct_id = map_size+1;
      map_insert(&structs_map, tr, map_size+1);
    } else {
      node->struct_id = p;
    }
    node->structs.root = NULL;
    node->structs.set_size = 0;
    set_merge(&node->structs, &left->structs);
    set_merge(&node->structs, &right->structs);
    node->similarity = set_similarity(&node->structs, &left->structs, &right->structs);
    set_insert(&node->structs, node->struct_id);
  }
}

int node_cmp(tr_node *p, tr_node *q)
{
  tr_node *pmx, *pmn, *qmx, *qmn;
  int c;

  c = rational_cmp(p->similarity, q->similarity);
  if(c > 0) {
    return 1;
  } else if(c < 0) {
    return -1;
  }

  if(p->left == NULL) {
    return 0;
  }

  if(node_cmp(p->left, p->right) > 0) {
    pmx = p->right;
    pmn = p->left;
  } else {
    pmx = p->left;
    pmn = p->right;
  }
  if(node_cmp(q->left, q->right) > 0) {
    qmx = q->right;
    qmn = q->left;
  } else {
    qmx = q->left;
    qmn = q->right;
  }

  c = node_cmp(pmx, qmx);
  if(c != 0) return c;
  c = node_cmp(pmn, qmn);
  if(c != 0) return c;

  return 0;
}

void fix_print(tr_node *p, int left)
{
  tr_node *pl, *pr;
  int c;
  if(p->left == NULL) {
    putchar('x');
    return;
  }

  c = node_cmp(p->left, p->right);
  if(c == 1) {
    pl = left ? p->right : p->left;
    pr = left ? p->left : p->right;
  } else {
    pl = left ? p->left : p->right;
    pr = left ? p->right : p->left;
  }

  putchar('(');
  fix_print(pl, 1);
  putchar(' ');
  fix_print(pr, 0);
  putchar(')');
}

tr_node *parse()
{
  char c;
  while(isspace(c = getchar())) { }
  if(c == 'x') {
    tr_node *ret = &node_heap[node_count++];
    node_init(ret, NULL, NULL);
    return ret;
  } else if(c == '0') {
    return NULL;
  } else if(c == '(') {
    tr_node *left, *right, *ret;
    left = parse();
    right = parse();
    ret = &node_heap[node_count++];
    node_init(ret, left, right);
    while((c = getchar()) != ')') { }
    return ret;
  }
}

int main()
{
  tr_node *tree;
  map_size = 0;
  structs_map = NULL;
  while(tree = parse()) {
    fix_print(tree, 1);
    puts("");
    node_count = 0;
  }
  return 0;
}
