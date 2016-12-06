#include <stdio.h>
#define MAXSIZE 4096

int num = 0;
int count = 0; 

int matches_leading(char *partial_line, char *pattern) {

  return 0;
}


int rgrep_matches(char *line, char *pattern) {

    if(*pattern == '\0'){
		count = 0;
		num = 0;
		return 1;
	}

	if(*line == '\n'){
		return rgrep_matches(++line, pattern);
	}
	
	if(*line == '\0'){
		count = 0;
		num = 0;
		return 0;
	}

	if(*pattern == '\\' && *(pattern+1) == '\\' && *(pattern+2) == '?'){
		num += 3;
		return rgrep_matches(line,pattern+=3);
	}

	if(*pattern == '\\' && *(pattern-1) != '\\'){
		++num;	
		return rgrep_matches(line, ++pattern);
	}

	if(*(pattern+1) == '+'){
		if(*pattern == *line || *pattern == '.'){
			if(*(line+1) != *pattern){
				num +=2;
				return rgrep_matches(++line,pattern+=2);
			}
			return rgrep_matches(++line,pattern);
		}		
	}

	if(*(pattern+1) == '?'){
		num += 2;
		if(*line == *pattern){
			return rgrep_matches(++line, pattern+=2);
		}
		else if(*line != *pattern){
			return rgrep_matches(line++,pattern+=2);
		}
	}

	if(*(pattern-1) == '\\'){
		if(*line == *pattern){
			++num;
			return rgrep_matches(++line, ++pattern);
		}
		else{
			count = num;
			num = 0;
			return rgrep_matches(++line, pattern-count);
		}
	}

	if(*pattern  == '.' || *line == *pattern){
		++num;
		return rgrep_matches(++line,++pattern);
	}	
	else{
		if(*line == *(pattern-1)){
			count = num;
			num = 0;
			return rgrep_matches(line,pattern-count);
		}
		
		count = num;
		num = 0;
		return rgrep_matches(++line, pattern-count);
	}	
	
	count = 0;
	num = 0;
	return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
