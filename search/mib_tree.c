/*
* This file is part of SmartSNMP
* Copyright (C) 2014, Credo Semiconductor Inc.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned short oid_t;

#define ARRAY_SIZE(a)  (sizeof(a)/sizeof(a[0]))
#define SNMP_TAG_NO_ERR          0x0
#define SNMP_TAG_NO_SUCH_OBJ     0x80
#define SNMP_TAG_END_OF_MIB_VIEW 0x82

struct mib_node {
  const char *name;
  int sub_id_cnt;
  int sub_id_cap;
  oid_t *sub_id;
  void **sub_ptr;
};

static struct mib_node dummy_root = {
  "",
  0,
  1,
  NULL,
  NULL
};

static oid_t *
oid_dup(const oid_t *oid, size_t len)
{
  int i;
  oid_t *new_oid = malloc(len * sizeof(oid_t));
  if (new_oid != NULL) {
    for (i = 0; i < len; i++) {
      new_oid[i] = oid[i];
    }
  }

  return new_oid;
}

int
oid_cmp(const oid_t *src, size_t src_len, const oid_t *target, size_t tar_len)
{
  int ret = 0;

  while (src_len && tar_len && !(ret = (int)(*src++ - *target++))) {
    src_len--;
    tar_len--;
    continue;
  }

  if (!ret)
    return src_len - tar_len;
  else
    return ret;
}

oid_t *
oid_cpy(oid_t *oid_dest, const oid_t *oid_src, size_t len)
{
  oid_t *dest = oid_dest;

  while (len-- > 0) {
    *dest++ = *oid_src++;
  }

  return oid_dest;
}

int
oid_binary_search(oid_t *arr, size_t len, oid_t target)
{
  int low = -1;
  int high = len;

  assert(high >= 0);
  while (low + 1 < high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] > target) {
      high = mid;
    } else {
      low = mid;
    }
  }

  if (arr[low] != target || low == -1)
    return -low - 2;
  else
    return low;
}

struct oid_search_result {
  /* Return oid */
  oid_t *oid;
  size_t id_len;
  /* Return status */
  int exist_status;
};

struct mib_node *
mib_tree_get(const oid_t *oid, size_t id_len, struct oid_search_result *ret_oid)
{
  struct mib_node *node;
  
  node = &dummy_root;
  ret_oid->oid = (oid_t *)oid;
  ret_oid->id_len = id_len;

  while (node != NULL && id_len > 0) {
    int i = oid_binary_search(node->sub_id, node->sub_id_cnt, *oid);
    if (i >= 0) {
      /* Match */
      node = node->sub_ptr[i];
      oid++;
      id_len--;
      continue;
    } else {
      /* Not match */
      ret_oid->exist_status = SNMP_TAG_NO_SUCH_OBJ;
      return NULL;
    }
  }

  ret_oid->exist_status = SNMP_TAG_NO_ERR;
  return node;
}

#define OID_MAX_LEN  64

struct node_backlog {
  /* node to be backlogged */
  struct mib_node *node;
  /* next sub-id index of the node */
  int n_idx;
};

static void
nbl_push(struct node_backlog *nbl, struct node_backlog **top, struct node_backlog **buttom)
{
  if (*top - *buttom < OID_MAX_LEN) {
    (*(*top)++) = *nbl;
  }
}

static struct node_backlog *
nbl_pop(struct node_backlog **top, struct node_backlog **buttom)
{
  if (*top - *buttom > 0)
    return --*top;
  else
    return NULL;
}

/* Test a newly allocated mib node. */
static inline int
is_leaf(struct mib_node *node)
{
  return node->sub_id[0] == 0 && node->sub_id_cnt == 0;
}

struct mib_node *
mib_tree_get_next(const oid_t *orig_oid, size_t orig_id_len, struct oid_search_result *ret_oid)
{
  oid_t *oid;
  size_t id_len;
  struct node_backlog *top, *buttom, nbl_stack[OID_MAX_LEN];
  struct node_backlog *p_nbl, nbl;
  struct mib_node *node;
  int immediate;

  /* Init something */
  ret_oid->oid = oid_dup(orig_oid, orig_id_len);
  ret_oid->id_len = orig_id_len;
  oid = ret_oid->oid;
  id_len = ret_oid->id_len;
  ret_oid->exist_status = SNMP_TAG_NO_ERR;
  top = buttom = nbl_stack;
  node = &dummy_root;
  p_nbl = NULL;
  immediate = 0;

  for (; ;) {

    if (node != NULL) {
      if (immediate) {
        /* If leaf node, that's it! */
        if (is_leaf(node)) {
          ret_oid->id_len -= id_len;
          return node;
        }

        /* Search the immediate close node. */
        int i;
        if (p_nbl != NULL) {
          /* Fetch the pop-up backlog sub-id */
          i = p_nbl->n_idx;
          p_nbl = NULL;
        } else {
          /* Just fetch the first sub-id */
          i = 0;
        }

        if (i + 1 >= node->sub_id_cnt) {
          /* Last sub-id, mark NULL and -1. */
          nbl.node = NULL;
          nbl.n_idx = -1;
        } else {
          nbl.node = node;
          nbl.n_idx = i + 1;
        }
        /* Backlog the current node and move on */
        nbl_push(&nbl, &top, &buttom);
        *oid++ = node->sub_id[i];
        id_len--;
        node = node->sub_ptr[i];
      } else {
        /* Find the match oid */
        int index = oid_binary_search(node->sub_id, node->sub_id_cnt, *oid);
        int i = index;

        if (index < 0) {
          /* Not found, switch to immediate mode */
          immediate = 1;
          /* Reverse the sign to locate the index */
          i = -i - 1;
          if (i == node->sub_id_cnt) {
            /* All sub-ids are greater than target;
             * Backtrack and fetch the next one. */
            goto BACK_TRACK;
          } else if (i == 0) {
            /* 1. All sub-ids are less than target;
             * 2. No sub-id in this node;
             * Switch to immediate mode. */
            continue;
          } /* else {
            Target is between the two sub-ids and [i] is the next one, 
            switch to immediate mode and move on.
          } */
        }

        /* Sub-id found is greater or just equal to the target,
         * anyway, record the current node and push it into stack. */
        if (i + 1 >= node->sub_id_cnt) {
          nbl.node = NULL;
          nbl.n_idx = -1;
        } else {
          nbl.node = node;
          nbl.n_idx = i + 1;
        }
        /* Backlog the current node and move on. */
        nbl_push(&nbl, &top, &buttom);
        *oid++ = node->sub_id[i];
        node = node->sub_ptr[i];
        if (--id_len == 0) {
          /* When oid length is decreased to zero, switch to the immediate mode */
          if (is_leaf(node)) {
            goto BACK_TRACK;
          } else {
            immediate = 1;
          }
        }
      }
      /* Go on loop */
      continue;
    }

    /* Backtracking condition:
     * 1. No greater sub-id in group node;
     * 2. Seek the immediate closest instance node.
     * 3. Node not exists(node == NULL).
     */
BACK_TRACK:
    p_nbl = nbl_pop(&top, &buttom);
    if (p_nbl == NULL) {
      /* End of traversal */
      oid_cpy(ret_oid->oid, orig_oid, orig_id_len);
      ret_oid->id_len = orig_id_len;
      ret_oid->exist_status = SNMP_TAG_END_OF_MIB_VIEW;
      return &dummy_root;
    }
    oid--;
    id_len++;
    node = p_nbl->node;
    /* Switch to the immediate mode. */
    immediate = 1;
  }

  assert(0);
  return NULL;
}

/* Check if mib root node is initialized */
static inline int
mib_tree_init_check(void)
{
  return (dummy_root.sub_id != NULL && dummy_root.sub_ptr != NULL);
}

/* Resize mib node's sub-id array */
#define alloc_nr(x) (((x)+2)*3/2)
static void
mib_node_expand(struct mib_node *node, int index)
{
  int i;

  assert(!is_leaf(node));
  if (node->sub_id_cnt + 1 > node->sub_id_cap) {
    node->sub_id_cap = alloc_nr(node->sub_id_cap);

    oid_t *sub_id = calloc(node->sub_id_cap, sizeof(oid_t));
    void **sub_ptr = calloc(node->sub_id_cap, sizeof(void *));
    assert(sub_id != NULL && sub_ptr != NULL);

    /* Duplicate and insert */
    for (i = 0; i < node->sub_id_cnt; i++) {
      if (i < index) {
        sub_id[i] = node->sub_id[i];
        sub_ptr[i] = node->sub_ptr[i];
      } else {
        sub_id[i + 1] = node->sub_id[i];
        sub_ptr[i + 1] = node->sub_ptr[i];
      }
    }

    /* Abandon old ones */
    free(node->sub_id);
    free(node->sub_ptr);
    node->sub_id = sub_id;
    node->sub_ptr = sub_ptr;
  } else {
    /* Just insert. */
    for (i = node->sub_id_cnt - 1; i >= index; i--) {
      node->sub_id[i + 1] = node->sub_id[i];
      node->sub_ptr[i + 1] = node->sub_ptr[i];
    }
  }
}

/* Shrink mib node's sub-id array when removing sub-nodes */
static void
mib_node_shrink(struct mib_node *node, int index)
{
  int i;

  if (node->sub_id_cnt > 1) {
    for (i = index; i < node->sub_id_cnt - 1; i++) {
      node->sub_id[i] = node->sub_id[i + 1];
      node->sub_ptr[i] = node->sub_ptr[i + 1];
    }
    node->sub_id_cnt--;
  } else {
    node->sub_id[0] = 0;
    node->sub_ptr[0] = NULL;
    node->sub_id_cnt = 0;
  }
}

static struct mib_node *
mib_node_new(const char *name)
{
  struct mib_node *node = malloc(sizeof(*node));
  if (node != NULL) {
    node->name = name;
    node->sub_id_cap = 1;
    node->sub_id_cnt = 0;
    node->sub_id = calloc(1, sizeof(oid_t));
    if (node->sub_id == NULL) {
      return NULL;
    }
    node->sub_ptr = calloc(1, sizeof(void *));
    if (node->sub_ptr == NULL) {
      free(node->sub_id);
      return NULL;
    }
  }
  return node;
}

static void
mib_node_delete(struct mib_node *node)
{
  if (node != NULL) {
    free(node->sub_id);
    free(node->sub_ptr);
    free(node);
  }
}

/* parent-child relationship */
struct node_pair {
  struct mib_node *parent;
  struct mib_node *child;
  int sub_idx;
};

/* Find node through oid and get its parent. */
static struct mib_node *
mib_tree_node_search(const oid_t *oid, size_t id_len, struct node_pair *pair)
{
  struct mib_node *parent = pair->parent = &dummy_root;
  struct mib_node *node = pair->child = parent;
  int sub_idx = 0;

  while (node != NULL && id_len > 0) {
    int i = oid_binary_search(node->sub_id, node->sub_id_cnt, *oid);
    if (i >= 0) {
      /* Sub-id found, go on loop */
      oid++;
      id_len--;
      sub_idx = i;
      parent = node;
      node = node->sub_ptr[i];
      continue;
    } else {
      /* Sub-id not found */
      pair->parent = parent;
      pair->child = node;
      pair->sub_idx = sub_idx;
      return NULL;
    }
  }

  /* node == NULL || id_len == 0 */
  /* Note: If target oid is the dummy root node, then
   * pair->parent == pair->child and pair->sub_idx == 0 */
  pair->parent = parent;
  pair->child = node;
  pair->sub_idx = sub_idx;
  return node;
}

/* Remove specified node int mib-tree. */
static void
__mib_tree_delete(struct node_pair *pair)
{
  struct node_backlog nbl, *p_nbl;
  struct node_backlog *top, *buttom, nbl_stk[OID_MAX_LEN];
  struct mib_node *node = pair->child;

  /* Dummy root node cannot be deleted */
  if (node == &dummy_root) {
    return;
  }

  /* Init something */
  p_nbl = NULL;
  top = buttom = nbl_stk;

  for (; ;) {

    if (node != NULL) {

        int i;
        if (p_nbl != NULL) {
          /* Fetch the pop-up backlog sub-id. */
          i = p_nbl->n_idx;
          p_nbl = NULL;
        } else {
          /* Fetch the first sub-id. */
          i = 0;
        }

        if (i == -1) {
          /* All sub-trees empty, free this node and go on backtracking */
          mib_node_delete(node);
          node = NULL;
          continue;
        }

        if (i + 1 >= node->sub_id_cnt) {
          /* Last sub-id, mark n_idx = -1. */
          nbl.n_idx = -1;
        } else {
          nbl.n_idx = i + 1;
        }
        nbl.node = node;

        /* Backlog the current node and move down. */
        nbl_push(&nbl, &top, &buttom);
        node = node->sub_ptr[i++];
        continue;
    }

    /* Backtracking */
    p_nbl = nbl_pop(&top, &buttom);
    if (p_nbl == NULL) {
      /* End of traversal. */
      mib_node_shrink(pair->parent, pair->sub_idx);
      return;
    }
    node = p_nbl->node;
  }
}

static void
mib_tree_delete(const oid_t *oid, size_t id_len)
{
  struct node_pair pair;
  struct mib_node *node;

  node = mib_tree_node_search(oid, id_len, &pair);
  if (node != NULL) {
    __mib_tree_delete(&pair);
  }
}

/* This function will create and insert new node(s) in mib tree according to oid
 * and name given. The parent node(s) which corresponding to the oid prefix
 * (except for the last id number) are assumed to be existing in mib tree.
 */
static struct mib_node *
mib_tree_insert(const oid_t *oid, size_t id_len, const char *name)
{
  struct mib_node *node = &dummy_root;

  while (id_len > 0) {
    if (is_leaf(node)) {
      /* Check the oid length */
      if (id_len != 1) {
        fprintf(stderr, "%s\'s parent node(s) have not been created!\n", name);
        return NULL;
      }
      /* Insert new mib node */
      node->sub_ptr[0] = mib_node_new(name);
      node->sub_id_cnt++;
      node->sub_id[0] = *oid++;
      node = node->sub_ptr[0];
      id_len--;
    } else {
      /* Search in sub-ids */
      int i = oid_binary_search(node->sub_id, node->sub_id_cnt, *oid);
      if (i >= 0) {
        /* Sub-id found, go on traversing */
        if (--id_len == 0) {
          fprintf(stderr, "Cannot insert at an existing node.\n");
          return NULL;
        }
        oid++;
        node = node->sub_ptr[i];
      } else {
        /* Sub-id not found, that's it. */
        i = -i - 1;
        /* Check the oid length */
        if (id_len != 1) {
          fprintf(stderr, "%s\'s parent node(s) have not been created!\n", name);
          return NULL;
        }
        /* Resize sub_id[] */
        mib_node_expand(node, i);
        /* Insert new mib node */
        node->sub_ptr[i] = mib_node_new(name);
        node->sub_id_cnt++;
        node->sub_id[i] = *oid++;
        node = node->sub_ptr[i];
        id_len--;
      }
    }
  }

  /* id_len == 0 */
  return node;
}

static void
mib_tree_init(void)
{
  struct mib_node *node = &dummy_root;
  node->sub_id_cap = 1;
  node->sub_id_cnt = 0;
  node->sub_id = malloc(sizeof(oid_t));
  if (node->sub_id == NULL) {
    return;
  }
  node->sub_id[0] = 0;
  node->sub_ptr = malloc(sizeof(void *));
  if (node->sub_ptr == NULL) {
    free(node->sub_id);
    return;
  }
  node->sub_ptr[0] = NULL;
}

void
mib_tree_draw(void)
{
  int level;
  oid_t id;
  struct mib_node *node = &dummy_root; 
  struct node_backlog nbl, *p_nbl;
  struct node_backlog *top, *buttom, nbl_stack[OID_MAX_LEN];

  top = buttom = nbl_stack;
  p_nbl = NULL;
  level = 0;
  id = 0;

  for (; ;) {
    if (node != NULL) {
      int i;

      if (p_nbl != NULL) {
        i = p_nbl->n_idx;
        p_nbl = NULL;
      } else {
        i = 0;
      }

      if (i + 1 >= node->sub_id_cnt) {
        nbl.node = NULL;
        nbl.n_idx = -1;
      } else {
        nbl.node = node;
        nbl.n_idx = i + 1;
      }
      nbl_push(&nbl, &top, &buttom);

      /* Draw lines */
      if (i == 0 && level > 0) {
        int j;
        for (j = 1; j < level; j++) {
          if (j == level - 1) {
              printf("%-8.8s", "+-------");
          } else {
            if (nbl_stack[j].n_idx != -1) {
              printf("%s", "|");
              printf("%-7.8s", " ");
            } else {
              printf("%-8.8s", " ");
            }
          }
        }
        printf("%s(%d)\n", node->name, id);
        for (j = 1; j < level; j++) {
          if (nbl_stack[j].n_idx != -1) {
            printf("%s", "|");
            printf("%-7.8s", " ");
          } else {
            printf("%-8s", " ");
          }
        }
        if (!is_leaf(node)) {
          printf("%-8s", "|");
        }
        printf("\n");
      }

      /* Move on */
      id = node->sub_id[i];
      node = node->sub_ptr[i];
      level++;
      continue;
    }

    p_nbl = nbl_pop(&top, &buttom);
    if (p_nbl == NULL) {
      /* End of traversal */
      return;
    }
    node = p_nbl->node;
    level--;
  }
}

int
main(void)
{
  int i;
  struct oid_search_result ret_oid;
  struct mib_node *node;

  oid_t dummy[] = {};
  oid_t iso[] = { 1 };
  oid_t org[] = { 1, 3 };
  oid_t dod[] = { 1, 3, 6 };
  oid_t internet[] = { 1, 3, 6, 1 };
  oid_t mgmt[] = { 1, 3, 6, 1, 2 };
  oid_t mib_2[] = {1, 3, 6, 1, 2, 1};
  oid_t system[] = { 1, 3, 6, 1, 2, 1, 1 };
  oid_t interfaces[] = { 1, 3, 6, 1, 2, 1, 2 };
  oid_t at[] = { 1, 3, 6, 1, 2, 1, 3 };
  oid_t ip[] = { 1, 3, 6, 1, 2, 1, 4 };
  oid_t icmp[] = { 1, 3, 6, 1, 2, 1, 5 };
  oid_t tcp[] = { 1, 3, 6, 1, 2, 1, 6 };
  oid_t udp[] = { 1, 3, 6, 1, 2, 1, 7 };
  oid_t private[] = { 1, 3, 6, 1, 4 };
  oid_t enterprises[] = { 1, 3, 6, 1, 4, 1 };
  oid_t traps[] = { 1, 3, 6, 1, 6 };

  mib_tree_init();

  mib_tree_insert(dummy, ARRAY_SIZE(dummy), "dummy");
  mib_tree_insert(iso, ARRAY_SIZE(iso), "iso");
  mib_tree_insert(org, ARRAY_SIZE(org), "org");
  mib_tree_insert(dod, ARRAY_SIZE(dod), "dod");
  mib_tree_insert(internet, ARRAY_SIZE(internet), "internet");
  mib_tree_insert(mgmt, ARRAY_SIZE(mgmt), "mgmt");
  mib_tree_insert(mib_2, ARRAY_SIZE(mib_2), "mib_2");
  mib_tree_insert(system, ARRAY_SIZE(system), "system");
  mib_tree_insert(interfaces, ARRAY_SIZE(interfaces), "interfaces");
  mib_tree_insert(at, ARRAY_SIZE(at), "at");
  mib_tree_insert(ip, ARRAY_SIZE(ip), "ip");
  mib_tree_insert(icmp, ARRAY_SIZE(icmp), "icmp");
  mib_tree_insert(tcp, ARRAY_SIZE(tcp), "tcp");
  mib_tree_insert(udp, ARRAY_SIZE(udp), "udp");
  mib_tree_insert(private, ARRAY_SIZE(private), "private");
  mib_tree_insert(enterprises, ARRAY_SIZE(enterprises), "enterprises");
  mib_tree_insert(traps, ARRAY_SIZE(traps), "traps");

  /* Draw whole mib tree */
  mib_tree_draw();

  /* Get request */
  node = mib_tree_get(udp, ARRAY_SIZE(udp), &ret_oid);
  if (node != NULL && ret_oid.exist_status == SNMP_TAG_NO_ERR) {
    printf("Get node %s (", node->name);
    for (i = 0; i < ret_oid.id_len; i++) {
      printf(".%d", ret_oid.oid[i]);
    }
    printf(")");
  } else {
    printf("Not found");
  }
  printf("\n");

  /* Getnext request */
  node = mib_tree_get_next(udp, ARRAY_SIZE(udp), &ret_oid);
  printf("Getnext node ");
  if (ret_oid.exist_status == SNMP_TAG_NO_ERR) {
    printf("%s (", node->name);
    for (i = 0; i < ret_oid.id_len; i++) {
      printf(".%d", ret_oid.oid[i]);
    }
    printf(")");
  } else if (ret_oid.exist_status == SNMP_TAG_END_OF_MIB_VIEW) {
    printf("-- End of MIB view");
  }
  printf("\n");
  free(ret_oid.oid);

  /* Deletion */
  mib_tree_delete(dod, ARRAY_SIZE(dod));
  printf("After delete node oid ");
  for (i = 0; i < ARRAY_SIZE(dod); i++) {
    printf(".%d", dod[i]);
  }
  printf("\n");

  /* Draw whole mib tree */
  mib_tree_draw();

  return 0;
}
