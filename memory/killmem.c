#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BLOCK 1024*1024*1024
int main()
{
    void * p1 = 0;
    void * p2 = 0;
    void * p3 = 0;
    void * p4 = 0;
    void * p5 = 0;
    void * p6 = 0;
    void * p7 = 0;
    void * p8 = 0;
    void * p9 = 0;
    void * p10 = 0;
    
    unsigned char f = 0;
    
    p1 = malloc(BLOCK);
    if(p1)
    {
        printf("1 gb assigned to p1\n");
        
        memset(p1, f, BLOCK);
    }
    
    p2 = malloc(BLOCK);
    if(p2)
    {
        printf("1 gb assigned to p2\n");
        
        memset(p2, f, BLOCK);
    }
    
    p3 = malloc(BLOCK);
    if(p3)
    {
        printf("1 gb assigned to p3\n");
        
        memset(p3, f, BLOCK);
    }
    
    p4 = malloc(BLOCK);
    if(p4)
    {
        printf("1 gb assigned to p4\n");
        
        memset(p4, f, BLOCK);
    }
    
    p5 = malloc(BLOCK);
    if(p5)
    {
        printf("1 gb assigned to p5\n");
        
        memset(p5, f, BLOCK);
    }
    
    p6 = malloc(BLOCK);
    if(p6)
    {
        printf("1 gb assigned to p6\n");
        
        memset(p6, f, BLOCK);
    }
    
    p7 = malloc(BLOCK);
    if(p7)
    {
        printf("1 gb assigned to p7\n");
        
        memset(p7, f, BLOCK);
    }
    
    p8 = malloc(BLOCK);
    if(p8)
    {
        printf("1 gb assigned to p8\n");
        
        memset(p8, f, BLOCK);
    }
    
    p9 = malloc(BLOCK);
    if(p9)
    {
        printf("1 gb assigned to p9\n");
        
        memset(p9, f, BLOCK);
    }
    
    p10 = malloc(BLOCK);
    if(p10)
    {
        printf("1 gb assigned to p10\n");
        
        memset(p10, f, BLOCK);
    }
}
