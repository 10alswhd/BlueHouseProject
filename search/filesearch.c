#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

#define FOPEN_RO "r"
#define TXT_EXT ".txt"

/*
 *  search the path for the given word
 */
void search(char *dir, char *w) {

  FILE *f;

  // Open file
  if ((f = fopen(dir, FOPEN_RO)) == NULL)
    return;

  char *l = NULL;
  size_t n = 0;
  ssize_t r;

  // Get the next line
  while ((r = getline(&l, &n, f)) != -1) {

    // Check for position of w in l
    if(strstr(l, w) != NULL) {

      // TODO: Printing of the file name not threadsafe
      // Perhaps we want to write to a file or something else?

      // Print file name
      printf("%s\n", dir);
      free(l);
      return;

    }

  }

  // Release resource
  if (l != NULL)
    free(l);

}

/*
 * Check if str ends with qlen (case insensitive)
 */
int endswith(char *str, char *q, int qlen) {

  // Check string length
  int slen = strlen(str);

  // Iterate the length of the extension
  for (int i = 0; i < qlen; i++) {

    // Check extension by iterating down from back return if no match
    if (tolower(str[slen - i]) != tolower(q[qlen - i]))
      return -1;

  }

  // OK
  return 1;

}

/*
 * usage: filesearch directory querystring
 */
int  main(int argc, char *argv[]) {

  DIR *dir;
  struct dirent *ent;

  // Open the directory for listing
  if ((dir = opendir (argv[1])) == NULL) {
    perror("Could not open directory");
    closedir(dir);
    return -1;
  }

  // Check the length of the extension
  int ext_len = strlen(TXT_EXT);

  // Iterate the files in the directory
  while ((ent = readdir (dir)) != NULL) {

    // Filter by extensions
    if (endswith(ent->d_name, TXT_EXT, ext_len) < 0)
      continue;

    // Fork, and carry on the condition if child only
    if (fork() == 0) {

      // Execute search for needle in haystack and exit thread when done
      search(ent->d_name, argv[2]);
      exit(0);

    }

  }

  // Release resource
  closedir (dir);

}
