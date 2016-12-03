#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <math.h>
#include <limits.h>
#include <assert.h>

#include "buffer.h"

/*!
 * Circular Buffer Example (Keep one slot open)
 * Compile: gcc cbuf.c -o cbuf.exe
 */
 
/**< Init Circular Buffer */
Buffer* 
BufferInit(unsigned size)
{
    Buffer *self = (Buffer*) malloc(sizeof(Buffer));
    if (self)
    {
        self->size=size;
        self->head = 0;
        self->tail  = 0;
        self->keys = malloc(sizeof(TYPE) * size);
        if (!self->keys)
        {
            free(self);
            self = NULL;
        }
    }
    return self;
}

void 
BufferDestroy(Buffer *self)
{
    free(self->keys);
    free(self);
}
 
inline int 
BufferIsFull(Buffer* self)
{
    return (((self->head + 1) % self->size) == self->tail);
}
 
inline int 
BufferIsEmpty(Buffer* self)
{
    return (self->head == self->tail);
}

inline TYPE *
BufferFirst (Buffer *self)
{
    if (BufferIsEmpty(self)) return NULL;
    return &self->keys[self->tail];
}

inline TYPE *
BufferLast (Buffer *self)
{
    if (BufferIsEmpty(self)) return NULL;
    return &self->keys[self->head - 1];
}

inline void 
BufferEnque(Buffer* self, double k)
{
    if (BufferIsFull(self))
    {        
        BufferDeque(self, NULL);
    }
    self->keys[self->head] = k;
    self->head++;
    self->head %= self->size;
}

inline void 
BufferDeque(Buffer* self, TYPE *k)
{
    if (!BufferIsEmpty(self))
    {        
        if (k)
        {
            *k = self->keys[self->tail];
        }
        self->tail++;
        self->tail %= self->size;
    }
}

unsigned BufferSearch (Buffer *self, TYPE k)
{
    unsigned a, b;
    for (b = self->head;b != self->tail && self->keys[a] >= k;b = a)
    {
        a = b > 0 ? b - 1 : self->size - 1;
    }
    return b;
}

unsigned 
BufferFastSearch (Buffer *self, TYPE k)
{
    unsigned a = self->head, b = self->tail, l, c;
    if (k > self->keys[a]) return a;
    do
    {
        l = (self->size + a - b) % self->size;
        c = (b + (unsigned)floor(l / 2.0)) % self->size;

        if (k > self->keys[c])
        {
            b = c;
        }
        else
        {
            a = c;
        }
    } while (l > 1);
    return a;
}

int 
BufferInsert(Buffer *self, double k)
{
    if (BufferIsFull(self))
    {        
        BufferDeque(self, NULL);
    }
    unsigned a, b;
    
    for (b = self->head;b != self->tail && self->keys[b] != k;b = a)
    {
        a = b > 0 ? b - 1 : self->size - 1;
        if (self->keys[a] > k)
        {
            self->keys[b] = self->keys[a];
        }
        else
        {
            break;
        }
    }
    self->keys[b] = k;

    self->head++;
    self->head %= self->size;

    return self->head;
}

int
BufferFastInsert(Buffer *self, double k)
{
    unsigned a = self->head, b = self->tail, l, c, i;
    
    do
    {
        l = (self->size + a - b) % self->size;
        c = (b + (unsigned)ceil(l / 2.0)) % self->size;

        if (k > self->keys[c])
        {
            b = c;
        }
        else
        {
            a = c;
        }
    } while (l > 1);
    
    i = k < self->keys[b] ? b : a;
    
    TYPE temp;
    
    if (BufferIsFull(self))
    {        
        BufferDeque(self, NULL);
    }
    
    if (i == self->head)
    {
        BufferEnque(self, k);
    }
    else
    {
        while (i != self->head)
        {
            temp = self->keys[i];
            self->keys[i] = k;
            k = temp;
            i++;
            i %= self->size;
        }
        self->keys[i] = k;
        self->head++;
        self->head %= self->size;
    }

    return 0;
}

int BufferPrint(Buffer* self)
{
    unsigned i = self->tail;
    while (i != self->head)
    {
        printf("%3.3f\t", self->keys[i]);
        i++;
        i %= self->size;
    }
    printf("\n");
    return 0;
}

int BufferPrint2(Buffer* self)
{
    unsigned i = 0;
    for (i = 0;i < self->size;i++)
    {
        printf("%3u: ", i);
        if (i >= self->tail && (i < self->head || self->head <= self->tail))
        {
            printf("%3.3f\t", self->keys[i]); 
        }
        else if (i < self->tail && i < self->head)
        {
            printf("%3.3f\t", self->keys[i]); 
        }
        else if (i == self->head)
        {
            printf(" X    \t");
        }
        else
        {
            printf(" O    \t"); 
        }
    }
    printf("\n");
    return 0;
}

int BufferPrintReverse(Buffer* self)
{
    unsigned i = self->head;
    while (i != self->tail)
    {
        i = i > 0 ? i - 1 : self->size - 1;
        printf("%3.3f\t", self->keys[i]);
    }
    printf("\n");
    return 0;
}
