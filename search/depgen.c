#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/stat.h>

enum {
	INC_COMMANDLINE,
	INC_AFTER,
	INC_PRESYSTEM,
	INC_SYSTEM,

	_INC_COUNT,
};

struct incldir {
	char path[4096];
	struct incldir *next;
};

struct inclset {
	struct incldir *head;
	struct incldir *tail;
	struct inclset *next;
};

static void inclset_init(struct inclset *set)
{
	set->head = set->tail = NULL;
	set->next = NULL;
}

static void inclset_fini(struct inclset *set)
{
	set->head = set->tail = NULL;
	set->next = NULL;
}

static void inclset_push(struct inclset *set, struct incldir *dir)
{
	dir->next = NULL;
	if (set->head == NULL)
		set->head = dir;
	else
		set->tail->next = dir;
	set->tail = dir;
}

struct file {
	char name[4096];
	struct file *next;
};

struct queue {
	struct file *head;
	struct file *tail;
};

static void queue_init(struct queue *queue)
{
	queue->head = queue->tail = NULL;
}

static void queue_fini(struct queue *queue)
{
	queue->head = queue->tail = NULL;
}

static void queue_push(struct queue *queue, struct file *file)
{
	file->next = NULL;
	if (queue->head == NULL)
		queue->head = file;
	else
		queue->tail->next = file;
	queue->tail = file;
}

static struct file *queue_pop(struct queue *queue)
{
	struct file *file;

	if (queue->head == NULL)
		return NULL;
	file = queue->head;
	queue->head = queue->head->next;
	if (queue->head == NULL)
		queue->tail = NULL;
	return file;
}

static unsigned int hash_string(const char *str)
{
	unsigned int key;
	unsigned int len;
	unsigned int i;

	len = strlen(str);
	key = len;

	for (i = 0; i < len; ++str, ++i)
		key = ((key << 5) ^ (key >> 27)) ^ (*str);
	return key;
}

struct hashmap_element {
	struct file *file;
	unsigned int key;
};

struct hashmap {
	unsigned int alloced;
	unsigned int count;
	struct hashmap_element *data;
};

static int hashmap_init(struct hashmap *h)
{
	h->alloced = 0;
	h->count = 0;
	h->data = NULL;
	return 0;
}

static void hashmap_fini(struct hashmap *h)
{
	if (h->data != NULL)
		free(h->data);
}

static int hashmap_hash(struct hashmap *h, unsigned int key)
{
	unsigned int idx, i;

	if (h->count == h->alloced)
		return -1;

	idx = key % h->alloced;

	for (i = 0; i < h->alloced; ++i) {
		if (h->data[idx].file == NULL)
			return idx;
		if (h->data[idx].key == key)
			return idx;
		idx = (idx + 1) % h->alloced;
	}

	return -1;
}

static int hashmap_put_keyed(struct hashmap *h, unsigned int key, struct file *file);

static int hashmap_rehash(struct hashmap *h)
{
	struct hashmap_element *e, *t;
	unsigned int o_alloced;
	unsigned int o_count;
	unsigned int n;
	unsigned int i;

	n = h->alloced + 32;
	t = (struct hashmap_element *)calloc(1, sizeof(*e) * n);
	if (t == NULL)
		return -1;

	e = h->data;
	h->data = t;
	o_alloced = h->alloced;
	o_count = h->count;
	h->alloced = n;
	h->count = 0;

	for (i = 0; i < o_alloced; ++i) {
		if (e[i].file == NULL)
			continue;
		if (hashmap_put_keyed(h, e[i].key, e[i].file)) {
			h->data = e;
			h->alloced = o_alloced;
			h->count = o_count;
			free(t);
			return -1;
		}
	}
	return 0;
}

static int hashmap_put_keyed(struct hashmap *h, unsigned int key, struct file *file)
{
	int idx;

	while ((idx = hashmap_hash(h, key)) < 0) {
		if (hashmap_rehash(h))
			return -1;
	}

	h->data[idx].file = file;
	h->data[idx].key = key;
	++h->count;

	return 0;
}

static int hashmap_put(struct hashmap *h, struct file *file)
{
	unsigned int key;
	key = hash_string(file->name);
	return hashmap_put_keyed(h, key, file);
}

static struct hashmap_element *hashmap_find(struct hashmap *h, unsigned int key)
{
	unsigned int idx, i;

	if (h->alloced == 0 || h->count == 0)
		return NULL;

	idx = key % h->alloced;
	for (i = 0; i < h->alloced; ++i) {
		if (h->data[idx].file == NULL)
			continue;
		if (h->data[idx].key == key)
			return &h->data[idx];
		idx = (idx + 1) % h->alloced;
	}
	return NULL;
}

static int hashmap_contains(struct hashmap *h, const char *name)
{
	struct hashmap_element *e;
	unsigned int key;

	key = hash_string(name);
	e = hashmap_find(h, key);
	return e != NULL;
}

static char *simple_dirname(const char *path, char *buf, unsigned blen)
{
	char *p;

	if (blen < 2)
		return 0;

	if (path[0] != '/' && !strchr(path, '/')) {
		buf[0] = '.';
		buf[1] = 0;
		return buf;
	}

	strncpy(buf, path, blen);
	buf[blen - 1] = 0;
	for (;;) {
		if (!strcmp(buf, "/"))
			return buf;
		if (!strcmp(buf, "./")) {
			buf[1] = 0;
			return buf;
		}
		p = strrchr(buf, '/');
		if (p == NULL)
			return buf;
		if (p[1] != 0)
			break;
		*p = 0;
	}
	*(p + (p == buf)) = 0;

	return buf;
}

struct depgen {
	struct hashmap map;
	struct queue pending;
	struct queue free;
	struct inclset incl[_INC_COUNT];
	struct inclset lincl;
};

static int depgen_init(struct depgen *d)
{
	int i;
	hashmap_init(&d->map);
	queue_init(&d->pending);
	queue_init(&d->free);

	for (i = 0; i < _INC_COUNT; ++i) {
		inclset_init(&d->incl[i]);
		if (i < _INC_COUNT - 1)
			d->incl[i].next = &d->incl[i + 1];
	}
	inclset_init(&d->lincl);
	return 0;
}

static void depgen_fini(struct depgen *d)
{
	struct incldir *inc;
	struct file *f;
	int i;

	f = d->pending.head;
	while (f != NULL) {
		struct file *next = f->next;
		free(f);
		f = next;
	}
	f = d->free.head;
	while (f != NULL) {
		struct file *next = f->next;
		free(f);
		f = next;
	}
	for (i = 0; i < _INC_COUNT; ++i) {
		inc = d->incl[i].head;
		while (inc != NULL) {
			struct incldir *next = inc->next;
			free(inc);
			inc = next;
		}
		inclset_fini(&d->incl[i]);
	}
	inc = d->lincl.head;
	while (inc != NULL) {
		struct incldir *next = inc->next;
		free(inc);
		inc = next;
	}
	inclset_fini(&d->lincl);

	queue_fini(&d->free);
	queue_fini(&d->pending);
	hashmap_fini(&d->map);
}

static int depgen_scan_file(struct depgen *d, struct file *file)
{
	struct inclset inclset;
	struct incldir curdir;
	char line[4096];
	char path[4096];
	FILE *fp;

	fp = fopen(file->name, "rt");
	if (fp == NULL)
		return -1;

	while (fgets(line, sizeof(line), fp)) {
		struct inclset *set;

		char *p;
		char *e;

		p = line;
		while (isspace(*p)) ++p;
		if (p[0] != '#')
			continue;
		if (strncmp(p + 1, "include", 7))
			continue;
		p += 8;
		while (isspace(*p)) ++p;
		if (*p == '<')
			e = strchr(p + 1, '>');
		else if (*p == '"')
			e = strchr(p + 1, '"');
		else
			continue;
		if (e == NULL)
			continue;

		if (e - p >= (int)sizeof(((struct file *)0)->name))
			continue;
		p += 1;

		if (*e == '"') {
			simple_dirname(file->name, curdir.path, sizeof(curdir.path));
			inclset_init(&inclset);
			inclset_push(&inclset, &curdir);
			inclset.next = &d->lincl;
			set = &inclset;
		} else {
			set = &d->incl[0];
		}
		e[0] = 0;

		for (; set != NULL; set = set ? set->next : set) {
			struct incldir *inc;

			for (inc = set->head; inc != NULL; inc = inc->next) {
				struct stat st;
				struct file *n;

				if (!strcmp(inc->path, "."))
					strcpy(path, p);
				else
					snprintf(path, sizeof(path), "%s/%s", inc->path, p);
				if (stat(path, &st))
					continue;
				if (hashmap_contains(&d->map, path)) {
					set = NULL;
					break;
				}

				n = (struct file *)calloc(1, sizeof(*n));
				if (n == NULL) {
					fclose(fp);
					return -1;
				}
				strcpy(n->name, path);
				hashmap_put(&d->map, n);
				queue_push(&d->pending, n);
				set = NULL;
				break;
			}
		}
	}
	fclose(fp);
	return 0;
}

static int depgen_scan(struct depgen *d)
{
	struct file *f;

	while ((f = queue_pop(&d->pending)) != NULL) {
		if (depgen_scan_file(d, f))
			return -1;
		queue_push(&d->free, f);
	}

	return 0;
}

static int depgen_add_incldir(struct depgen *d,
		const char *prefix, const char *name, int set)
{
	struct incldir *inc;
	int nlen, plen;

	if (prefix != NULL)
		plen = strlen(prefix);
	else
		plen = 0;

	nlen = strlen(name);
	if (nlen + plen > sizeof(inc->path) - 1)
		return -1;

	inc = (struct incldir *)calloc(1, sizeof(*inc));
	if (inc == NULL)
		return -1;

	if (plen)
		memcpy(inc->path, prefix, plen);
	memcpy(inc->path + plen, name, nlen);
	inc->path[plen + nlen] = 0;
	if (plen + nlen != 0 && inc->path[(plen + nlen) - 1] == '/')
		inc->path[(plen + nlen) - 1] = 0;
	if (set < 0) {
		inclset_push(&d->lincl, inc);
	} else {
		inclset_push(&d->incl[set], inc);
	}
	return 0;
}

static int depgen_add_file(struct depgen *d, const char *name)
{
	struct file *f;
	struct stat st;

	if (stat(name, &st))
		return -1;

	f = (struct file *)calloc(1, sizeof(*f));
	if (f == NULL)
		return -1;

	strncpy(f->name, name, sizeof(f->name));
	f->name[sizeof(f->name) - 1] = 0;
	queue_push(&d->pending, f);

	return 0;
}

static int depgen_print(struct depgen *d, FILE *out, int type)
{
	struct hashmap_element *e;
	unsigned int i, c;

	e = d->map.data;
	for (c = i = 0; i < d->map.alloced; ++i) {
		if (e[i].file == NULL)
			continue;
		if (type)
			fprintf(out, "%s%s", &" "[c == 0], e[i].file->name);
		else
			fprintf(out, "%s:\n\n", e[i].file->name);
		++c;
	}
	return 0;
}

#define VERSION "0.1"

static void version()
{
	fprintf(stderr, " - depgen version " VERSION " - \n");
}

static void usage(const char *name)
{
	fprintf(stderr,
"Usage: %s [OPTIONS]... <file>...\n"
"  -I <dir>                    add <dir> to 1st include search path\n"
"  -idirafter <dir>            add <dir> to 2nd include search path\n"
"  -isystem <dir>              add <dir> to 3rd include search path\n"
"  -isysroot <dir>             add <dir> to 4th include search path\n"
"  -sysroot <dir>              add <dir> to 4th include search path\n"
"  -iquote <dir>               add <dir> to local include search path\n"
"  -iprefix <prefix>           specify directory prefix\n"
"  -iwithprefix <dir>          add <prefix><dir> to 2nd include search path\n"
"  -iwithprefixbefore <dir>    add <prefix><dir> to 1st include search path\n"
"  -include <file>             force include <file>\n"
"  -D <def>                    macro to define (ignored)\n"
"  -U <def>                    macro to undefine (ignored)\n"
"  -o, -output <file>          output file (default is stdout)\n"
"  -r, -target <file>          target file (default is <input>.o)\n"
"  -v, -version                display version information and exit\n"
"  -h, -help                   display this help and exit\n"
"\n"
"Ignored Parameters:\n"
"  -g, -c, -S, -E, -W*, -f*, -m*, -O*, -std*, -ansi, -param* -pedantic\n"
"  -pedantic-errors -x*, -P, -X*, -A*, -nostdinc, -nostdinc++\n"
"  -pass-exit-codes, -no-integrated-cpp, -pg, -undef\n"
"\n"
		, name);
	version();
}

static void error(const char *name, const char *msg)
{
	fprintf(stderr, "%s: %s\n", name, msg);
	usage(name);
}

int main(int argc, char **argv)
{
	const char *outfile;
	const char *target;
	char prefix[4096];
	struct depgen d;
	FILE *output;
	int i;
	int c;

	prefix[0] = 0;
	target = NULL;
	outfile = NULL;
	output = stdout;

	depgen_init(&d);

	for (;;) {
		int idx = 0;
		static struct option long_options[] = {
			{"iprefix",           1, 0, 'p'},
			{"iwithprefix",       1, 0, '.'},
			{"iwithprefixbefore", 1, 0, ','},
			{"include",           1, 0, 'n'},
			{"idirafter",         1, 0, '0'},
			{"isystem",           1, 0, '1'},
			{"isysroot",          1, 0, '2'},
			{"sysroot",           1, 0, '2'},
			{"iquote",            1, 0, 'i'},
			{"output",            1, 0, 'o'},
			{"target",            1, 0, 'r'},
			{"nostdinc++",        0, 0, 'f'},
			{"nostdinc",          0, 0, 'f'},
			{"pass-exit-codes",   0, 0, 'f'},
			{"ansi",              0, 0, 'f'},
			{"pedantic-errors",   0, 0, 'f'},
			{"pedantic",          0, 0, 'f'},
			{"no-integrated-cpp", 0, 0, 'f'},
			{"undef",             0, 0, 'f'},
			{"param",             1, 0, 'f'},
			{"pg",                0, 0, 'f'},
			{"std",               1, 0, 'f'},
			{"help",              0, 0, 'h'},
			{"version",           0, 0, 'v'},
			{ 0, 0 }
		};
		c = getopt_long_only(argc, argv,
				"x:A:cPSEX:f:m:O:I:W:gD:U:o:r:hv",
				long_options, &idx);
		if (c == -1) break;

		switch (c) {
		case 'p':
			strncpy(prefix, optarg, sizeof(prefix));
			prefix[sizeof(prefix) - 1] = 0;
			break;
		case '.':
			depgen_add_incldir(&d, prefix, optarg, INC_AFTER);
			break;
		case ',':
			depgen_add_incldir(&d, prefix, optarg, INC_COMMANDLINE);
			break;
		case 'I':
			depgen_add_incldir(&d, NULL, optarg, INC_COMMANDLINE);
			break;
		case '0':
			depgen_add_incldir(&d, NULL, optarg, INC_AFTER);
			break;
		case '1':
			depgen_add_incldir(&d, NULL, optarg, INC_PRESYSTEM);
			break;
		case '2':
			depgen_add_incldir(&d, NULL, optarg, INC_SYSTEM);
			break;
		case 'i':
			depgen_add_incldir(&d, NULL, optarg, -1);
			break;
		case 'n':
			depgen_add_file(&d, optarg);
			break;
		case 'g': case 'W': case 'f': case 'm':
		case 'O': case 'c': case 'S': case 'E':
		case 'X': case 'P': case 'A': case 'x':
			/* ignored */
			break;
		case 'D':
		case 'U':
			break;
		case 'o':
			if (outfile != NULL) {
				error(argv[0], "only one output may be specified");
				goto exit_dirty;
			}
			outfile = optarg;
			break;
		case 'r':
			if (target != NULL) {
				error(argv[0], "only one target may be specified");
				goto exit_dirty;
			}
			target = optarg;
			break;
		case 'h':
			usage(argv[0]);
			goto exit_clean;
		case 'v':
			version();
			goto exit_clean;
		case '?':
		default:
			usage(argv[0]);
			goto exit_dirty;
		}
	}

	if (argc == optind) {
		error(argv[0], "at least one source file must be specified");
		goto exit_dirty;
	}

	if (outfile != NULL && strcmp(outfile, "-")) {
		output = fopen(outfile, "wt");
		if (output == NULL) {
			perror(outfile);
			goto exit_dirty;
		}
	} else {
		outfile = "";
	}

	for (i = optind; i < argc; ++i) {
		if (depgen_add_file(&d, argv[i]))
			argv[i] = 0;
	}

	depgen_scan(&d);
	for (i = optind; i < argc; ++i) {
		if (argv[i] == 0)
			continue;
		if (target == NULL) {
			fprintf(output, "%s.o %s: %s ", argv[i], outfile, argv[i]);
		} else {
			fprintf(output, "%s %s: %s ", target, outfile, argv[i]);
		}
		depgen_print(&d, output, 1);
		fprintf(output, "\n\n");
	}
	depgen_print(&d, output, 0);

exit_clean:
	depgen_fini(&d);
	if (output != stdout)
		fclose(output);
	return 0;
exit_dirty:
	depgen_fini(&d);
	if (output != NULL && output != stdout)
		fclose(output);
	return 1;
}
