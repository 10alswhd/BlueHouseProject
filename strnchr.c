#include <stdlib.h>
/*
Returns a pointer to the first occurrence of character in the C string str.
The terminating null-character is considered part of the C string. Therefore, 
it can also be located to retrieve a pointer to the end of a string.
@param str the string to be searched
@param len the number of characters to search
@param character the character to search for
@returns A pointer to the first occurrence of character in str.
If the value is not found, the function returns a null pointer.
*/
const char *strnchr(const char *str, size_t len, int character) {
    const char *end = str + len;
    char c = (char)character;
    do {
        if (*str == c) {
            return str;
        }
    } while (++str <= end);
    return NULL;
}
