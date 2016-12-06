#include <stdio.h>
#include <string.h>


int main()
{
	char *token;
	char *line = "trivial example";
	char *search = " ";
	token = strtok(line, search);
	return 0;
}
