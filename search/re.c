/* Copyright (C) 2010 Alexandru Scvortov <scvalex@gmail.com>
 *                    http://github.com/scvalex
 *                    http://abstractbinary.org
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Memory related */

void* wrap_alloc(void* ptr) {
	if (ptr == NULL) {
		perror("Cannot allocate memory");
		exit(1);
	}
	return ptr;
}

/* Dynamic Strings */

typedef struct {
        int size; // excluding the '\0'
        int cap;
        char *str;
} DStr;

/* alloc and initialise a dynamic string */
DStr* make_dstr() {
        DStr *ds = wrap_alloc(malloc(sizeof(DStr)));
        ds->size = 0;
        ds->cap = 1;
        ds->str = wrap_alloc(malloc(ds->cap));
        ds->str[0] = '\0';
        return ds;
}

/* append one char to a dstr, realloc'ing if necessary */
void append_dstr(DStr *ds, char c) {
        if (ds->size + 1 >= ds->cap) {
                ds->cap = (ds->cap+1)*2;
                ds->str = wrap_alloc(realloc(ds->str, ds->cap));
        }
        ds->str[ds->size] = c;
        ds->str[++ds->size] = '\0';
}

/* chop the last char from a dstr */
void chop_dstr(DStr *ds) {
        ds->str[--ds->size] = '\0';
}

/* return a dstr's buffer and free the rest */
char* dstr_to_str(DStr *ds) {
        char *str = ds->str;
        free(ds);
        return str;
}

/* free a dstr's memory */
void destroy_dstr(DStr *ds) {
	free(ds->str);
	free(ds);
}

/* Simple Capturing Regular Expressions
 *
 * When a Regular Expression is checked against a subject text,
 *   - the dot '.' matches any character,
 *   - the star '*' matches the previous character zero or more times,
 *   - the carat '^' mathes any char *except* the next one zero or more times,
 *   - space ' ' matches both spaces and tabs.
 *   - every other character matches itself.
 *
 * Patterns are implicitly anchored on both ends.
 * The matching strategy is longest-match-first.
 * Star '*' and carat '^' patterns are captured.
 */

enum {END = 0, CHAR, STAR, NEG};
enum {NA = 0, ANY = '.', SPACE = ' '};

typedef struct {
	int type;
	char sym;
} Regexp;

int matchhere(Regexp*, char*, char**);
int matchstar(Regexp, Regexp*, char*, char**);
int matchchar(Regexp, char);

/* compile a string into a regular expression */
Regexp* compile_regexp(char *str) {
	Regexp *re = wrap_alloc(calloc(strlen(str) + 1, sizeof(Regexp)));
	int i;
	for (i = 0; str[0] != '\0'; i++, str++) {
		re[i].sym = str[0];
		if (str[1] == '*') {
			re[i].type = STAR;
			str++;
		} else if (str[0] == '^') {
			re[i].type = NEG;
			re[i].sym = str[1];
			str++;
		} else if (str[0] == ' ') {
			re[i].type = SPACE;
		} else if (str[0] == '.') {
			re[i].type = ANY;
		} else {
			re[i].type = CHAR;
		}
	}
	return re;
}

/* search for regexp at beginning of text */
int matchhere(Regexp *regexp, char *text, char **cs) {
	if (regexp[0].type == END)
		return *text == '\0';
	if (regexp[0].type == STAR || regexp[0].type == NEG)
		return matchstar(regexp[0], regexp+1, text, cs);

	if (*text != '\0' && matchchar(regexp[0], *text))
		return matchhere(regexp+1, text+1, cs);
	return 0;
}

/* search for c*regexp at beginning of text */
int matchstar(Regexp c, Regexp *regexp, char *text, char **cs) {
	char *t;

	DStr *ds = make_dstr();
	for (t = text; *t != '\0' && matchchar(c, *t); t++)
		append_dstr(ds, *t);
	do { /* * matches zero or more */
		if (matchhere(regexp, t, cs+1)) {
			*cs = dstr_to_str(ds);
			return 1;
		}
		chop_dstr(ds);
	} while (t-- > text);
	destroy_dstr(ds);
	return 0;
}

/* check if a regexp symbol matches a char */
int matchchar(Regexp r, char c) {
	if (r.type == ANY || r.sym == ANY)
		return 1;
	if (r.type == SPACE || r.sym == SPACE)
		return (c == ' ' || c == '\t');
	if (r.type == NEG)
		return (c != r.sym);
	return r.sym == c;
}

/* Example usage */

int main(int argc, char *argv[]) {
	Regexp *PAT = compile_regexp("a.*x^bb.*");
	char *cs[3];

	printf("Subject is: ");
	fflush(stdout);

	char *subj = NULL;
	size_t n = 48;
	n = getline(&subj, &n, stdin);
	subj[--n] = '\0';

	if (matchhere(PAT, subj, cs)) {
		printf("Match:\n");
		int i;
		for (i = 0; i < 3; ++i) {
			printf("Group %d: ``%s''\n", i, cs[i]);
			free(cs[i]);
		}
	} else {
		printf("No match :(\n");
	}
	free(subj);
	free(PAT);

	return 0;
}
