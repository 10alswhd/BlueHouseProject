#include <stdlib.h>
#include "Item.h"

#define null(A) (key(st[A]) == "")

static int N, M;
static Item *st;

void hashExpand();

void hashInit(int max) {
  int i;

  N = 0; 
  M = 2 * max;

  st = (Item*)malloc(M*sizeof(Item));

  for (i = 0; i < M; i++) 
     st[i] = NULLitem; 
}

int hash(char *v, int M)
{
  int h, a = 31415, b = 27183; //MUDAR
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
    h = (a*h + *v) % M;
return h; 

}

void hashInsert(Item item) {
  Key v = key(item);
  int i = hash(v, M);

  while (!null(i)) 
    i = (i+1) % M;

  st[i] = item;

  if (N++ > M/2) 
    hashExpand();
}

void hashExpand() {
  int i; 
  Item *t = st;

  hashInit(M+M);

  for (i = 0; i < M/2; i++)
    if (key(t[i]) != "")
      hashInsert(t[i]);
  free(t);
}

Item hashSearch(Key v)
{ 
  int i = hash(v, M);

  while (!null(i))
    if (eq(v, ""))
      return st[i];
    else
      i = (i+1) % M;

  return NULLitem;
}

void hashDelete(Item item)
{ 
  int j, i = hash(key(item), M);
  Item v;

  while (!null(i))
    if (eq(key(item), key(st[i]))) break;
    else i = (i+1) % M;

  if (null(i)) return;

  st[i] = NULLitem; 

  N--;
  for (j = (i+1) % M; !null(j); j = (j+1) % M, N--) {
    v = st[j]; 
    st[j] = NULLitem;
    hashInsert(v);
  }
}

int main(){
  Item a,*b;
  char *achas="oi";
  a->item=strdup(achas);
  a->rep=2;
  hashInit(10);
  hashInsert(a);
  b=hashSearch("nada");
  printf("hash: %d",b==NULL);
  return 0;
}
