#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LINE_BUFFER_LENGTH 1024
#define DEFAULT_LINE_BUFFER_INCREMENT DEFAULT_LINE_BUFFER_LENGTH

#define ARG_IS_NOT_SEARCH_WORD "-x"
#define ARG_SEARCH_WORD "-c"
#define ARG_FILE_STDIN "-"

typedef struct _arg_file {
  struct _arg_file *next;
  struct _arg_file *prev;

  char *name;
  FILE *fhandle;
} arg_file;

typedef struct _arg_context {
  bool is_not_search_word;
  char *search_word;
  arg_file *first_file;
} arg_context;

void usage(const char *message) {
  fprintf(stderr, "Syntax: \n");
  fprintf(stderr, "reverse [–c WORD [–x]] [FILES...]\n");

  if (message != NULL) 
    fprintf(stderr, "Hinweis: %s\n", message);
}

void cleanup_arg_file(arg_file *file) {
  if (file->fhandle != NULL && strcmp(file->name, ARG_FILE_STDIN) > 0)
      fclose(file->fhandle);

  if (file->name != NULL)
      free(file->name);

  free(file);
}

void cleanup_and_exit(arg_context *ctx, int exit_code) {
  if (ctx->search_word != NULL)
    free(ctx->search_word);
 
  arg_file *current_file = ctx->first_file; 
  arg_file *next_file = NULL;
  while(current_file != NULL) {
    next_file = current_file->next; 
    cleanup_arg_file(current_file);
    current_file = next_file;
  }

  exit(exit_code);
}

arg_file *create_file_arg_for_filename(arg_context *ctx, char *filename) {
  arg_file *new_file = calloc(1, sizeof(arg_file));

  FILE *fhandle;
  if (strcmp(filename, ARG_FILE_STDIN) == 0) {
    fhandle = stdin;
  }
  else {
    fhandle = fopen(filename, "r");
    if (fhandle == NULL) {
      char error_msg[DEFAULT_LINE_BUFFER_LENGTH];
      sprintf(error_msg, "%s: %s", filename, strerror(errno));

      usage(error_msg);
      free(filename);
      cleanup_and_exit(ctx, 2);
    }
  }

  new_file->name = filename;
  new_file->fhandle = fhandle;

  return new_file;
}

bool append_file_to_ctx(arg_context *ctx, arg_file *new_file) {
  if (ctx->first_file == NULL) {
    ctx->first_file = new_file;
    return true;
  }

  arg_file *current_file = NULL;
  for(current_file = ctx->first_file; current_file->next != NULL; current_file = current_file->next) {
    if (strcmp(current_file->name, new_file->name) == 0)
      return false;
  }

  current_file->next = new_file;
  new_file->prev = current_file;

  return true;
}

void create_file_arg_and_append_to_ctx(arg_context *ctx, char *filename) {
  arg_file *new_file = create_file_arg_for_filename(ctx, filename);
  if (append_file_to_ctx(ctx, new_file) == false) {
    cleanup_arg_file(new_file);  
  }
}

size_t consume_is_not_search_word_arg(arg_context *ctx, char **argv) {
  char *current_arg = *argv;
  
  if (strstr(current_arg, ARG_IS_NOT_SEARCH_WORD) == NULL)
    return 0;

  ctx->is_not_search_word = true;
  return 1;
}

size_t consume_search_word_arg(arg_context *ctx, char **argv) {
  char *current_arg = *argv;

  if (strstr(current_arg, ARG_SEARCH_WORD) == NULL)
    return 0;

  // -cSUCHWORT
  if (strlen(current_arg) > strlen(ARG_SEARCH_WORD)) {
    ctx->search_word = strndup((current_arg + strlen(ARG_SEARCH_WORD)),
                               (strlen(current_arg) - strlen(ARG_SEARCH_WORD)));

    return 1;
  }
  // -c SUCHWORT
  
  char *next_arg = *(++argv);
  if (next_arg == NULL || next_arg[0] == '-') {
    usage("Nach -c muss ein SUCHWORT folgen");
    cleanup_and_exit(ctx, 1);
  }

  ctx->search_word = strndup(next_arg, strlen(next_arg));
  return 2;
}

size_t consume_file_arg(arg_context *ctx, char **argv) {
  char *current_arg = *argv;

  create_file_arg_and_append_to_ctx(ctx, strdup(current_arg));

  return 1;
}

size_t consume_next_argument(arg_context *ctx, char **argv) {
  size_t consume_count = 0;
  
  if ((consume_count = consume_is_not_search_word_arg(ctx, argv)) > 0)
    return consume_count;

  if ((consume_count = consume_search_word_arg(ctx, argv)) > 0) 
    return consume_count;

  consume_count = consume_file_arg(ctx, argv);
  return consume_count;
}

void create_default_file_arg_if_neccessary(arg_context *ctx) {
  if (ctx->first_file == NULL)
    create_file_arg_and_append_to_ctx(ctx, strdup(ARG_FILE_STDIN));
}

char *read_next_line(arg_file *file) {
  char *line = NULL; 

  char c = EOF;
  size_t idx = 0;
  for(size_t r = 1; (c = fgetc(file->fhandle)) != EOF; r--) {
    if (r <= 1) {
      line = (char *)realloc(line, DEFAULT_LINE_BUFFER_INCREMENT);
      r = DEFAULT_LINE_BUFFER_INCREMENT;
    }

    if (c == '\n')
      break;

    line[idx++] = c;    
  }
  
  if (line != NULL)
    line[idx] = '\0';

  return line;
}

char *reverse_word(char *orig_word) {
  char *new_word = strdup(orig_word);
  
  size_t n = (unsigned int)strlen(orig_word);
  for (size_t i = 0; i < n; i++) 
    new_word[n - i - 1] = orig_word[i];

  return new_word;
}

void print_reversed_line(char *line) {
  char *delimiter = " ,.;!";
  
  for(char *orig_token = strtok(line, delimiter); orig_token != NULL; orig_token = strtok(NULL, delimiter)) {

    char *new_token = reverse_word(orig_token);
    printf("%s ", new_token);

    free(new_token);
  }

  printf("\n");
}

void cat_single_file(arg_context *ctx, arg_file *file) {
  printf("%s >>>\n", file->name);

  char *line = NULL;
  while ((line = read_next_line(file)) != NULL) {
    // Kein Suchbegriff.
    if (ctx->search_word == NULL) {
      print_reversed_line(line);
      free(line);

      continue;
    }

    bool search_word_found = (strstr(line, ctx->search_word)) != NULL ? true : false;
    
    // Zeile normal ausgeben, wenn Suchwort gefunden und mit -x negiert
    // oder Suchwort nicht gefunden
    if (  (search_word_found == true  && ctx->is_not_search_word == true)
        ||(search_word_found == false && ctx->is_not_search_word == false))
    {
      printf("%s\n", line);
    }
    else {
      print_reversed_line(line);
    }

    free(line);
  }

  printf("<<< %s\n", file->name);
}

void cat_files_from_arg_context(arg_context *ctx) {
  for(arg_file *current_file = ctx->first_file; current_file != NULL; current_file = current_file->next) {
    cat_single_file(ctx, current_file);
  }
}

int main(int argc, char *argv[]) {
  arg_context ctx;

  argv = (argv + 1);
  while(*argv != NULL) {
    size_t consume_count = consume_next_argument(&ctx, argv);
    argv += consume_count;
  }

  create_default_file_arg_if_neccessary(&ctx);
  cat_files_from_arg_context(&ctx);

  cleanup_and_exit(&ctx, 0);
}
