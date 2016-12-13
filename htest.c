#include <stdio.h>
#include "hash.h"

int main() {
  htable h = emptytable;
  hset(h, "george", "harrison" );
  hset(h, "john"  , "lennon"   );
  hset(h, "paul"  , "mccartney");
  hset(h, "ringo" , "starr"    );

  printf("john -> %s\n", hget(h, "john"));
  printf("jim -> %s\n", hget(h, "jim"));
  hremove(h, "john");
  printf("john -> %s\n", hget(h, "john"));

  hfree(h);
  return 0;
}
