#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// TODO: 値を返すところで NULL のかわりをしたい
typedef long long int_val;

struct fun_val;

typedef enum { val_int_tag, val_func_tag } value_tag;

typedef struct {
  value_tag tag;
  union {
    void *other;
    int_val i;
    struct fun_val *func;
  } data;
} value;

typedef enum {
    ex_none_tag, ex_add_tag, ex_sub_tag, ex_mul_tag, ex_div_tag, ex_mod_tag,
    ex_lt_tag, ex_le_tag, ex_gt_tag, ex_ge_tag, ex_ne_tag, ex_eq_tag,
    ex_app_tag, ex_val_tag, ex_var_tag, ex_asgn_tag, ex_oper_asgn_tag
  } expr_tag;

typedef struct expr {
  expr_tag tag;
  union {
    void *ex_none;
    struct {
      struct expr *l;
      struct expr *r;
    } ex_bin;
    value *ex_val;
    const char *ex_var;
    struct {
      const char *lhs;
      struct expr *rhs;
    } ex_asgn;
    struct {
      const char *lhs;
      struct expr *rhs;
      expr_tag oper;
    } ex_oper_asgn;
  } data;
} expr;

typedef enum {
    st_none_tag, st_ex_tag,
    st_if_tag, st_while_tag, st_for_tag
  } statement_tag;

typedef struct statement {
  statement_tag tag;
  union {
    void *st_none;
    expr st_ex;
    struct {
      expr cond;
      struct statement *if_true;
      struct statement *if_false;
    } st_if;
    struct {
      expr cond;
      struct statement *st;
    } st_while;
    struct {
      expr init, cond, incr;
      struct statement *st;
    } st_for;
  } data;
  struct statement *next;
} statement;

typedef struct env {
  const char *name;
  value *val;
  struct env *l;
  struct env *r;
} env;

// TODO: 可変長引数取りたい voidもあり
typedef struct fun_val {
  bool is_prim;
  union {
    value *(*prim)(value *);
    struct {
      env *en;
      const char *name;
      statement st;
    } closure;
  } data;
} fun_val;

typedef enum {
    gc_value_tag, gc_expr_tag, gc_statement_tag,
    gc_env_tag, gc_fun_val_tag, gc_char_tag,
    gc_void_tag
  } gc_type_tag;

typedef struct {
  union {
    value *val;
    expr *ex;
    statement *st;
    env *en;
    fun_val *func;
    char *ch;
    void *p;
  } ptr;
  bool mark;
  gc_type_tag type;
} gc_data;

// TODO: 単純な二分探索木だから遅い
typedef struct gc_ptrs {
  // number of nodes
  int size;
  struct {
    void *ptr;
    gc_data data;
    struct gc_ptrs *l;
    struct gc_ptrs *r;
  } node;
} gc_ptrs;

gc_ptrs *gc_mk_leaf(void) {
  gc_ptrs *p = malloc(sizeof(gc_ptrs));
  p->size = 0;
  return p;
}

void gc_ptrs_free(gc_ptrs *ptrs, bool free_ptr) {
  if (!ptrs) {
    return;
  }
  if (ptrs->size) {
    if (free_ptr) {
      free(ptrs->node.ptr);
    }
    gc_ptrs_free(ptrs->node.l, free_ptr);
    gc_ptrs_free(ptrs->node.r, free_ptr);
  }
  free(ptrs);
}

gc_data *gc_lookup(gc_ptrs *ptrs, const void *ptr) {
  // NULLはキーにできない
  if (!ptr || !ptrs) {
    return NULL;
  }
  for (gc_ptrs *i = ptrs; ;) {
    if (!i->size) {
      return NULL;
    } else if (ptr == i->node.ptr) {
      return &i->node.data;
    } else if (ptr < i->node.ptr) {
      i = i->node.l;
    } else {
      i = i->node.r;
    }
  }
}

void gc_insert(gc_ptrs *ptrs, void *ptr, gc_data data) {
  if (!ptr || !ptrs) {
    return;
  }
  bool b = !gc_lookup(ptrs, ptr);
  for (gc_ptrs *i = ptrs; ;) {
    if (!i->size) {
      ++i->size;
      i->node.ptr = ptr;
      i->node.data = data;
      i->node.l = gc_mk_leaf();
      i->node.r = gc_mk_leaf();
      break;
    } else if (ptr == i->node.ptr) {
      i->node.data = data;
      break;
    } else if (ptr < ptrs->node.ptr) {
      if (b) {
        ++i->size;
      }
      i = i->node.l;
    } else {
      if (b) {
        ++i->size;
      }
      i = i->node.r;
    }
  }
}

void gc_delete_min(gc_ptrs **ptrs, void **ptr, gc_data *data) {
  if (!ptrs || !*ptrs || !(*ptrs)->size /* || !gc_lookup(*ptrs, ptr) */) {
    return;
  }
  gc_ptrs **i;
  for (i = ptrs; !(*i)->node.l->size; --(*i)->size, i = &(*i)->node.l) {
  }
  gc_ptrs *tmp = *i;
  *ptr = tmp->node.ptr;
  *data = tmp->node.data;
  *i = tmp->node.r;
  free(tmp->node.l);
  free(tmp);
}

// 多分変な名前
void gc_delete_self(gc_ptrs **ptrs) {
  if (!ptrs || !*ptrs || !(*ptrs)->size) {
    return;
  }
  gc_ptrs *tmp = *ptrs, *tmp_l = tmp->node.l, *tmp_r = tmp->node.r;
  if (!tmp_l->size) {
    *ptrs = tmp_r;
    free(tmp_l);
    free(tmp);
  } else if (!tmp_r->size) {
    *ptrs = tmp_l;
    free(tmp_r);
    free(tmp);
  } else {
    gc_delete_min(ptrs, &tmp->node.ptr, &tmp->node.data);
  }
}

void gc_delete(gc_ptrs **ptrs, void *ptr) {
  if (!ptr || !ptrs || !*ptrs || !gc_lookup(*ptrs, ptr)) {
    return;
  }
  for (gc_ptrs **i = ptrs; ;) {
    if (!(*i)->size) {
      return;
    } else if (ptr == (*i)->node.ptr) {
      gc_delete_self(i);
      return;
    } else if (ptr < (*i)->node.ptr) {
      --(*i)->size;
      i = &(*i)->node.l;
    } else {
      --(*i)->size;
      i = &(*i)->node.r;
    }
  }
}

struct {
  gc_ptrs *ptrs, *roots;
} gabe_colle = { NULL, NULL };

void gc_init(void) {
  if (gabe_colle.roots) {
    gc_ptrs_free(gabe_colle.roots, false);
  }
  gabe_colle.roots = gc_mk_leaf();
  if (gabe_colle.ptrs) {
    gc_ptrs_free(gabe_colle.ptrs, true);
  }
  gabe_colle.ptrs = gc_mk_leaf();
}

void *gc_malloc(size_t s, gc_type_tag tag) {
  void *p = malloc(s);
  gc_insert(gabe_colle.ptrs, p, (gc_data){ { .p = p }, false, tag });
  return p;
}

void gc_add_root(void *p, gc_type_tag tag) {
  // rootではmarkは関係ない どっちでもいい
  gc_insert(gabe_colle.roots, p, (gc_data){ { .p = p }, false, tag });
}

gc_data *gc_search(const void *p) {
  return gc_lookup(gabe_colle.ptrs, p);
}

void gc_traverse(gc_data *data);

void gc_traverse_expr(expr *ex) {
  if (!ex) {
    return;
  }
  switch (ex->tag) {
    case ex_none_tag :
      break;
    case ex_val_tag :
      gc_traverse(gc_search(ex->data.ex_val));
      break;
    case ex_add_tag :
    case ex_sub_tag :
    case ex_mul_tag :
    case ex_div_tag :
    case ex_mod_tag :
    case ex_lt_tag :
    case ex_le_tag :
    case ex_gt_tag :
    case ex_ge_tag :
    case ex_ne_tag :
    case ex_eq_tag :
    case ex_app_tag :
      gc_traverse(gc_search(ex->data.ex_bin.l));
      gc_traverse(gc_search(ex->data.ex_bin.r));
      break;
    case ex_var_tag :
      gc_traverse(gc_search(ex->data.ex_var));
      break;
    case ex_asgn_tag :
      gc_traverse(gc_search(ex->data.ex_asgn.lhs));
      gc_traverse(gc_search(ex->data.ex_asgn.rhs));
      break;
    case ex_oper_asgn_tag :
      gc_traverse(gc_search(ex->data.ex_oper_asgn.lhs));
      gc_traverse(gc_search(ex->data.ex_oper_asgn.rhs));
      break;
  }
}

void gc_traverse_statement(statement *st) {
  switch (st->tag) {
    case st_ex_tag :
      gc_traverse_expr(&st->data.st_ex);
      break;
    case st_if_tag :
      gc_traverse_expr(&st->data.st_if.cond);
      gc_traverse(gc_search(st->data.st_if.if_true));
      gc_traverse(gc_search(st->data.st_if.if_false));
      break;
    case st_while_tag :
      gc_traverse_expr(&st->data.st_while.cond);
      gc_traverse(gc_search(st->data.st_while.st));
      break;
    case st_for_tag :
      gc_traverse_expr(&st->data.st_for.init);
      gc_traverse_expr(&st->data.st_for.cond);
      gc_traverse_expr(&st->data.st_for.incr);
      gc_traverse(gc_search(st->data.st_for.st));
      break;
    default :
      break;
  }
  gc_traverse(gc_search(st->next));
}

void gc_traverse(gc_data *data) {
  if (!data) {
    return;
  }
  data->mark = true;
  switch (data->type) {
    case gc_value_tag :
      switch (data->ptr.val->tag) {
        case val_int_tag :
          break;
        case val_func_tag :
          gc_traverse(gc_search(data->ptr.val->data.func));
          break;
      }
      break;
    case gc_expr_tag :
      gc_traverse_expr(data->ptr.ex);
      break;
    case gc_statement_tag :
      gc_traverse_statement(data->ptr.st);
      break;
    case gc_env_tag :
      gc_traverse(gc_search(data->ptr.en->name));
      gc_traverse(gc_search(data->ptr.en->val));
      gc_traverse(gc_search(data->ptr.en->l));
      gc_traverse(gc_search(data->ptr.en->r));
      break;
    case gc_fun_val_tag :
      if (!data->ptr.func->is_prim) {
        gc_traverse(gc_search(data->ptr.func->data.closure.en));
        gc_traverse(gc_search(data->ptr.func->data.closure.name));
        gc_traverse_statement(&data->ptr.func->data.closure.st);
      }
      break;
    case gc_char_tag :
    case gc_void_tag :
      break;
  }
}

void gc_mark_init(gc_ptrs *ptrs) {
  if (!ptrs || !ptrs->size) {
    return;
  }
  gc_mark_init(ptrs->node.l);
  gc_mark_init(ptrs->node.r);
  ptrs->node.data.mark = false;
}

void gc_traverse_roots(gc_ptrs *roots) {
  if (!roots || !roots->size) {
    return;
  }
  gc_data *data = gc_search(roots->node.ptr);
  if (data) {
    data->mark = true;
  }
  gc_traverse(&roots->node.data);
  gc_traverse_roots(roots->node.l);
  gc_traverse_roots(roots->node.r);
}

void gc_sweep_rec(gc_ptrs **top, gc_ptrs **ptrs) {
  if (!ptrs || !*ptrs || !(*ptrs)->size) {
    return;
  }
  gc_sweep_rec(top,&(*ptrs)->node.l);
  gc_sweep_rec(top,&(*ptrs)->node.r);
  if (!(*ptrs)->node.data.mark) {
    free((*ptrs)->node.ptr);
    gc_delete(top,(*ptrs)->node.ptr);
  }
}

void gc_sweep(gc_ptrs **ptrs) {
  if (!ptrs || !*ptrs) {
    return;
  }
  gc_sweep_rec(ptrs,ptrs);
}

// TODO: debug mode
void gc_collect(void) {
  int size = gabe_colle.ptrs->size;
  gc_mark_init(gabe_colle.ptrs);
  gc_traverse_roots(gabe_colle.roots);
  gc_sweep(&gabe_colle.ptrs);
  int new_size = gabe_colle.ptrs->size;
  printf("がべこれ: %d => %d (-%d)\n", size, new_size, size - new_size);
}

#define gc_data_show_prefix(s,pre) { char ty[] = "(" #pre ")"; int l = sizeof(ty)-1; memcpy(s,ty,l); s += l; }

// TODO: char **s か 戻り値char *s
void gc_data_show_value(value *val, char *s);
void gc_data_show_statement(statement *st, char *s);

void gc_data_show_fun_val(fun_val *func, char *s) {
  if (!func) {
    gc_data_show_prefix(s,fun_val);
    strcpy(s,"NULL");
  }
  if (func->is_prim) {
    gc_data_show_prefix(s,prim_fun);
    sprintf(s, "%p", func->data.prim);
  } else {
    sprintf(s, "fun (%s) { ", func->data.closure.name);
    s += strlen(s);
    gc_data_show_statement(&func->data.closure.st, s);
    strcat(s," }");
  }
}

void gc_data_show_value(value *val, char *s) {
  gc_data_show_prefix(s,val);
  switch (val->tag) {
    case val_int_tag :
      sprintf(s, "%lld", val->data.i);
      break;
    case val_func_tag :
      gc_data_show_fun_val(val->data.func, s);
      break;
  }
}

void gc_data_show_expr(expr *ex, char *s) {
  gc_data_show_prefix(s,expr);
}

void gc_data_show_statement(statement *st, char *s) {
  gc_data_show_prefix(s,st);
}

char *gc_data_show_env_rec(env *en, char *s, bool comma) {
  if (!en) {
    strcpy(s,"NULL");
    return s + 4;
  }
  if (comma) {
    strcpy(s,", ");
    s += 2;
  }
  sprintf(s, "%s: ", en->name);
  s += strlen(s);
  gc_data_show_value(en->val, s);
  s += strlen(s);
  if (en->l) {
    gc_data_show_env_rec(en->l, s, true);
    s += strlen(s);
  }
  if (en->r) {
    gc_data_show_env_rec(en->r, s, true);
    s += strlen(s);
  }
  return s;
}

void gc_data_show_env(env *en, char *s) {
  gc_data_show_prefix(s,env);
  strcpy(s,"{ "); s += 2;
  s = gc_data_show_env_rec(en,s,false);
  strcpy(s," }");
}

// TODO: s の範囲に収まるか?
void gc_data_show(gc_data *data, char *s) {
  if (!data) {
    return;
  }
  switch (data->type) {
    case gc_value_tag : {
      gc_data_show_value(data->ptr.val, s);
      break;
    }
    case gc_expr_tag :
      gc_data_show_expr(data->ptr.ex, s);
      break;
    case gc_statement_tag :
      gc_data_show_statement(data->ptr.st, s);
      break;
    case gc_env_tag :
      gc_data_show_env(data->ptr.en, s);
      break;
    case gc_fun_val_tag :
      gc_data_show_fun_val(data->ptr.func, s);
      break;
    case gc_char_tag :
      sprintf(s, "\"%s\"", data->ptr.ch);
      break;
    case gc_void_tag :
      sprintf(s, "(void*)%p", data->ptr.p);
      break;
  }
}

value *lookup(const env *en, const char *name) {
  if (!en || !en->name) {
    return NULL;
  }
  int c = strcmp(en->name,name);
  if (c == 0) {
    return en->val;
  } else if (c > 0) {
    return lookup(en->l,name);
  } else {
    return lookup(en->r,name);
  }
}

void insert(env **enp, const char *name, value *val) {
  if (!enp) {
    return;
  }
  env *en = *enp;
  if (!en) {
    *enp = gc_malloc(sizeof(env), gc_env_tag);
    **enp = (env){ name, val, NULL, NULL };
    return;
  }
  int c = strcmp(en->name,name);
  if (c == 0) {
    en->val = val;
  } else if (c > 0) {
    insert(&en->l,name,val);
  } else {
    insert(&en->r,name,val);
  }
}

env *copy_env(const env *en) {
  if (!en) {
    return NULL;
  }
  env *copy_l = copy_env(en->l);
  env *copy_r = copy_env(en->r);
  env *new_env = gc_malloc(sizeof(env), gc_env_tag);
  *new_env = (env){ en->name, en->val, copy_l, copy_r };
  return new_env;
}

value *value_one(void) {
  static value v = { val_int_tag, { .i = 1 } };
  return &v;
}

expr *expr_one(void) {
  static value v = { val_int_tag, { .i = 1 } };
  static expr ex = { ex_val_tag, { .ex_val = &v } };
  return &ex;
}

expr *expr_m_one(void) {
  static value v = { val_int_tag, { .i = -1 } };
  static expr ex = { ex_val_tag, { .ex_val = &v } };
  return &ex;
}

value *prim_print(value *val) {
  if (!val) {
    printf("<<NULL>>\n");
    return NULL;
  }
  switch (val->tag) {
    case val_int_tag :
      printf("%lld\n", val->data.i);
      return val;
    case val_func_tag :
      if (val->data.func->is_prim) {
        printf("<<prim_fun>>\n");
      } else {
        printf("<<fun>>\n");
      }
      return val;
  }
}

value *prim_time(value *vvvvvvvvvvvvvvvv) {
  value *v = gc_malloc(sizeof(value), gc_value_tag);
  *v = (value){ val_int_tag, { .i = time(NULL) } };
  return v;
}

value *prim_gc_collect(value *val) {
  gc_collect();
  return val;
}

value *make_prim_fun(value *(*prim)(value *)) {
  fun_val *f = gc_malloc(sizeof(fun_val), gc_fun_val_tag);
  *f = (fun_val){ true, { .prim = prim } };
  value *val = gc_malloc(sizeof(value), gc_value_tag);
  *val = (value){ val_func_tag, { .func = f } };
  return val;
}

env *init_env(void) {
  env *en = NULL;
  insert(&en,"print",make_prim_fun(prim_print));
  insert(&en,"time",make_prim_fun(prim_time));
  insert(&en,"gc_collect",make_prim_fun(prim_gc_collect));
  gc_add_root(en, gc_env_tag);
  return en;
}

bool is_true(value *val) {
  if (!val) {
    return false;
  }
  switch (val->tag) {
    case val_int_tag :
      return val->data.i;
    default :
      return true;
  }
}

int_val value2int(value *val) {
  if (val->tag == val_int_tag) {
    return val->data.i;
  } else {
    return 0;
  }
}

value *eval(env **en, const expr *ex);

value *eval_bin_int(env **en, expr_tag tag, const expr *ex_l, const expr *ex_r) {
  value *l = eval(en,ex_l);
  value *r = eval(en,ex_r);
  value *v = gc_malloc(sizeof(value), gc_value_tag);
  *v = (value){ val_int_tag, { .i = 0 } };
  int li = value2int(l);
  int ri = value2int(r);
  switch (tag) {
    case ex_add_tag :
      v->data.i = li + ri;
      break;
    case ex_sub_tag :
      v->data.i = li - ri;
      break;
    case ex_mul_tag :
      v->data.i = li * ri;
      break;
    case ex_div_tag :
      v->data.i = li / ri;
      break;
    case ex_mod_tag :
      v->data.i = li % ri;
      break;
    case ex_lt_tag :
      v->data.i = li < ri;
      break;
    case ex_le_tag :
      v->data.i = li <= ri;
      break;
    case ex_gt_tag :
      v->data.i = li > ri;
      break;
    case ex_ge_tag :
      v->data.i = li >= ri;
      break;
    case ex_ne_tag :
      v->data.i = li != ri;
      break;
    case ex_eq_tag :
      v->data.i = li == ri;
      break;
    default :
      break;
  }
  return v;
}

value *run(env **en, statement *st);

value *apply(env **en, const expr *ex_f, const expr *ex_x) {
  value *f = eval(en,ex_f);
  value *x = eval(en,ex_x);
  if (!f || !x || f->tag != val_func_tag) {
    return NULL;
  }
  fun_val *fv = f->data.func;
  if (fv->is_prim) {
    return fv->data.prim(x);
  } else {
    env *new_env = copy_env(fv->data.closure.en);
    insert(&new_env,fv->data.closure.name,x);
    return run(&new_env,&fv->data.closure.st);
  }
}

value *eval(env **en, const expr *ex) {
  if (!ex) {
    return NULL;
  }
  switch (ex->tag) {
    case ex_none_tag :
      return value_one();
    case ex_val_tag : {
      value *v = ex->data.ex_val;
      if (v && v->tag == val_func_tag && !v->data.func->is_prim
        && !v->data.func->data.closure.en) {
        env *new_env = copy_env(*en);
        v->data.func->data.closure.en = new_env;
      }
      return v;
    }
    case ex_add_tag :
    case ex_sub_tag :
    case ex_mul_tag :
    case ex_div_tag :
    case ex_mod_tag :
    case ex_lt_tag :
    case ex_le_tag :
    case ex_gt_tag :
    case ex_ge_tag :
    case ex_ne_tag :
    case ex_eq_tag : {
      return eval_bin_int(en,ex->tag,ex->data.ex_bin.l,ex->data.ex_bin.r);
    }
    case ex_app_tag : {
      return apply(en,ex->data.ex_bin.l,ex->data.ex_bin.r);
    }
    case ex_var_tag : {
      return lookup(*en,ex->data.ex_var);
    }
    case ex_asgn_tag : {
      value *v = eval(en,ex->data.ex_asgn.rhs);
      insert(en,ex->data.ex_asgn.lhs,v);
      return v;
    }
    case ex_oper_asgn_tag : {
      expr var = { ex_var_tag, { .ex_var = ex->data.ex_oper_asgn.lhs } };
      expr e = { ex->data.ex_oper_asgn.oper, { .ex_bin = { &var, ex->data.ex_oper_asgn.rhs } } };
      value *v = eval(en,&e);
      insert(en,ex->data.ex_asgn.lhs,v);
      return v;
    }
  }
}

value *run(env **en, statement *st) {
  value *res = NULL;
  for (statement *i = st; i; i = i->next) {
    switch (i->tag) {
      case st_none_tag :
        break;
      case st_ex_tag :
        res = eval(en,&i->data.st_ex);
        break;
      case st_if_tag : {
        value *v = eval(en,&i->data.st_if.cond);
        if (is_true(v)) {
          res = run(en,i->data.st_if.if_true);
        } else {
          res = run(en,i->data.st_if.if_false);
        }
        break;
      }
      case st_while_tag : {
        while (is_true(res = eval(en,&i->data.st_while.cond))) {
          res = run(en,i->data.st_while.st);
        }
        break;
      }
      case st_for_tag : {
        for (res = eval(en,&i->data.st_for.init);
          is_true(res = eval(en,&i->data.st_for.cond));
          res = eval(en,&i->data.st_for.incr)) {
          res = run(en,i->data.st_for.st);
        }
        break;
      }
    }
  }
  return res;
}

void skip_spaces(const char **strp) {
  while (isspace((*strp)[0])) {
    ++*strp;
  }
}

bool parse_char(const char **strp, char c) {
  bool b = (*strp)[0] == c;
  if (b) {
    ++*strp;
    skip_spaces(strp);
  }
  return b;
}

int parse_oneof(const char **strp, const char **cs, int l) {
  for (int i = 0; i < l; ++i) {
    if (strstr(*strp,cs[i]) == *strp) {
      *strp += strlen(cs[i]);
      skip_spaces(strp);
      return i;
    }
  }
  return -1;
}

bool parse_word(const char **strp, const char *s) {
  size_t l = strlen(s);
  bool b = !strncmp(*strp,s,l) && !isalnum((*strp)[l]);
  if (b) {
    *strp += l;
    skip_spaces(strp);
  }
  return b;
}

bool parse_sym(const char **strp, const char *s) {
  size_t l = strlen(s);
  bool b = !strncmp(*strp,s,l);
  if (b) {
    *strp += l;
    skip_spaces(strp);
  }
  return b;
}

const char *parse_var(const char **strp) {
  if (!strp || !*strp) {
    return NULL;
  }
  const char *str = *strp;
  if (!isalpha(str[0]) && str[0] != '_') {
    return NULL;
  }
  int i;
  for (i = 0; isalnum(str[i]) || str[i] == '_'; ++i, ++*strp)
    ;
  char *res = gc_malloc(i+1, gc_char_tag);
  memcpy(res,str,i);
  res[i] = '\0';
  skip_spaces(strp);
  return res;
}

statement parse_statement(const char **, bool);

value parse_value(const char **strp) {
  const char *str = *strp;
  if (isdigit(str[0])) {
    int_val dt = 0;
    for (int i = 0; isdigit(str[i]); ++i, ++*strp) {
      dt = 10*dt + (str[i]-'0');
    }
    skip_spaces(strp);
    return (value){ val_int_tag, { .i = dt } };
  }
  if (parse_word(strp,"fun")) {
    if (parse_char(strp,'(')) {
      const char *name = parse_var(strp);
      if (parse_char(strp,')') && parse_char(strp,'{')) {
        const char *str0 = *strp;
        statement st = parse_statement(strp,true);
        fun_val *f = gc_malloc(sizeof(fun_val), gc_fun_val_tag);
        *f = (fun_val){ false, { .closure = { NULL, name, st } } };
        if (str0 != *strp && parse_char(strp,'}')) {
          return (value){ val_func_tag, { .func = f } };
        }
      }
    }
  }
  *strp = str;
  return (value){ 0, { NULL } };
}

expr parse_expr(const char **strp);

expr parse_expr_0(const char **strp) {
  const char *str = *strp;
  if (parse_char(strp,'(')) {
    ++str;
    expr ex = parse_expr(strp);
    if (str != *strp) {
      if (parse_char(strp,')')) {
        return ex;
      }
    } else {
      // 失敗v('ω')v 
      return (expr){ 0, { NULL } };
    }
  }
  value v = parse_value(strp);
  if (str != *strp) {
    value *res = gc_malloc(sizeof(value), gc_value_tag);
    *res = v;
    return (expr){ ex_val_tag, { .ex_val = res } };
  }
  const char *name = parse_var(strp);
  if (str != *strp) {
    return (expr){ ex_var_tag, { .ex_var = name } };
  }
  return (expr){ 0, { NULL } };
}

expr parse_expr_1(const char **strp) {
  const char *str = *strp;
  const char *name = parse_var(strp);
  if (str != *strp) {
    if (parse_sym(strp,"++")) {
      return (expr){ ex_oper_asgn_tag,
        { .ex_oper_asgn = { name, expr_one(), ex_add_tag } } };
    } else if (parse_sym(strp,"--")) {
      return (expr){ ex_oper_asgn_tag,
        { .ex_oper_asgn = { name, expr_one(), ex_sub_tag } } };
    }
  }
  *strp = str;
  if (parse_char(strp,'+')) {
    expr *p = gc_malloc(sizeof(expr), gc_expr_tag);
    *p = parse_expr_0(strp);
    return (expr){ ex_mul_tag,
      { .ex_bin = { expr_one(), p } } };
  } else if (parse_char(strp,'-')) {
    expr *p = gc_malloc(sizeof(expr), gc_expr_tag);
    *p = parse_expr_0(strp);
    return (expr){ ex_mul_tag,
      { .ex_bin = { expr_m_one(), p } } };
  }
  return parse_expr_0(strp);
}

expr parse_expr_2(const char **strp) {
  const char *str = *strp;
  if (parse_sym(strp,"++")) {
    const char *str0 = *strp;
    const char *name = parse_var(strp);
    if (str0 != *strp) {
      return (expr){ ex_oper_asgn_tag,
        { .ex_oper_asgn = { name, expr_one(), ex_add_tag } } };
    }
  } else if (parse_sym(strp,"--")) {
    const char *str0 = *strp;
    const char *name = parse_var(strp);
    if (str0 != *strp) {
      return (expr){ ex_oper_asgn_tag,
        { .ex_oper_asgn = { name, expr_one(), ex_sub_tag } } };
    }
  }
  *strp = str;
  return parse_expr_1(strp);
}

expr parse_expr_3(const char **strp) {
  const char *str = *strp;
  expr ex_f = parse_expr_2(strp);
  if (str != *strp) {
    str = *strp;
    if (parse_char(strp,'(')) {
      const char *str1 = *strp;
      expr ex_x = parse_expr(strp);
      if (str1 != *strp && parse_char(strp,')')) {
        expr *f = gc_malloc(sizeof(expr), gc_expr_tag);
        *f = ex_f;
        expr *x = gc_malloc(sizeof(expr), gc_expr_tag);
        *x = ex_x;
        return (expr){ ex_app_tag, { .ex_bin = { f, x } } };
      } else {
        *strp = str;
      }
    }
    return ex_f;
  }
  *strp = str;
  return (expr){ 0, { NULL } };
}

expr parse_expr_bin_op(const char **strp,
  const char **cs, expr_tag tags[], int l, expr (*next)(const char **)) {
  const char *str = *strp;
  expr ex = next(strp);
  if (str != *strp) {
    int op;
    while ((op = parse_oneof(strp,cs,l)) != -1) {
      str = *strp;
      expr tmp = next(strp);
      if (str != *strp) {
        expr *l, *r;
        l = gc_malloc(sizeof(expr), gc_expr_tag);
        *l = ex;
        r = gc_malloc(sizeof(expr), gc_expr_tag);
        *r = tmp;
        ex = (expr){ tags[op], { .ex_bin = { l, r } } };
      }
    }
  }
  return ex;
}

expr parse_expr_4(const char **strp) {
  expr_tag tags[] = { ex_mul_tag, ex_div_tag, ex_mod_tag };
  const char *ops[] = { "*", "/", "%" };
  int l = sizeof(ops) / sizeof(const char *);
  return parse_expr_bin_op(strp, ops, tags, l, parse_expr_3);
}

expr parse_expr_5(const char **strp) {
  expr_tag tags[] = { ex_add_tag, ex_sub_tag };
  const char *ops[] = { "+", "-" };
  int l = sizeof(ops) / sizeof(const char *);
  return parse_expr_bin_op(strp, ops, tags, l, parse_expr_4);
}

expr parse_expr_6(const char **strp) {
  expr_tag tags[] = { ex_lt_tag, ex_le_tag, ex_gt_tag, ex_ge_tag, ex_ne_tag, ex_eq_tag };
  const char *ops[] = { "<", "<=", ">", ">=", "!=", "==" };
  int l = sizeof(ops) / sizeof(const char *);
  return parse_expr_bin_op(strp, ops, tags, l, parse_expr_5);
}

bool parse_expr_asgn_op(const char **strp, const char *name, const char *c, expr_tag tag, expr *p) {
  if (parse_word(strp,c)) {
    expr *ex = gc_malloc(sizeof(expr), gc_expr_tag);
    *ex = parse_expr(strp);
    *p = (expr){ ex_oper_asgn_tag, { .ex_oper_asgn = { name, ex, tag } } };
    return true;
  } else {
    return false;
  }
}

bool parse_expr_asgn_ops(const char **strp,
  const char *name, const char **cs, expr_tag tags[], int l, expr *p) {
  for (int i = 0; i < l; ++i) {
    if (parse_expr_asgn_op(strp,name,cs[i],tags[i],p)) {
      return true;
    }
  }
  return false;
}

expr parse_expr(const char **strp) {
  const char *str = *strp;
  const char *name = parse_var(strp);
  if (str != *strp) {
    if (parse_char(strp,'=')) {
      expr *ex = gc_malloc(sizeof(expr), gc_expr_tag);
      *ex = parse_expr(strp);
      return (expr){ ex_asgn_tag, { .ex_asgn = { name, ex } } };
    }
    expr ex;
    const char *ops[] = { "+=", "-=", "*=", "/=", "%=" };
    expr_tag tags[] = { ex_add_tag, ex_sub_tag, ex_mul_tag, ex_div_tag, ex_mod_tag };
    int l = sizeof(ops) / sizeof(const char *);
    if (parse_expr_asgn_ops(strp,name,ops,tags,l,&ex)) {
      return ex;
    } else {
      *strp = str;
    }
  }
  expr ex = parse_expr_6(strp);
  if (str != *strp) {
    return ex;
  }
  return (expr){ 0, { NULL } };
}

statement *parse_statement_next(const char **strp, bool is_multi) {
  if (!is_multi) {
    return NULL;
  }
  const char *str = *strp;
  statement next;
  next = parse_statement(strp,true);
  if (str != *strp) {
    statement *nextp = gc_malloc(sizeof(statement), gc_statement_tag);
    *nextp = next;
    return nextp;
  }
  return NULL;
}

statement parse_statement(const char **strp, bool is_multi) {
  const char *str = *strp;
  if (parse_char(strp,'{')) {
    statement st = parse_statement(strp,true);
    if (parse_char(strp,'}')) {
      statement *next = parse_statement_next(strp,is_multi);
      if (st.next) {
        statement *i;
        for (i = st.next; i->next; i = i->next) {
        }
        i->next = next;
      }
      return st;
    }
    *strp = str;
  }
  if (parse_word(strp,"if") && parse_char(strp,'(')) {
    expr cond = parse_expr(strp);
    if (parse_char(strp,')')) {
      statement *st_true = gc_malloc(sizeof(statement), gc_statement_tag);
      *st_true = parse_statement(strp,false);
      statement *st_false = NULL;
      if (parse_word(strp,"else")) {
        st_false = gc_malloc(sizeof(statement), gc_statement_tag);
        *st_false = parse_statement(strp,false);
      }
      statement *next = parse_statement_next(strp,is_multi);
      return (statement){ st_if_tag, { .st_if = { cond, st_true, st_false } }, next };
    }
    *strp = str;
  }
  if (parse_word(strp,"while") && parse_char(strp,'(')) {
    expr cond = parse_expr(strp);
    if (parse_char(strp,')')) {
      const char *str0 = *strp;
      statement *st = gc_malloc(sizeof(statement), gc_statement_tag);
      *st = parse_statement(strp,false);
      if (str0 != *strp) {
        statement *next = parse_statement_next(strp,is_multi);
        return (statement){ st_while_tag, { .st_while = { cond, st } }, next };
      }
    }
    *strp = str;
  }
  if (parse_word(strp,"for") && parse_char(strp,'(')) {
    expr init = parse_expr(strp);
    if (parse_char(strp,';')) {
      expr cond = parse_expr(strp);
      if (parse_char(strp,';')) {
        expr incr = parse_expr(strp);
        if (parse_char(strp,')')) {
          const char *str0 = *strp;
          statement *st = gc_malloc(sizeof(statement), gc_statement_tag);
          *st = parse_statement(strp,false);
          if (str0 != *strp) {
            statement *next = parse_statement_next(strp,is_multi);
            return (statement){ st_for_tag, { .st_for = { init, cond, incr, st } }, next };
          }
        }
      }
    }
    *strp = str;
  }
  expr ex = parse_expr(strp);
  if (str != *strp) {
    if (parse_char(strp,';')) {
      statement *next = parse_statement_next(strp,is_multi);
      return (statement){ st_ex_tag, { .st_ex = ex }, next };
    }
  }
  if (parse_char(strp,';')) {
    if (is_multi) {
      return parse_statement(strp,true);
    } else {
      return (statement){ st_none_tag, { NULL }, NULL };
    }
  }
  // 失敗v('ω')v 
  return (statement){ 0, { NULL }, NULL };
}

value *run_str(const char *s) {
  gc_init();
  env *en = init_env();
  statement *st = gc_malloc(sizeof(statement), gc_statement_tag);
  *st = parse_statement(&s,true);
  gc_add_root(st, gc_statement_tag);
  return run(&en,st);
}

int main(int argc, char **argv) {
  run_str(
    "x = 8;\n"
    "for (i = 0; i < 4; ++i) {\n"
    "  print(x = (3 * x + 5) % 13);\n"
    "}\n"
    "gc_collect(0);\n"
    "print(time(0));\n"
    );
  run_str(
    "x = time(0) % 13;\n"
    "for (i = 0; i < 3; ++i) {\n"
    "  print(x = (3 * x + 5) % 13);\n"
    "}\n"
    "gc_collect(0);\n"
    );
}
