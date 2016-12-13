// "Poor man's valgrind"
#include "pmvg.h"
#include <stdlib.h>
#include <search.h>
static void *track_tree;
struct track_pair {
    void *addr;    size_t size;
};

static long bytes_lost;

static int track_pair_finder(const void *a, const void *b)
{
    return b - a;
}

void *track_malloc(size_t size)
{
    void *addr = malloc(size);

    struct track_pair **where = tsearch(addr, &track_tree, track_pair_finder);
    *where = malloc(sizeof **where);
    (*where)->addr = addr;
    (*where)->size = size;

    return addr;
}

void *track_realloc(void *addr, size_t size)
{
    if (addr)
        tdelete(addr, &track_tree, track_pair_finder);

    void *ptr = realloc(addr, size);

    struct track_pair **where = tsearch(ptr, &track_tree, track_pair_finder);
    *where = malloc(sizeof **where);
    (*where)->addr = ptr;
    (*where)->size = size;

    return ptr;
}

void track_free(void *addr)
{
    free(addr);

    //struct track_pair **where =
    tdelete(addr, &track_tree, track_pair_finder);
    //free(*where);
    //*where = NULL;
}

static void treewalker(const void *nodep, const VISIT which, const int depth)
{
    struct track_pair * const *what = nodep;
    if (which == postorder)
        bytes_lost += (*what)->size;
}

long track_byteslost(void)
{
    bytes_lost = 0;
    twalk(track_tree, treewalker);
    return bytes_lost;
}
