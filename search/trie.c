#include "trie.h"

void trie_create (trie_t **trie, char edgeName, trie_t *previousSibling, trie_t *parent)
{
  *trie = calloc(1, sizeof(struct trie));

  (*trie)->edgeName = edgeName;

  if (previousSibling == NULL) {
    if (parent != NULL) parent->firstChild = *trie;
  } else {
    previousSibling->nextSibling = *trie;
  }
}

void trie_destroy (trie_t **trie)
{
  while ((*trie)->firstChild != NULL)
    trie_destroy(&(*trie)->firstChild);

  trie_t *next = (*trie)->nextSibling;

  free(*trie);

  *trie = next;
}

int trie_search (trie_t *trie, char *name, trie_t **dest)
{
  while (*name != '\0') {
    if (trie == NULL) {
      return 0;
    } else if (trie->edgeName == *name) {
      if (*++name != '\0')
        trie = trie->firstChild;
    } else {
      trie = trie->nextSibling;
    }
  }
  *dest = trie;
  return 1;
}
