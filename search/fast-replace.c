#define _XOPEN_SOURCE 500       /* strdup() */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ahocorasick.h>

enum { MAX_LINE_LEN = 4096 };

typedef struct {
    char* find;
    char* replace;
} Replacement;

static Replacement* replacement_list = NULL;
static int replacements_len = 0;

typedef struct {
    const char* line;
    int printed_upto;
} Input;

int on_match(AC_MATCH_t * m, void * param) {
    Input* input = param;

    fwrite(input->line + input->printed_upto,
        m->position - m->patterns[0].length - input->printed_upto, sizeof(char), stdout);
    input->printed_upto = m->position - m->patterns[0].length;

    const char* rstr = replacement_list[m->patterns[0].rep.number].replace;
    fwrite(rstr, strlen(rstr), sizeof(char), stdout);
    input->printed_upto = m->position;

    /* to find all matches always return 0 */
	return 0;
	/* return 0 : continue searching
	 * return none zero : stop searching
	 * as soon as you get enough from search results, you can stop search and
	 * return from ac_automata_search() and continue the rest of your program.
	 * e.g. if you only need first N matches, define a counter and return none
	 * zero after the counter exceeds N.
     **/
}

static void do_replacing(AC_AUTOMATA_t* replacer, FILE* replace_target) {

    for (;;) {
        char buf[MAX_LINE_LEN];
        if (!fgets(buf, sizeof buf, replace_target)) break;

        AC_TEXT_t line = { buf, strlen(buf) };
        Input input = { buf, 0 };
        ac_automata_reset(replacer);
        ac_automata_search(replacer, &line, &input);
        fwrite(buf + input.printed_upto, line.length - input.printed_upto, sizeof(char), stdout);
    }
}

static AC_AUTOMATA_t* load_replacements(FILE* replacements) {
    AC_AUTOMATA_t* matcher = ac_automata_init(&on_match);

    replacements_len = 16;
    replacement_list = malloc(sizeof(*replacement_list) * replacements_len);
    assert(replacement_list);

    for (int nreplacements = 0; ; nreplacements++) {
        char buf[MAX_LINE_LEN];
        if (!fgets(buf, sizeof buf, replacements)) break;

        if (nreplacements >= replacements_len) {
            replacements_len *= 2;
            replacement_list = realloc(replacement_list, sizeof(*replacement_list) * replacements_len);
            assert(replacement_list);
        }

        char* space = strchr(buf, ' ');
        assert(space);
        *space = 0;
        Replacement* r = &replacement_list[nreplacements];
        r->find = strdup(buf);
        int replacelen = strlen(space+1);
        space[1+replacelen-1] = '\0'; // remove newline
        r->replace = strdup(space+1);
        assert(r->find && r->replace);

        AC_PATTERN_t pattern;
        pattern.astring = r->find;
        pattern.length = strlen(r->find);
        pattern.rep.number = nreplacements;
        AC_ERROR_t rc = ac_automata_add(matcher, &pattern);
        assert(rc == ACERR_SUCCESS);
    }

    ac_automata_finalize(matcher);

    return matcher;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <replacements> [replace-target]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* replacements = fopen(argv[1], "r");
    if (!replacements) { perror("fopen()"); return EXIT_FAILURE; }

    AC_AUTOMATA_t* replacer = load_replacements(replacements);
    fclose(replacements);

    FILE* replace_target = argc >= 3? fopen(argv[2], "r") : stdin;
    if (!replace_target) { perror("fopen()"); return EXIT_FAILURE; }

    do_replacing(replacer, replace_target);
    ac_automata_release(replacer);
    fclose(replace_target);
    /* NOTE: exit frees replacement_list memory */

    return 0;
}
