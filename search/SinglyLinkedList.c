/* Singly Linked list
Funtions:
1) Create the list
2) Insert elements in the list
3) Find the specific elements from the list
4) Delete specific elements from the list
5) Free the list / Destroy all the list
*/

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef struct list{
	int num;
	struct list* next;
}node;

node* create(int number){
	node* head = malloc(sizeof(node));
	head->num = number;
	head->next = NULL;
	return head;
}

void insert(node** head,int number){
	// initializing our temp container
	node* temp = malloc(sizeof(node));
	temp->num = number;
	// pointing the temp to next of head
	temp->next = *head;
	// inserting temp after head
	*head = temp;
	return;
}

int find(node* head, int number){
	// defining a traversal node so that we don't break the link of head
	node* traversal =  head;
	while(traversal!=NULL){
		if(traversal->num == number){
			return true;
		}
		else
			traversal = traversal -> next;
		}
	return false;	
}

void print(node* head){
	node* traversal = head;
	while(traversal!=NULL){
		printf("%d->",traversal->num);
		traversal = traversal->next;
	} 
}

void delete(node** head,int number){
	// defining new pointer to head and previous 
	node* current = *head;
	node* previous = NULL; // since pointers before head is null
	// Iterating through the list
	while(current != NULL){
		if(current->num == number){
			if(previous== NULL){
				*head = current ->next;
			}
			else{
				previous->next = current->next;
				
			}
			// free the current node
			free(current);
			return;
		}
		else{
		previous = current;
		current = current->next;
		}
	}
	
}

void destroy(node* head){
	node * temp;
	while(head!=NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
}
int main(){
	// creating a list 
	node*head = create(6);
	//inserting some values
	insert(&head,7); // passing the address of the head pointer as head is a local variable. Make head global variable to pass just head pointer
	insert(&head,9);
	// printing the list
	print(head);
	// deleting a number
	delete(&head,9);
	// printing the list
	print(head);
	// freeing the list heap block
	destroy(head);
	return 0;
}
