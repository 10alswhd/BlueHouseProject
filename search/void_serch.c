#include <stdio.h>
#include <stdlib.h>
#include <err.h>

void *cool_alloc(void *ptr, size_t size){
    void *tmp;

    if(ptr != NULL){
        if((tmp = realloc(ptr, size)) == NULL){
            free(ptr);
            err(1,"realloc() failed");
        }

        return tmp;
    }

    else if(ptr == NULL){
        if((ptr = malloc(size)) == NULL){
            err(1,"malloc() failed");
        }
        return ptr;
    }

    return NULL;
}

size_t void_search(const void *string, const void *search, size_t string_len, size_t search_len, size_t **output){
    size_t i, j, k, ret = 0;

    if(!string_len || !search_len)
        return 0;

    for(i=0;i<string_len;i++){
        for(j=i, k=0; j<string_len && k<search_len && *(char *)(string+j) == *(char *)(search+k); j++, k++ ){

            if(k == search_len-1){

                if(output){
                    *output = cool_alloc(*output, (ret+1)*(sizeof(size_t)) );
                    (*output)[ret] = i;
                }

                ret++;
            }
        }

    }

    return ret;
}

int main(void){
    int x[] = { 0x22, 0x6b636168 };
    char str[]="\x22\x00\x00\x00\x22\x00\x00\x00";
    size_t *output = NULL, found, i = 0;

    if( (found = void_search(str, &x[0], sizeof(str)-1, sizeof(int), &output)) ){
        printf("%zu matches found\n", found);

        while(i < found){
            printf("Match(%zu) -> %zu\n",i, output[i]);
            i++;
        }

        free(output);
        output = NULL;
    }

    puts("---------------------");
    printf("%zu Matches found\n", void_search("lolabcdeflolghijklol", "lol", 20, 3, NULL) );
    puts("---------------------");

    i = 0;
    found = void_search("dont learn to hack, hack to learn", &x[1], 33, sizeof(int), &output );
    printf("%zu matches found\n", found);

    while( i < found ){
        printf("Match(%zu) -> %zu\n",i, output[i]);
        i++;
    }

    free(output);

    return 0;

}
