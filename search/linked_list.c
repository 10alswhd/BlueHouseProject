#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node;

void insert_node(node **head, int x){
    node *new_node = malloc(sizeof(node));
    new_node -> next = *head;
    new_node -> data = x;
    *head = new_node;
}


void print_list(node *head){
    //helper variable that will keep track of current node to iterate through the list
    node *cursor = head;
    int counter = 0;
    while(cursor != NULL){
        printf("Element %d: %d\n",++counter,cursor->data);
        cursor = cursor -> next;
    }
    printf("\n\n\n");
}

void reverse_list(node **head){
    node *prev = NULL;
    node *cursor = *head;
    node *next_node;

    while(cursor != NULL){
        next_node = cursor -> next; //the next node is the node next to current cursor
        cursor -> next = prev; //the reversal; the cursor's next is now it's previous node
        prev = cursor; // the current node is now the previous node (for the next iteration)
        cursor = next_node; //shift cursor to next node
    }
    *head = prev;
}

void reverse_list_recursive(node **head){
    //empty list
    if(*head == NULL)
        return;

    node *first_node = *head;
    //the rest of the list
    node *remaining_list = (*head) -> next;

    //for a list with a single node
    if(remaining_list == NULL)
        return;

    //reverse the the remaining list via a recursive call
    reverse_list_recursive(&remaining_list);
    //the reversal of links
    first_node -> next -> next = first_node;
    //due to the reversal, the original head node is now the tail node
    first_node -> next = NULL;
    //re-adjust the head pointer to the reversed list
    *head = remaining_list;
}

/**
*   Searches the linked list for a given element 
*   The pointer to the head is given 
*/
node *search_recursive(node *head, int x){
    //return null if the the node is null
    if(head == NULL)
        return NULL;
    //found it, return the pointer
    if(head->data == x)
        return head;
    //recursive call with the pointer to the next node
    return(search_recursive(head->next,x));
}

/**
*Gets the predecessor node of a particular node.
*Essential for removal of a node
**/
node *get_predecessor(node *head, int x){
    if(head == NULL || head -> next == NULL)
        return NULL;
    if(head->next->data == x)
        return head;
    return(get_predecessor(head->next,x));
}

void delete_node(node **head, int x){
    node *to_remove = search_recursive(*head,x);

    if(to_remove != NULL){
        node *predecessor = get_predecessor(*head,x);
        //if it is the head that is to be removed
        if(predecessor == NULL)
            *head = to_remove -> next;
        else
            predecessor -> next = to_remove -> next;

        free(to_remove);

        // to_remove -> data = to_remove ->next -> data;
        // node *temp = to_remove -> next;
        // free(to_remove -> next);
        // to_remove -> next = temp -> next;
    }
}

void print_middle(node *head){
    if(head == NULL){
        printf("EMPTY!");
    }
    else{
        node *cursor = head;
        node *middle = head;
        int counter = 0;

        while(cursor -> next != NULL){
            if(++counter %2 == 0)
                middle = middle -> next;
            cursor = cursor -> next;
        }

        printf("MIDDLE : %d\n", middle -> data);
    }
}

/* Function to swap nodes x and y in linked list by
   changing links */
void swap_nodes(node **head, int x, int y){
    //get the node which has x
    node *x_node = search_recursive(*head,x);

    //if x doesn't exist, return
    if(x_node == NULL)
        return;

    //get the node preceding x
    node *x_previous = get_predecessor(*head,x);

    //get the node which has y
    node *y_node = search_recursive(*head,y);

    //if y doesn't exist, return
    if(y_node == NULL)
        return;

    //get the node preceding x
    node *y_previous = get_predecessor(*head,y);

    //if x is not the head
    if(x_previous != NULL)
        x_previous -> next = y_node;
    //if x IS the head
    else
        *head = y_node;

    //if y is not the head
    if(y_previous != NULL)
        y_previous -> next = x_node;
    //if y IS the head
    else
        *head = x_node;

    //perform the swap
    node *temp = x_node -> next;
    x_node -> next = y_node -> next;
    y_node -> next = temp;

}

int main(){ 
    node *head = NULL;
    insert_node(&head,6);
    insert_node(&head,7);
    insert_node(&head,9);
    insert_node(&head,4);
    insert_node(&head,5);
    print_list(head);

    //swap_nodes(&head,5,7);
    //print_middle(head);

    reverse_list_recursive(&head);
    print_list(head);
}
