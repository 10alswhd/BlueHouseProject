#include "document.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void failed_write_to_file(const char *filename) {
    fprintf(stderr, "Cannot write to %s\n", filename);
}

void write_line_to_file(const char *line, FILE *fp) {
    if(line) {
        fprintf(fp, "%s\n", line);
    } else {
        fprintf(fp, "\n");
    }
}

void print_usage_error() {
    printf("\n  editor <filename>\n\n");
}

void print_line(Document *document, size_t index) {
    char *line = (char *)Document_get_line(document, index);
    if (line) {
        printf("%zu\t%s\n", index+1, line);
    } else {
        printf("%zu\n", index+1);
    }
}

void print_document_empty_error() {
    fprintf(stderr, "This file has no lines to display!\n");
}

void invalid_line() {
    fprintf(stderr, "Invalid Line Number!\n");
}

void invalid_command(const char *command) {
    fprintf(stderr, "Invalid command: \"%s\"\n", command);
}

void print_search_line(int line_number, const char *line, const char *start, const char *search_term) {
    int search_term_len = strlen(search_term);
    printf("%d\t%.*s[%s]%s\n", line_number, (int)(start - line), line, search_term, start + search_term_len);
}

char **strsplit(const char* str, const char* delim, size_t* numtokens) {
    char *s = strdup(str);
    size_t tokens_alloc = 1;
    size_t tokens_used = 0;
    char **tokens = calloc(tokens_alloc, sizeof(char*));
    char *token, *rest = s;
    while ((token = strsep(&rest, delim)) != NULL) {
        if (tokens_used == tokens_alloc) {
            tokens_alloc *= 2;
            tokens = realloc(tokens, tokens_alloc * sizeof(char*));
        }
        tokens[tokens_used++] = strdup(token);
    }
    if (tokens_used == 0) {
        free(tokens);
        tokens = NULL;
    } else {
        tokens = realloc(tokens, tokens_used * sizeof(char*));
    }
    *numtokens = tokens_used;
    free(s);
    return tokens;
}

int validate_command(char expected_prefix, char * command,
    size_t * number_arg,
    char ** string_arg,
    int command_flag)
{
  if (!command) {
    printf("null command\n");
    return COMMAND_ERROR;
  }

  // first check that we got the prefix
  if (strlen(command) <= 0 || command[0] != expected_prefix) {
    printf("wrong prefix\n");
    return COMMAND_ERROR;
  }

  // check the possible cases in reverse order (most complicated to simplest)
  // is it COMMAND_STR_ONLY?
  if (command_flag & COMMAND_STR_ONLY) {
    // the rest of the command is used as the string argument to the command
    *string_arg = command + 1;
    return COMMAND_STR_ONLY;
  }

  // if we didn't match that, try for num and string
  // we are going to need the string to be separated by spaces now
  // not doing this before COMMAND_STR_ONLY because we don't want to modify the
  // string at all in that case
  char *strings[4] = {NULL, NULL, NULL, NULL};

  char delim = ' ';
  char * curr = command;
  size_t counter = 0;
  while (1) {
    strings[counter] = strsep(&curr, &delim);

    // we ran out of spaces, time to stop
    if (strings[counter] == NULL)
      break;

    // we handled the first to entires, time to stop
    if (counter == 1) {
      // need to hold on to the rest of the string
      strings[counter+1] = curr;
      break;
    }

    counter++;
  }

  size_t num;
  int have_num = 0;
  if (strings[1]) {
    have_num = 1;
  }

  if (have_num
      && (command_flag & COMMAND_SC_AND_NUM_AND_STR || command_flag & COMMAND_SC_AND_NUM)) {
    // check for the number, anything that can be read with strtol should be
    // valid. We should have also taken care of any whitespace
    // all of the remaining cases require a number here, so we can fail if we
    // don't find one

    // don't assign to num yet, we haven't returned officially stating that we
    // did
    char * remain;
    num = strtol(strings[1], &remain, 10);
    if (strlen(remain) != 0)
      return COMMAND_ERROR;
  }

  // now, we need to check if we got a string at the end or not
  if (have_num && (command_flag & COMMAND_SC_AND_NUM_AND_STR && strings[2])) {
    *number_arg = num;
    *string_arg = strings[2];
    return COMMAND_SC_AND_NUM_AND_STR;
  }

  if (have_num && (command_flag & COMMAND_SC_AND_NUM)) {
    *number_arg = num;
    return COMMAND_SC_AND_NUM;
  }

  if (command_flag & COMMAND_SC) {
    return COMMAND_SC;
  }

  return COMMAND_ERROR;
}
