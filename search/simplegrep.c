#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include <dirent.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>

#define CKEYWORD "\x1B[31m"
#define CFILENAME "\x1B[35m"
#define CLINENUM "\x1B[32m"
#define CBYTEOFT "\x1B[32m"
#define CCOLON "\x1B[36m"
#define RESETC "\033[0m"

struct Option
{
    bool case_sensitive;    // -i
    bool invert;            // -v
    bool line_number;       // -n
    bool filename_only;     // -l
    bool suppress;          // -h
    bool whole_word;        // -w
    bool whole_line;        // -x
    bool count_succ;        // -c
    int stop_count;         // -m
    bool byte_offset;       // -b
    int compare_time;      // -p
    int above;              // -A
    int below;              // -B
    bool recur;

    bool one_file_only;
};

typedef struct Option Opt;

Opt* get_default_option() {
    Opt* option = (Opt*) malloc(sizeof(Opt));
    option->case_sensitive = true;
    option->invert         = false;
    option->line_number    = false;
    option->filename_only  = false;
    option->suppress       = false;
    option->whole_word     = false;
    option->whole_line     = false;
    option->count_succ     = false;
    option->stop_count     = -1;
    option->byte_offset    = false;
    option->compare_time   = -1;    // not comparing; 0: kmp; 1: strstr
    option->above          = 0;
    option->below          = 0;
    option->one_file_only  = false;
    option->recur          = false;

    return option;
}

int* kmp_table(const char* p) {
    const int Np = strlen(p);
    int *T = (int*) malloc (sizeof (int)*Np);
    int pos = 2;
    int size = 0;
    T[0] = -1;
    T[1] = 0;

    while (pos < Np) {
        if (p[pos-1] == p[size]) {
            size++;
            T[pos] = size;
            pos++;
        }
        else if (size > 0) {
            size = T[size];
        }
        else {
            T[pos] = 0;
            pos++;
        }
    }

    return T;
}

int kmp_search(const char* s, const char* p, int* T, int start_idx) {
    const int Ns = strlen(s);
    const int Np = strlen(p);

    if (Ns < Np) return -1;

    int m = start_idx;
    int i = 0;
    while (m+i < Ns) {
        if (p[i] == s[m+i]) {
            if (i == Np-1)
                return m;
            i++;
        }
        else if (T[i] > -1) {
            m = m + i - T[i];
            i = T[i];
        }
        else {
            i = 0;
            m++;
        }
    }

    return -1;
}

char* to_upper_case(const char* s) {
    int len = strlen(s);
    char* new_s = (char*) malloc(sizeof(char)*(len+1));
    new_s[len] = 0;

    for (int i=0; i<len; i++) {
        if ('a' <= s[i] && s[i] <= 'z')
            new_s[i] = s[i] - 'a' + 'A';
        else
            new_s[i] = s[i];
    }

    return new_s;
}

bool is_all_digit(const char* s) {
    int len = strlen(s);
    for (int i=0; i<len; i++)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}

void search_file_print(Opt* option, const char* p, int* T, const char* path) {
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        printf("ERROR: unable to open %s!\n", path);
        return;
    }

    long long byte_offset_cnt = 0;
    long long line_number_cnt = 1;
    long long success_cnt = 0;

    const int Np = strlen(p);

    char inp[1024];

    if (option->compare_time == -1 && option->count_succ && option->suppress == false) {
        printf(CFILENAME "%s" RESETC, path);
        printf(CCOLON ":" RESETC);
    }

    // main loop
    while (fgets(inp, 1024, f) != NULL) {
        int len = strlen(inp);

        // remove \n read in by fgets
        if (inp[len-1] == '\n') {
            inp[len-1] = '\0';
            len--;
        }

        if (len == 0) continue;

        // case_sensitive
        char* s = (char*) malloc (sizeof(char) * (len+1));
        if (option->case_sensitive == false)
            s = to_upper_case(inp);
        else
            strcpy(s, inp);

        // invert
        bool success_flag = ((option->invert) ? false: true);

        // perform search
        int idx;
        bool found = false;

        int start_idx = 0;
		for (start_idx = 0; start_idx + Np-1 < len; start_idx = idx+1) {
			if (option->compare_time == 1) {
				char* flag = strstr(s+start_idx, p);
                if (flag == NULL)
                    idx = -1;
                else
                    idx = flag - s;
			}
			else if (option->compare_time <= 0) {
				idx = kmp_search(s, p, T, start_idx);
			}

			if (idx != -1 && option->whole_line) {
				if (idx == 0 && len == Np) {
					found = true;
					break;
				}
				else
					continue;
			}

			if (idx != -1 && option->whole_word) {
				int start = idx;
                int end = idx+Np-1;

                if (start >= 1 && isalpha(s[start-1]) != 0)
                    continue;
                else if (end+1 < len && isalpha(s[end+1]) != 0)
                    continue;

                found = true;
                break;
			}

			if (idx != -1) {
				found = true;
				break;
			}
			else {
				found = false;
				break;
			}
		}

        /*int start_idx = 0;
        while (found != success_flag && start_idx + Np-1 < len) {
            if (option->compare_time == 1) {
                char* flag = strstr(s+start_idx, p);
                if (flag == NULL)
                    idx = -1;
                else
                    idx = flag - s;
            }
            else if (option->compare_time <= 0) {
                idx = kmp_search(s, p, T, start_idx);
            }
            found = ((idx == -1) ? false: true);
            printf("found: %d\n", found);
            // whole_line/ whole_word
            if (found && option->whole_line) {
                if (idx == 0 && len == Np)
                    found = true;
                else
                    found = false;
            }
            if (found && option->whole_word) {
                int start = idx;
                int end = idx+Np-1;
                if (start >= 1 && isalpha(s[start-1]) != 0)
                    found = false;
                else if (end+1 < len && isalpha(s[end+1]) != 0)
                    found = false;
            }
            if (idx == -1 && option->invert == false) break;
            start_idx = idx+1;
            //printf("::%d\n", start_idx);
        }*/

		//printf("%s: %d, %d\n", inp, found, success_flag);

        if (found == success_flag) {
            // print filename
            if (option->count_succ == false && option->suppress == false &&
                option->one_file_only == false && option->compare_time == -1) {
                printf(CFILENAME "%s" RESETC, path);
                if (option->filename_only) {
                    printf("\n");
                    return;
                }
                else {
                    printf(CCOLON ":" RESETC);
                }
            }

            // line number
            if (option->compare_time == -1 && option->line_number) {
                printf(CLINENUM "%lld" RESETC, line_number_cnt);
                printf(CCOLON ":" RESETC);
            }
            // byte_offset
            if (option->compare_time == -1 && option->byte_offset) {
                printf(CBYTEOFT "%lld" RESETC, byte_offset_cnt);
                printf(CCOLON ":" RESETC);
            }

            // count success
            success_cnt++;

            // print line
            if (option->compare_time == -1 && option->count_succ == false) {
                if (idx != -1) {
                    for (int i=0; i<idx; i++)
                        printf("%c", inp[i]);
                    for (int i=idx; i<idx+Np; i++)
                        printf(CKEYWORD "%c" RESETC, inp[i]);
                    for (int i=idx+Np; i<len; i++)
                        printf("%c", inp[i]);
                    printf("\n");
                }
                else
                    printf("%s\n", inp);
            }

            if (option->stop_count != -1 && success_cnt >= option->stop_count) {
                return;
            }
        }

        // byte_offset
        if (option->byte_offset)
            byte_offset_cnt += (len+1); // len + len('\n' previously eliminated)

        // line_number
        if (option->line_number)
            line_number_cnt++;
    }

    if (option->compare_time == -1 && option->count_succ)
        printf("%lld\n", success_cnt);
}

void walk_folder(Opt* option, const char* p, int* T, DIR* dir, const char* path) {
    struct dirent * ptr;
    while ((ptr=readdir(dir)) != NULL) {
        char * sub_path = (char*) malloc (sizeof(char) * 257);
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        sprintf(sub_path, "%s/%s", path, ptr->d_name);

        DIR* subdir = opendir(sub_path);
        if (subdir == NULL && errno == ENOTDIR) {   // It's file
            search_file_print(option, p, T, sub_path);
            continue;
        }
        else if (subdir == NULL) {
            printf("ERROR: unable to open %s !\n", sub_path);
            continue;
        }
        else if (option->recur) {
            walk_folder(option, p, T, subdir, sub_path);
        }

        closedir(subdir);

        free(sub_path);
    }

    free(ptr);
}

void print_help() {
    puts("-[option] pattern file/directory");
    puts("");
    puts("-i case insensitive");
    puts("-v inverse");
    puts("-n display line numbers");
    puts("-l display filenames only");
    puts("-h suppress filenames when multi-files are searched");
    puts("-w whole words");
    puts("-x whold lines");
    puts("-c count the number of matcheds in every file");
    puts("-m NUM stop reading after NUM matches");
    puts("-b display byte-offset");
    puts("-p display time comparing to strstr");
    puts("-R Recursively read directories");
    puts("");
}

bool get_option(Opt* option, int argc, char* argv[]) {
    char c;
    while((c=getopt(argc, argv, "ivnlhwxcm:bpA:B:R")) != -1) {
        switch (c) {
            case 'i':
                option->case_sensitive = false;
                break;

            case 'v':
                option->invert = true;
                break;

            case 'n':
                option->line_number = true;
                break;

            case 'l':
                option->filename_only = true;
                break;

            case 'h':
                option->suppress = true;
                break;

            case 'w':
                option->whole_word = true;
                break;

            case 'x':
                option->whole_line = true;
                break;

            case 'c':
                option->count_succ = true;
                break;
            case 'm':
                if (is_all_digit(optarg) == false) {
                    puts("-m should be followed by an integer");
                    return false;
                }
                option->stop_count = atoi(optarg);
                break;

            case 'b':
                option->byte_offset = true;
                break;

            case 'p':
                option->compare_time = 0;
                break;

            case 'A':
                if (is_all_digit(optarg) == false) {
                    puts("-A should be followed by an integer");
                    return false;
                }
                option->above = atoi(optarg);
                break;

            case 'B':
                if (is_all_digit(optarg) == false) {
                    puts("-B should be followed by an integer");
                    return false;
                }
                option->below = atoi(optarg);
                break;

            case 'R':
                option->recur = true;
                break;

            case '?':
            case ':':
            default:
                print_help();
                break;
        }
    }

    return true;
}

clock_t search(int argc, char* argv[], Opt* option, const char* pattern, int* T) {
    clock_t start = clock();
    // Distinguish file/folder
    for (int i=optind; i<argc; i++) {
        DIR* dir = opendir(argv[i]);

        if (dir == NULL && errno == ENOTDIR) {  // It's a path to a file
            search_file_print(option, pattern, T, argv[i]);
            continue;
        }
        else if (dir == NULL) {
            printf("ERROR: unable to open %s !\n", argv[i]);
            continue;
        }
        else {  // It's a path to a folder
            option->one_file_only = false;
            walk_folder(option, pattern, T, dir, argv[i]);

            closedir(dir);
        }
    }

    clock_t end = clock();
    return (end - start);
}


int main(int argc, char* argv[]) {
    if (argc <= 2) {
        print_help();
        return 0;
    }

    Opt* option = get_default_option();

    // Parse arguments
    if (get_option(option, argc, argv) == false) {
        free(option);
        return 0;
    }

    // Pre-process option

    if (option->filename_only) {
        option->count_succ = false;
        option->line_number = false;
        option->byte_offset = false;
    }
    if (option->count_succ) {
        option->line_number = false;
        option->byte_offset = false;
    }

    //    case insensitive
    const char* pattern;
    if (option->case_sensitive == false)
        pattern = to_upper_case(argv[optind]);
    else
        pattern = argv[optind];
    optind++;

    //    create table
    int *T = kmp_table(pattern);

    // Check whether is only one file/folder
    if (optind == argc-1)
        option->one_file_only = true;

    if (option->compare_time != -1) {
        // kmp
        clock_t time_kmp = search(argc, argv, option, pattern, T);
        // strstr
        option->compare_time = 1;
        clock_t time_strstr = search(argc, argv, option, pattern, T);

        printf("kmp time: %lf\n", (double) time_kmp / CLOCKS_PER_SEC);
        printf("strstr time: %lf\n", (double) time_strstr / CLOCKS_PER_SEC);
    }
    else {
        search(argc, argv, option, pattern, T);
    }

    // free option
    free(option);
    free(T);

    return 0;
}
