/* This implementation is a highly 
 * modified version taken from the book
 * Algorithm Design Manual - Skiena.
 */

#include <stdio.h> 
#include <stdlib.h> 
#include "list.h" 
 
void initList(list **l) 
{ 
        *l = (list *) malloc(sizeof(list)); 
        (*l)->item = -1; 
        (*l)->next = (*l); 
} 
 
int emptyList(list *l) 
{ 
        if(l->next == l) 
                return 1; 
        else 
                return 0; 
} 
 
void listInsert(list **l, int x) 
{ 
        list *p = (list *)malloc(sizeof(list)); 
 
        p->item = x; 
        p->next = *l; 
         
        *l = p; 
} 

list* searchListByItem(list *l, int x)
{
        if(emptyList(l))
                return NULL;

        if(l->item == x)
                return l;
        else
                return searchListByItem(l->next, x);
}

list* searchListByNode(list *l, list *node)
{
        if(emptyList(l))
                return NULL;

        if(l == node)
                return l;
        else
                return searchListByNode(l->next, node);
}

list* predecessorListByItem(list *l, int x)
{
        if((emptyList(l)) || (emptyList(l->next)))
        {
                return NULL;
        }

        if(l->next->item == x)
                return l;
        else
                return predecessorListByItem(l->next, x);
}

list* predecessorListByNode(list *l, list *node)
{
        if((emptyList(l)) || (emptyList(l->next)))
        {
                return NULL;
        }

        if(l->next == node)
                return l;
        else
                return predecessorListByNode(l->next, node);
}

/* Delete node using predecessor */
void listDeleteByNodePred(list **l, list *node)
{
        if(!searchListByNode(*l, node))
                return; /* Node not found */

        list *pred = predecessorListByNode(*l, node);

        if(pred != NULL)
        {
                pred->next = node->next;
                free(node);
        }
        else
        {
                /* Node exists but has no predecessor. 
                 * Hence, must be the first node.
                 */
                list *temp = *l;
                *l = (*l)->next;
                free(temp);
        }
}

/* Delete node using trick described in blog post */
void listDeleteByNode(list **l, list *node)
{
        if(emptyList(*l))
                return;

        list *n = node->next;

        /* Check if node is the last in the list */
        if(emptyList(n))
        {
                *l = n;
                free(node);
        }
        else
        {
                node->item = n->item;
                node->next = n->next;
                free(n);
        }
}

void listDeleteByItem(list **l, int x)
{
        list *p = searchListByItem(*l, x);

        if(p != NULL)
        {
                list *pred = predecessorListByItem(*l, x);

                if(pred != NULL)
                {
                        pred->next = p->next;
                        free(p);
                }
                else
                {
                        list *temp = *l;
                        *l = (*l)->next;
                        free(temp);
                }
        }
}

/* Recursive approach */
void reverseList(list **l)
{
        if(emptyList(*l))
                return;

        list *head = (list *) malloc(sizeof(list));
        head->item = -1; 
        head->next = head;

        revList(l, head, *l);
}

void revList(list **l, list *oldList, list *newList)
{
        if(emptyList(newList))
        {   
                *l = oldList;
                free(newList);
                return;
        }   

        list *temp = newList->next;

        newList->next = oldList;

        revList(l, newList, temp);
}

/* Iterative approach */
list* reverseList2(list *l)                                                                             
{       
        list *newHead = (list *) malloc(sizeof(list));                                                  
        newHead->item = -1;
        newHead->next = newHead;                                                                        
        
        while(!emptyList(l))                                                                            
        {       
                list *temp = l->next;                                                                   
                l->next = newHead;                                                                      
                newHead = l;                                                                            
                l = temp;                                                                               
        }                                                                                               
        
        free(l);                                                                                        
        
        return newHead;                                                                                 
}
