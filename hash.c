#define _GNU_SOURCE
#include <search.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

typedef struct { char *key, *value; } helem;

static int hcmp(const void *a, const void *b) {
  return strcmp(((helem *)a)->key, ((helem *)b)->key);
}

void hset(htable h, char *key, char *value) {
  helem *he = malloc(sizeof(helem));
  he->key = strdup(key);
  he->value = strdup(value);
  tsearch(he, h, hcmp);
}

char *hget(htable h, char *key) {
  helem **he = tfind(&(helem) { key, NULL }, h, hcmp);
  return he ? (*he)->value : NULL;
}

void hremove(htable h, char *key) {
  helem **he = tdelete(&(helem) { key, NULL }, h, hcmp);
  if (he) {
    free((*he)->key);
    free((*he)->value);
  }
}

static void hefree(void *e) {
  helem *he = e;
  free(he->key);
  free(he->value);
  free(he);
}

void hfree(htable h) {
  tdestroy(*h, hefree);
}
