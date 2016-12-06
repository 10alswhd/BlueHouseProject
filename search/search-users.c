/*
 *  modify const char *search = "your@email.com";
 *
 *  gcc -O2 -Wall search-users.c -o search-users
 *
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char line[1024];
  int size = sizeof(line);
  FILE *fp = fopen("users", "rb"); // you know the adobe file...
  const char *search = "youraddress@example.com";

  while (fgets(line, size, fp) != NULL) {
    if (strnstr(line, search, size)) {
      printf("your email/password have been compromised\n");
      fputs(line, stdout);
      break;
    }
  }

  fclose(fp);
  return 0;
}
