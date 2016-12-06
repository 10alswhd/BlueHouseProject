#include <assert.h>
#include <string.h>
#include <stdio.h>
 
void ehstrncpy_s(char *dest,size_t size, const char *source, size_t n)
{
    size_t i;
    assert(size >= n);//size는 n보다 크거나 같아야 함
    for (i = 0; i<n; i++)//i가 n보다 작으면 반복
    {
        dest[i] = source[i];
    }   
}
void main(void)
{
    char *src = "1234567890";
    char buffer[50] = "aaaaaaa";
 
    printf("== strncpy_s 사용 ==\n");
    strncpy_s(buffer, sizeof(buffer), src, 5);
    printf("buffer: %s \n", buffer );
    strncpy_s(buffer, sizeof(buffer), src + 2, 5);
    printf("buffer: %s \n", buffer);
 
    printf("== ehstrncpy_s 사용 ==\n");
    ehstrncpy_s(buffer, sizeof(buffer), src, 5);
    ehstrncpy_s(buffer, sizeof(buffer), src + 2, 5);
    printf("buffer: %s \n", buffer);
    printf("buffer: %s \n", buffer);
}
 
