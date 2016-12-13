#include <stddef.h>

void *track_malloc(size_t size);
void *track_realloc(void *addr, size_t size);
void track_free(void *addr);
long track_byteslost(void);
