/*
 * File:   adt_list.h
 * Author: EntropiaFox
 *
 * Created on 30 de diciembre de 2011, 01:30 PM
 * Released into the Public Domain.
 */

/* This is a simple ADT for singly linked Lists. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ADT_List_H
#define	ADT_List_H

typedef struct _List
{
    struct _List *next;
    void *var; // Defined as a pointer of null type, asking for trouble
} List;

List *listNewList()
{
    /* This functions returns a pointer to an initialized List */

    List *auxPtr = malloc(sizeof(List));
    auxPtr->var = NULL;
    auxPtr->next = NULL;
    return auxPtr;
}

List *listInsertBeginning(List *listToInsert, void *dataToInsert, int dataSize)
{
    /* This function inserts a new node at the beginning of a List, then
     * returns a pointer to that node. */

    List *auxPtr = malloc(sizeof(List));
    auxPtr->var = malloc(dataSize); //Allocate enough bytes of memory for the data to be inserted
    //printf("DEBUG: size of dataToInsert: %d \n", dataSize);
    memcpy(auxPtr->var, dataToInsert, sizeof(dataToInsert)); //Then copy it
    auxPtr->next = listToInsert;
    return auxPtr;
}

List *listInsertEnd(List *listToInsert, void *dataToInsert, int dataSize)
{
    /* This function goes through the List, finds its last node and realizes
     * the insertion there, then returns a pointer to the aforementioned node */

    List *auxPtr = listToInsert;
    while (auxPtr->next != NULL)
    {
        auxPtr = auxPtr->next;
    }
    List *auxPtr2 = malloc(sizeof(List));
    auxPtr2->var = malloc(dataSize);
    //printf("DEBUG: size of dataToInsert: %d \n", dataSize);
    memcpy(auxPtr2->var, dataToInsert, dataSize);
    auxPtr2->next = NULL;
    auxPtr->next = auxPtr2;
    return auxPtr2;
}

List *listSearch(List *listToSearch, void *dataToSearch, int dataSize)
{
    /* This function performs a linear search through a List, returning a
     * pointer to the relevant node, or a null pointer if the search was not
     * successful. */

    List *auxPtr = listToSearch;
    while (auxPtr->next != NULL)
    {
        if(memcmp(auxPtr->var, dataToSearch, dataSize) == 0)
        {
            return auxPtr;
        }
        auxPtr = auxPtr->next;
    }
    return NULL;
}

List *listDelete(List *listToDelete, void *dataToDelete, int dataSize)
{
    /* This function deletes an arbitrary member of a List, after performing
     * a search for the data it contains. Returns a pointer to the node
     * before or after the removal, or NULL if the last member was removed. */

    List *auxPtr = listToDelete;
    List *auxPtr2 = auxPtr->next;

    // Fringe case 1: First member of the List is the match

    if(memcmp(auxPtr->var, dataToDelete, dataSize) == 0)
    {
       // Fringe case 2: First member of the List is also the last
       if(auxPtr2 == NULL)
       {
           free(auxPtr);
           return NULL;
       }
       else // Else, proceed returning a pointer to the next member
       {
           List *delNode = auxPtr;
           auxPtr = auxPtr->next;
           free(delNode);
           return auxPtr;
       }
    }

    // Any other case, search for the member to be deleted

    while (auxPtr2->next != NULL)
    {
        if(memcmp(auxPtr2->var, dataToDelete, dataSize) == 0)
        {
            List *delNode = auxPtr2;
            auxPtr->next = auxPtr2->next;
            free(delNode);
            return auxPtr;
        }
        auxPtr = auxPtr2;
        auxPtr2 = auxPtr2->next;
    }
}

int listGetLength(List *listToCheck)
{
    /* This function returns the number of elements on a given list. */

    int elementCount = 0;
    List *auxPtr = listToCheck;
    while (auxPtr != NULL)
    {
        elementCount++;
        auxPtr = auxPtr->next;
    }
    return elementCount;
}

#endif	/* ADT_List_H */
