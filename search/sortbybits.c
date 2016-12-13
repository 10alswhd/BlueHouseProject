#include <stdio.h>
#include <stdlib.h>



typedef struct {
  int n; /* number of integers */
  int m; /* current number of bits */
  int top; /* current top */
  int *st; /* current stack */
  unsigned x; /* number represented by the stack */
} sortbybits_t;



static sortbybits_t *sortbybits_open(int n)
{
  sortbybits_t *sbb;

  if ((sbb = calloc(1, sizeof(*sbb))) == NULL) exit(1);
  sbb->n = n;
  sbb->m = 1;
  if ((sbb->st = calloc(n + 1, sizeof(int))) == NULL) exit(1);
  sbb->st[sbb->top = 0] = 0;
  sbb->x = 0;
  return sbb;
}



static void sortbybits_close(sortbybits_t *sbb)
{
  free(sbb->st);
  free(sbb);
}



static unsigned sortbybits_next(sortbybits_t *sbb)
{
  int top = sbb->top, *st = sbb->st, n = sbb->n, m = sbb->m, v;
  unsigned x = sbb->x;

START:
  while (top >= 0) {
    if ( st[top] < n ) { /* push */
      v = st[top];
      /* push if we still have numbers to fill */
      if (top < m - 1) {
        /* the number on the next level must be greater than
         * the number on this level */
        st[++top] = v + 1;
        x ^= 1u << v; /* add the vth bit */
        continue;
      } else { /* we are at the top, save the state and leave */
        st[sbb->top = top] = v + 1; /* v is no longer available on top */
        return (sbb->x = x) ^ (1u << v);
      }
    }
    if (--top >= 0) /* pop, mark st[top] as unavailable */
      x ^= 1u << st[top]++; /* remove the st[top]th bit */
  }

  if (m < n) { /* restart the search */
    sbb->m = ++m;
    x = 0;
    st[top = 0] = 0;
    goto START;
  }
  return 0;
}



int main(int argc, char **argv)
{
  int n = 4;
  unsigned x;
  sortbybits_t *sbb;

  if (argc >= 2) n = atoi(argv[1]);

  sbb = sortbybits_open(n);
  while ( (x = sortbybits_next(sbb)) != 0 )
    printf("x %#x\n", x);
  sortbybits_close(sbb);

  return 0;
}
