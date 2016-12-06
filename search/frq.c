/* Frequency of words
 *
 * This program reads the standard input,
 * counts word frequencies
 * and output them in a list sorted by frequencies.
 *
 * Author: Andreas Abel, andreas.abel@ifi.lmu.de
 * This code is placed in the public domain.
 * Do with it what you like, but leave my name in it.
 */

#include <stdio.h>        
#include <stdlib.h>       /* malloc */
#include <string.h>       /* strdup */
#include <search.h>       /* glibc search tress */

#define MAX_LENGTH 10000  /* maximum word length */

/******************************************************************
 Tries (dictionaries)
 define a finite map from strings (words) to numbers (frequencies)
 ******************************************************************/

struct node {
  int freq;    /* frequency of the word that terminates at the current node */
  struct node *(next[26]); /* array of pointers to children */
};

typedef struct node Node;

/* allocate a new Node */
Node *newNode() {
  return calloc(1, sizeof(Node)); /* calloc sets everything to 0 */
}

/* global variable: the trie in which all words are stored with their freq. */

Node *the_trie; /* will be initialized in main */

/* Process standard input, count frequencies */
void calc () {

  int c;                 /* the currently read character */
  int i;                 /* is equivalent in a=0 .. z=25 */
  Node *trie = the_trie; /* current position in trie, never NULL */

  while ((c = getchar()) != EOF) {

    /* compute i */
    if ((c >= 'A') && (c <= 'Z'))
      i = c - 'A';
    else if ((c >= 'a') && (c <= 'z'))
      i = c - 'a'; 
    else {
      /* not a letter, counts as word separator */
      trie->freq++;    /* increment counter for current word */
      trie = the_trie; /* start with new word */
      continue;        /* next iteration */
    }
    /* Now i=0..25 */
    if (trie->next[i] == NULL)
      trie->next[i] = newNode();
    trie = trie->next[i];
  }
}


/* the current word to print */

char the_string[MAX_LENGTH];

/* Iterate through trie, output frequencies */

void trie_foreach
  ( Node *trie               /* current position in trie 
                               never NULL */
  , int string_pos           /* next free character in string 
                               always < MAX_LENGTH */
  , void action(int, char*)  /* what to do with freq,word pair */
  ) 
{
  int i; /* counter for loop, 0..25 */

  /* cut off strings which are too long */
  if (string_pos >= MAX_LENGTH) {
    return;
  }

  /* print frequency of current string */
  if (trie->freq > 0) {
    the_string[string_pos] = 0; /* terminate string */
    action(trie->freq, the_string);
  }  

  /* recursively, output children */
  for (i=0; i<26; i++) {
    if (trie->next[i] != NULL) {
      the_string[string_pos] = i + 'a';
      trie_foreach(trie->next[i], string_pos+1, action);
    }
  }
}

/* an action for trie-iteration */

void print_action(int freq, char *word)
{
   printf("%6d\t%s\n", freq, word);
}

/******************************************************************
  sorting the output
  we use the glibc search trees to implement a sorted map 
  from frequencies to words
 ******************************************************************/

typedef struct {
  int freq;
  char *word;
} Entry;

Entry *newEntry(int freq, char *word) {
  Entry *entry = malloc(sizeof(Entry));
  entry->freq = freq;
  entry->word = word;
  return entry;
}

/* compare entries                          */
/* sort by frequency, biggest first         */
/* for equal freq. sort alphabetically      */
int compare_entries (const Entry *e1, const Entry *e2) {
  int dist = e2->freq - e1->freq; 
  if (dist == 0) 
    dist = strcmp(e1->word, e2->word);
  return dist;
}

Entry *the_map = NULL; /* the search tree as a global variable */

/* inserting a new word into the map */
void insert_action(int freq, char *word)
{
  Entry *entry = newEntry(freq, strdup(word)); /* word is volatile */
  tsearch(entry, &the_map, compare_entries);   /* insert new entry */
}

/* the print action for search tree traversal */
void map_print_action (Entry **entry, VISIT visit, int level) {
  switch (visit) {
  case leaf:
  case postorder:
    print_action((*entry)->freq, (*entry)->word);
  }    
}

/******************************************************************
  main
 ******************************************************************/

int main (int argc, char **argv) {

  fprintf(stderr, "frq -- word frequency analyser written by andreas.abel@ifi.lmu.de in C\n\nanalysing stdin\n");

  /* Initialize root trie */
  the_trie = newNode();

  /* Process stdin until EOF */
  calc();

  /* Extract results */
  trie_foreach (the_trie, 0, insert_action);

  /* Print results, sorted by frequency */
  twalk(the_map, map_print_action);

  return 0;
}
