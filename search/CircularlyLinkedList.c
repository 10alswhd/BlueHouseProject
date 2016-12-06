#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int info;
} DATA;

typedef struct node {
    DATA data;
    struct node *next;
} NODE;

void insert(NODE *pointer, DATA data) {
    NODE *start = pointer;
    /*Iterate through the list till we encounter the last node.*/
    while (pointer->next != start) {
        pointer = pointer -> next;
    }
    /* Allocate memory for the new node and put data in it.*/
    pointer->next = (NODE *) malloc(sizeof (NODE));
    pointer = pointer->next;
    pointer->data = data;
    pointer->next = start;
}

int find(NODE *pointer, DATA key) {
    NODE *start = pointer;
    pointer = pointer -> next; //First node is dummy node.
    /*Iterate through the entire linked list and search for the key. */
    while (pointer != start) {
        if (pointer->data.info == key.info) { //key is found.
            return 1;
        }
        pointer = pointer -> next; //Search in the next node.
    }
    return 0; /*Key is not found */
}

void delete(NODE *pointer, DATA data) {
    NODE *temp;
    NODE *start = pointer;
    /*Go to the node for which the node next to it has to be deleted */
    while (pointer->next != start &&
            (pointer->next)->data.info != data.info) {
        pointer = pointer -> next;
    }
    if (pointer->next == start) {
        printf("Element %d is not present in the list\n", data.info);
        return;
    }
    /* Now pointer points to a node and the node next to it has to be removed */
    temp = pointer -> next;
    /*temp points to the node which has to be removed*/
    pointer->next = temp->next;
    /*We removed the node which is next to the pointer (which is also temp) */
    free(temp);
    /* Beacuse we deleted the node, we no longer require the memory used for it .  free() will deallocate the memory.*/
    return;
}

void print(NODE *start, NODE *pointer) {
    if (pointer == start) {
        return;
    }
    printf("\n%d ", pointer->data.info);
    print(start , pointer->next);
}

int main() {
    int i, status;
    DATA data;
    /* start always points to the first node of the linked list.
     * temp is used to point to the last node of the linked list.*/
    NODE *start, *temp;
    start = (NODE *) malloc(sizeof (NODE));
    temp = start;
    temp -> next = start;
    /* Here in this code, we take the first node as a dummy node.
     * The first node does not contain data, but it used because to avoid 
     * handling special cases in insert and delete functions.*/
  
    for (i = 0; i < 20; i++) {  //Add
        data.info = i;
        insert(start, data);
    }
    do {
        printf("What would you like to do ?\n");
        printf("\t1 - Delete a node\n");
        printf("\t2 - Print the list\n");
        printf("\t3 - Search in the list\n");
        printf("\t4 - Quit\n");
        scanf("%d", &i);
        switch (i) {
            case 1: // DELETE
                printf("\nEnter data to delete:\n");
                scanf("%d", &data.info);
                delete(start, data);
                break;
            case 2: //print
                printf("The list is ");
                print(start, start->next);
                printf("\n");
                break;
            case 3: //find
                printf("\nEnter data to find:\n");
                scanf("%d", &data.info);
                status = find(start, data);
                if (status) {
                    printf("Element Found\n");
                } else {
                    printf("Element Not Found\n");
                }
        }
    } while (i < 4);

    return EXIT_SUCCESS;
}
