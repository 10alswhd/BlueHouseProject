#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Count the occurences of one sting as a substring of a different string.
 * Every overlapping occurrance of the substring is counted.
 * The empty string is considered to match anything.
 *
 * @param char *haystack: The string to search through
 * @param char *needle: The substring to search for
 * @return: number of occurences. -1 if needle is longer than haystack.
 */
int count_substring(char *haystack, char *needle){

    // We pray these are proper C-strings
    int haystack_length = strlen(haystack);
    int needle_length = strlen(needle);

    if(needle_length > haystack_length){
        return 0;
    }

    // Return value
    int occurrences = 0;

    int j;
    for(j=0; j <= haystack_length - needle_length; ++j){
        if(!strncmp(haystack+j,needle, needle_length)){
            ++occurrences;
        }
    }

    return occurrences;

}

/**
 * Pretty-print a trial run of the substring function.
 *
 * @param char* haystack: The string to search through
 * @param char* needle: The substring to search for
 */
void test_substring(char* haystack, char* needle){
    int found = count_substring(haystack, needle);
    printf("%d occurrences of \"%s\" in \"%s\"\n", found, needle, haystack);
}

int main(){

    test_substring("tewrwabcfasabcgadfasdabcsfasfd", "abc");
    test_substring("tewrwabcfasabcgadfasdabcsfasfdabc", "abc");
    test_substring("abc", "abc");
    test_substring("abc", "abcd");
    test_substring("bbbb","bbb");
    test_substring("abc","");
    test_substring("","abc");
    test_substring("","");

    return 0;

}
