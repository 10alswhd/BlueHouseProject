/* Doubly Linked List
Functions: 
1) Create the list
2) Insert items in the list
3) Print the items in the list
3) Search for specific value in the list
4) Delete specific node based on the value
5) Free the memory used by the list
*/

#include <stdio.h>
#include <stdlib.h>

// defining the structure of the doubly linked list
typedef struct list{
	int num;
	struct list* prev;
	struct list* next;
}node;

// Defining Create function
node* create(int num){
	node* head = malloc(sizeof(node));
	head->num = num;
	head->prev = head->next = NULL;
	return head;
}

// Defining Insert function
/* Why passing pointer of the head pointer and is there any solution? 
Yes, there is that is declare head as global variable but declaring head as global variable limits me 
to create only one doubly linked list whereas with the method below,
I can create as many list as the computer memory permits me */
void insert(node** head,int num){ 
	node* temp = malloc(sizeof(node));
	temp->num = num;
	temp->next=*head;
	temp->next->prev = temp;
	temp->prev=NULL;
	*head=temp;
}

// Defining the print function
void print(node* head){
	node* traversal = head;
	while(traversal!=NULL){
		printf("%d->",traversal->num);
		traversal = traversal->next;
	}
}

// Defining search function
node* search(node* head, int num){
	node* traversal = head;
	while(traversal!=NULL){
		if(traversal->num == num)
			return traversal;
		else 
			traversal = traversal -> next;
	}
	return NULL;
}

// Defining Delete function
void delete(node** head, int num){ 
	// first check if the num is in the list
	node* num_ptr = search(*head,num);
	
	// if num is not in the list the return nothing
	if(num_ptr==NULL)
		return;
	else{
		// Checking if the num is in first position of the list
		if(num_ptr->prev == NULL){
			*head = num_ptr ->next;
			free(num_ptr);
		}
		// Checking if the num is in last position of the list
		else if(num_ptr->next == NULL){
			num_ptr ->prev ->next = NULL;
			free(num_ptr);
		}
		// Then obiviously the num is the middle and I don't give a damn checking if it is in the middle
		else{
			num_ptr->prev->next = num_ptr->next;
			num_ptr->next->prev = num_ptr->prev;
			free(num_ptr);
	}
	}
}

// free the memory used by the list
void free_list(node* head){
	while(head!=NULL){
		node* curr = head;
		head=head->next;
		free(curr);
	}
}

int main(){
	// Testing the fuctions !!!!!
	
	// Creating the list and storing the address in head 
	node* head = create(7); 
	
	// inserting data into head list
	insert(&head,8); 
	insert(&head,9); 
	
	// deleting data
	delete(&head,9); 
	
	// searching the value
	node* result = search(head, 7); 
	if(result !=NULL){
		printf("Found 7 at address %p",result);
	}
	else
		printf("Not Found!!!");
	printf("\n");
	
	// printing the list
	print(head); 	
	
	// freeing the memory used by the list
	free_list(head);
	
	// Ending the program
	return 0;
}
