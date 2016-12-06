#include "log.h"
#include <string.h>
#include <stdio.h>
//#define NDEBUG
#include <assert.h>

void setup_log(log_t *l);
void test_setup(log_t *l);
void test_size(log_t* l);
void test_search(log_t* l);
void test_pop(log_t* l);
void test_destroy(log_t* l);
void test_pop_to_empty(log_t* l);

int main(){
    log_t * l = malloc(sizeof(log_t));
    setup_log(l);
    test_setup(l);
    test_pop(l);
    test_size(l);
    test_search(l);
    test_pop_to_empty(l);
    test_destroy(l);
    free(l);
    return 0;
}


void setup_log(log_t *l)
{
    log_init(l);
    char* a;
    a = malloc(5 * sizeof(char));
    strncpy(a, "zero", 5);
    log_append(l, a);

    a = malloc(4 * sizeof(char));
    strncpy(a, "one", 4);
    log_append(l, a);

    a = malloc(4 * sizeof(char));
    strncpy(a, "two", 4);
    log_append(l, a);

    a = malloc(6 * sizeof(char));
    strncpy(a, "three", 6);
    log_append(l, a);
}

void test_setup(log_t *l)
{
    assert(strcmp("zero", log_at(l,0)) == 0);
    assert(strcmp("one", log_at(l,1)) == 0);
    assert(strcmp("two", log_at(l,2)) == 0);
    assert(strcmp("three", log_at(l,3)) == 0);
    printf("test_setup passed\n");
}

void test_pop(log_t* l)
{
    char* a = log_pop(l);
    assert(strcmp("three", a) == 0);
    free(a);
    printf("test_pop passed\n");
}

void test_pop_to_empty(log_t* l)
{
    char* a = log_pop(l);
    assert(strcmp("two", a) == 0);
    assert(log_size(l) == 2);
    free(a);

    a = log_pop(l);
    assert(strcmp("one", a) == 0);
    assert(log_size(l) == 1);
    free(a);

    a = log_pop(l);
    assert(strcmp("zero", a) == 0);
    assert(log_size(l) == 0);
    free(a);

    a = log_pop(l);
    assert(a == NULL);
    assert(log_size(l) == 0);
    printf("test_pop_to_empty passed\n");
}

void test_size(log_t* l)
{
    assert(log_size(l) == 3);
    printf("test_size passed\n");
}

void test_search(log_t* l)
{
    assert(strcmp("one", log_search(l, "one")) == 0);
    printf("test_search passed\n");
}

void test_destroy(log_t* l)
{
    log_destroy(l);
    printf("test_destroy passed\n");
}
