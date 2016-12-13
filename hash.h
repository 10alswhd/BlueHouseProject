typedef void** htable;
#define emptytable &(void*){ NULL }

void hset(htable, char *, char *);
char *hget(htable, char *);
void hremove(htable, char *);
void hfree(htable);
