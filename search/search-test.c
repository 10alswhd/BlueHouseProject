#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define TEST_NROUNDS 2e6
#define TEST_NITEMS 10000


struct test_case {
    char *name;
    void (*insert)(uint32_t);
    int (*search)(uint32_t);
};

static uint32_t keys[TEST_NITEMS];

static double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + ((double)tv.tv_usec / 1e6);
}

/**********************************************************************
 * Linear search
 **********************************************************************/
static uint32_t linear_items[TEST_NITEMS];
static uint32_t linear_nitems;

static void linear_insert(uint32_t addr)
{
    linear_items[linear_nitems++] = addr;
}

static int linear_search(uint32_t addr)
{
    int i;
    for (i = 0; i < linear_nitems; ++i) {
        if (linear_items[i] == addr)
            return 1;
    }
    return 0;
}

/**********************************************************************
 * binary search
 **********************************************************************/
static uint32_t binary_items[TEST_NITEMS];
static uint32_t binary_nitems;

static void binary_insert(uint32_t addr)
{
    int low = 0, high = binary_nitems;
    if (binary_nitems > 0) {
        while (low < high) {
            int mid = low + ((high - low) >> 1); 
            if (binary_items[mid] < addr)
                low = mid + 1;
            else if (addr < binary_items[mid])
                high = mid;
            else
                break;
        }
        memmove(&binary_items[low + 1], &binary_items[low],
                sizeof(uint32_t) * (binary_nitems - low));
    } 
    binary_items[low] = addr;
    ++binary_nitems;
}

static int binary_search(uint32_t addr)
{
    int low = 0, high = binary_nitems - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1); 
        if (binary_items[mid] < addr)
            low = mid + 1;
        else if (addr < binary_items[mid])
            high = mid;
        else
            return 1;
    }
    return 0;
}

/**********************************************************************
 * radix search
 **********************************************************************/
#define RADIX_BITS 4
#define RADIX_BASE (1 << RADIX_BITS)
#define RADIX_MASK (~(-RADIX_BASE))

#define LOOKUP_BITS 16
#define LOOKUP_SIZE (1 << LOOKUP_BITS)
#define LOOKUP_MASK (~(-LOOKUP_SIZE))

struct radix_node {
    uint32_t addr;
    struct radix_node *children[RADIX_BASE];
};

static struct radix_node *radix_lookup[1 << LOOKUP_BITS];
static struct radix_node radix_mem[2 * TEST_NITEMS];
static int radix_mem_free;

static struct radix_node *radix_node_alloc()
{
    return &radix_mem[radix_mem_free++];
}

static void radix_insert_0(struct radix_node *node, uint32_t addr)
{
    uint32_t index = addr & RADIX_MASK;
    addr >>= RADIX_BITS;

    if (!node->children[index]) {
        node->children[index] = radix_node_alloc();
        node->children[index]->addr = addr;
    }
    if (addr != node->addr >> RADIX_BITS) {
        radix_insert_0(node->children[index], addr);
        radix_insert_0(node->children[index], node->addr >> RADIX_BITS);
    }
}

static void radix_insert(uint32_t addr)
{
    uint32_t index = addr & LOOKUP_MASK;
    if (!radix_lookup[index]) {
        radix_lookup[index] = radix_node_alloc();
        radix_lookup[index]->addr = addr >> LOOKUP_BITS;
    } else {
        radix_insert_0(radix_lookup[index], addr >> LOOKUP_BITS);
    }
}

static int radix_search_0(struct radix_node *node, uint32_t addr)
{
    uint32_t index = addr & RADIX_MASK;
    if (!node->children[index])
        return node->addr == addr;
    else
        return radix_search_0(node->children[index], addr >> RADIX_BITS);
}

static int radix_search(uint32_t addr)
{
    uint32_t index = addr & LOOKUP_MASK;
    return radix_search_0(radix_lookup[index], addr >> LOOKUP_BITS);
}

/**********************************************************************
 * test functions
 **********************************************************************/
static void run_test(struct test_case *tc)
{
    int i, j;
    int nhits = 0, nmisses = 0;
    double start, insert_total, search_total;

    start = get_time();
    for (i = 0; i < TEST_NITEMS; ++i)
        tc->insert(keys[i]);
        
    insert_total = get_time() - start;

    start = get_time();
    for (i = 0; i < TEST_NROUNDS / TEST_NITEMS; ++i)
        for (j = 0; j < TEST_NITEMS; ++j)
            if (!tc->search(keys[j]))
                ++nmisses;
            else
                ++nhits;
    search_total = get_time() - start;

    printf("%10s: insert %.4g s, %.4g ns/op\n",
           tc->name, insert_total, insert_total / TEST_NITEMS * 1e9);
    printf("%10s  search %.4g s, %.4g ns/op, %d hits, %d misses\n",
           "", search_total, search_total / TEST_NROUNDS * 1e9, nhits, nmisses);
}

int main(void)
{
    int i;
    struct test_case radix_test = {
        .name = "radix", .insert = radix_insert, .search = radix_search
    };
    struct test_case binary_test = {
        .name = "binary", .insert = binary_insert, .search = binary_search
    };
    struct test_case linear_test = {
        .name = "linear", .insert = linear_insert, .search = linear_search
    };

    for (i = 0; i < TEST_NITEMS; ++i)
        keys[i] = (uint32_t)rand();

    run_test(&radix_test);
    run_test(&binary_test);
    run_test(&linear_test);
}
