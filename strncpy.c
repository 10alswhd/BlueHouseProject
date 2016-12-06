#pragma warning(disable:4996)
#include <string.h>
#include <stdio.h>
 
char *ehstrncpy(char *dest,  const char *source,size_t n)
{
    int i;
    for (i = 0; i<n; i++)//i가 n보다 작으면 반복
    {
        dest[i] = source[i];
    }
    return dest;
}
void main (void)
{
    char *src = "1234567890";   
    char buffer[50] = "aaaaaaa";
   
    printf("== strncpy 사용 ==\n");
    printf("buffer: %s \n",strncpy(buffer,src,5));
    printf("buffer: %s \n",strncpy(buffer,src+2,5));
 
    printf("== ehstrncpy 사용 ==\n");
    printf("buffer: %s \n", ehstrncpy(buffer, src, 5));
    printf("buffer: %s \n", ehstrncpy(buffer, src + 2, 5));
}
 
