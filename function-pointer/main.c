#include <stdio.h>
#include <stdlib.h>

typedef char* (**fpDef)(char*);//define a new type to make my fucntion pointers cleaner.

//protocols
char** stringCentral(fpDef functions, char* string);
char* char_double(char* str);
char* char_shift(char* str);
char* char_flip(char* str);

int main(void)
{
    char* string="Hello World";
    char** result;
    fpDef func=(fpDef)malloc(sizeof(void*)*4);//allocate enough room for 4 pointers
    *func++=&char_double;//three of
    *func++=&char_shift;//the pointers
    *func++=&char_flip;//are functions
    *func=NULL;//the last one points to NULL to terminate the array
    func-=3;//move back to the first function pointer
    result=stringCentral(func,string);//where the magic happens
    while(*result){
        printf("_%s_\n",*result++);
    }
    return 0;
}

char** stringCentral(fpDef functions,char* string){
    char **result;
    fpDef fncptr;
    fncptr=(fpDef)functions;
    int count=0;
    while(*fncptr){//count number of functions being passed
        fncptr++;
        count++;
    }
    result=(char**)malloc(sizeof(char**)*count);//allocate the number of strings our functions will return
    fncptr=functions;
    while(*fncptr){
        *result++=(*fncptr)(string);//execute the functions
        fncptr++;
    }
    *result=NULL;//end our string array
    result-=count;
    return result;
}

//the following functions are simple and reletively follow the same pattern
char* char_double(char* str){
    char *ptr1,*ptr2;
    int count=0;
    ptr1=str;
    while(*ptr1){//count number of characters
        count++;
        ptr1++;
    }
    ptr1=(char*)malloc(count*2);//allocate the amount needed
    ptr2=ptr1;
    while(*str){
        *ptr2++=*str;
        *ptr2++=*str++;//copy twice before iterating
    }
    *ptr2='\0';//end array of characters with NULL
    return ptr1;
}

char* char_shift(char* str){
    char *ptr1,*ptr2;
    int count=0;
    ptr1=str;
    while(*ptr1){
        count++;
        ptr1++;
    }
    ptr1=(char*)malloc(count*2);
    ptr2=ptr1;
    while(*str){
        *ptr2++=*str;
        *ptr2++=*str+1;
        str++;
    }
    *ptr2='\0';
    return ptr1;
}

char* char_flip(char* str){
    char *ptr1,*ptr2;
    int count=0;
    ptr1=str;
    while(*ptr1){
        count++;
        ptr1++;
    }
    ptr1=(char*)malloc(count);
    ptr2=ptr1;
    while(*str){
        *ptr2++=*str>90?*str-32:*str+32;//I love turnary operator
        str++;//the above turnary basically says:
              //if(*str>90)
              //    *ptr2++=*str-32;
              //else
              //    *ptr2++=*str+32;
    }
    *ptr2='\0';
    return ptr1;
}
