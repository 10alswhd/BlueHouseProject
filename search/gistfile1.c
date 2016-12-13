#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_last_token(char ch, char *str) {
	while((*str != ch)&&(*str != '\0')) ++str;
	if(*str == '\0') return 1;
	while(*str == ch) ++str;
	if(*str == '\0') return 1;
	else return 0;
}

char* next_start_point(char *str) {
	++str;
	while(*str != ' ') ++str;
	return str;
}

char* split(char *src, char *dst, const char ch) {
	int len;
	int flag = 0;
	char *p;
	if(is_last_token(ch, src)) flag = 1;
	// Count token length
	for(p = src; (*p != ch)&&(*p != '\0'); ++p);
	// Get length
	len = p - src;
	printf("len:%d\n", len);
	// Set null char
	*p = '\0';
	// Search next start point if this is not last token
	if(!flag) p = next_start_point(p);
	// memory allocate
	if((dst = (char*)malloc(len+1)) == NULL) exit(1);
	// Copy the token
	memcpy(dst, src, len+1);
	printf("%s\n", dst);
	printf("next:%p\n", p);
	if(flag) return p;    // returns next start address
	else     return NULL;
}

int main(void) {
	char buf[512];
	char *temp;
	char *token, *next;
	gets(buf);
	temp = buf;
	while(1) {
		next = split(temp, token, ' '); // Split by space
		puts(token); 
		free(token);
		if(next == NULL) break;
		temp = next;
	}
	free(buf);
	return 0;
}
