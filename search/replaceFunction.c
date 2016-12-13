/*
* C function to replace a sub string with something in a string. Would suggest to use glib to avoid memory overwritting or use mallocs.
* You can use malloc() to assign memory to return string and get rid of the last argument but make sure to free it later.
* This function replaces multiple instances of the found substring. To replace single instance, see the comment in the function. 
* If you want to dig more into it, check this out: http://creativeandcritical.net/str-replace-c
*
* Date: 23/09/2015
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h> // Download from- https://developer.gnome.org/glib/

void replace_str(char *origString, char *stringToReplace, char *replaceWith, char *resultString);
short int find_str(char *string, char start, char stop, char *foundStr);
// GString functions using glib
void g_string_replace(GString *g_origString, char *stringToReplace, char *replaceWith, GString *g_output);
short int g_find_str(char *string, char start, char stop, GString *foundStr);

void main(){
    char result[200];
    char foundStr[100];
    
    replace_str("we need to (replace this) whole string.", "(replace this)", "print", result);
    printf("%s\n", result);
}

void replace_str(char *origString, char *stringToReplace, char *replaceWith, char *resultString){
    char *found;
    char *pointer;
    int length;
    char *origCopy;
    char *copyPointer;
    
    origCopy = malloc(strlen(origString) + 1);
    origCopy = strcpy(origCopy, origString);
    copyPointer = origCopy;
    
    if(replaceWith != NULL){
        pointer = origString;
        // replace 'if' with 'while' to use function to replace multiple instance
        if(found = (strstr(pointer, stringToReplace))){
            length = found - pointer;
            if (length > 0)
            {
            	replaceResultStr = strncpy(replaceResultStr, pointer, length) + length;
            }
            replaceResultStr = strcpy(replaceResultStr, replaceWith) + strlen(replaceWith);
            copyPointer += length + strlen(stringToReplace);
            strcpy(replaceResultStr, copyPointer);
        }
        else
        {
            strcpy(replaceResultStr, copyPointer);
        }
        //strcpy(replaceResultStr, pointer);
    }
    /*
    else{
        strcpy(replaceResultStr, origString);
    } */
    free(origCopy);    
}

/**
 * Function to find and retrieve a substring using
 * @param  string   string to search
 * @param  start    the substring start char
 * @param  stop     the substring end char
 * @param  foundStr pointer pointing to the copy of found substring
 * @return          1 if found else 0
 */
short int find_str(char *string, char start, char stop, char *foundStr)
{
    char *startP;
    char *stopP;
    
    if((startP = strchr(string, start)) && (stopP = strchr(startP, stop)))
    {
        strncpy(foundStr, startP, (stopP - startP) + 1);
        *(foundStr + ((stopP - startP) + 1)) = '\0';
        return 1;
    }
    else
        return 0;
}

/*
    If using the G library, then use this replace function. it's neat.
*/
void g_string_replace(GString *g_origString, char *stringToReplace, char *replaceWith, GString *g_output)
{
    char *found;
    char *copy;
    char * p;

    copy = malloc(g_origString->len + 1);
    copy = strcpy(copy, g_origString->str);
    p = copy;

    if (strlen(replaceWith) > 0)
    {
        if(found = (strstr(copy, stringToReplace)))
        {
            if((found-copy) > 0){
                g_string_overwrite_len(g_output, 0, copy, found-copy);
                g_string_truncate(g_output, found-copy);
                p += (found - copy);
            }
            else{
                g_string_assign(g_output, "");
                //g_string_truncate(g_output, 0);
            }
            g_string_append(g_output, replaceWith);
            g_string_append(g_output, p + strlen(stringToReplace));
        }
        else
        {
            g_string_assign(g_output, g_origString->str);
        }
    }
    else{
        g_string_assign(g_output, g_origString->str);
    }
    free(copy);
}

/**
 * Function to find and retrieve a substring between the given start and stop chars
 * @param  string   string to search
 * @param  start    the substring start char [not included in output]
 * @param  stop     the substring end char [not included in output]
 * @param  foundStr GString to be returned containing the found string
 * @return          1 if found else 0
 */
short int g_find_str(char *string, char start, char stop, GString *foundStr)
{
    char *startP;
    char *stopP;
    
    if((startP = strchr(string, start)) && (stopP = strchr(startP, stop)))
    {
        // +1 and -1 gets rid of the < > brackets
        g_string_overwrite_len(foundStr, 0, startP + 1, (stopP - startP - 1));
        return 1;
    }
    else
        return 0;
}
