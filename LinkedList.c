#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next;
}*head;

void addtoHead(int el) {
	struct node *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = el;
	if(head == NULL) {
    head = temp;
		head->next = NULL;
  } else {
		temp->next = head;
		head = temp;
	}
}

void addtoTail(int el) {
	struct node *temp,*current;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = el;
	if(head == NULL) {
		head = temp;
		head->next	= NULL;
	} else {
		for(current = head;current->next != NULL; current = current->next);
			current->next = temp;
			temp->next = NULL;
  }
}

void printAll() {
	struct node *current;
	for(current = head; current != NULL; current = current->next)
		printf("%d ",current->data);
}

void printAllRecursive(struct node *current) {
	if(current != NULL) {
		printf("%d ",current->data);
		printAllRecursive(current->next);
	}
		return;
}

void printAllRecursiveReverse(struct node *current) {
	if(current != NULL) {
		printAllRecursiveReverse(current->next);
		printf("%d ",current->data);
	}
		return;
}

void reverseListRecursive(struct node *current) {
	struct node *temp;
	if(current->next == NULL) {
		head = current;
		return;
	}
	else {
		reverseListRecursive(current->next);
		temp = current->next;
		temp->next = current;
		current->next = NULL;
	}
}

void reverseList() {
	struct node *prev, *current, *next;
	prev = NULL;
	current = head;
  next = NULL;

	while(current != NULL) {
		next = current->next;
    current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}

int search(int el) {
	struct node *current;
	for(current = head; (current != NULL) && (current->data != el); current = current->next);
		return current != NULL;
}

int deleteFromHead() {
	int el = head->data;
	head = head->next;
	return el;
}

int deleteFromTail() {
	struct node *prev,*current;
	int el;
	if(head->next == NULL) {
		el = head->data;
		head = NULL;
		return el;
	}
	for(prev = head, current = head->next; current->next != NULL; prev = prev->next, current = current->next);
	el = current->data;
	prev->next = NULL;
	return el;
}

int delete(int el) {
	struct node *prev, *current;
	if(el == head->data) {
		head = head->next;
		return 1;
  } else {
		for(prev = head, current = head->next; (current !=NULL) && (current->data != el); prev = prev->next, current = current->next);
		if(current != NULL) {
			prev->next = current->next;
			return 1;
		}
  }
	return 0;
}

int size() {
	struct node *temp;
	int count = 0;
	temp = head;
	while(temp != NULL) {
		temp = temp->next;
		count++;
	}
	return count;
}

int main() {
	int choice, el;
	head=NULL;
	do {
		printf("\nList Operations\n");
  	printf("1.Add\n");
    printf("2.Print All\n");
    printf("3.Search\n");
    printf("4.Delete\n");
    printf("5.Size\n");
    printf("6.Reverse\n");
    printf("7.Exit\n");
    printf("Enter your choice : ");

		scanf("%d", &choice);
		switch(choice) {
			case 1:
				printf("\nEnter your choice : \n");
				printf("1.Add to head\n");
				printf("2.Add to tail\n");

				scanf("%d",&choice);
				switch(choice) {
					case 1:
						printf("\nEnter an element : ");
						scanf("%d", &el);
						addtoHead(el);
						break;
					case 2:
						printf("\nEnter an element : ");
						scanf("%d", &el);
						addtoTail(el);
						break;
					default:
						printf("Invalid argument");
				}
				break;
			case 2:
				if(head == NULL) {
					printf("List is Empty\n");
				}
				else {
					printf("\nEnter your choice : \n");
					printf("1.Print Iteratively\n");
					printf("2.Print Recursively\n");
					printf("2.Print Reverse Recursively\n");

					scanf("%d",&choice);
					printf("Elements of the list are : \n");
					switch(choice) {
						case 1:
							printAll();
							break;
						case 2:
							printAllRecursive(head);
							break;
						case 3:
							printAllRecursiveReverse(head);
							break;
						default:
							printf("Invalid argument");
					}
				}
				break;
			case 3:
				if(head == NULL) {
					printf("List is Empty\n");
				}
				else {
					printf("Enter the number to search : ");
					scanf("%d",&el);
					if(search(el))
						printf("Element is present\n");
					else
						printf("Not found in the list\n");					
				}
				break;
			case 4:
				if(head == NULL) {
					printf("List is Empty\n");
				}
        else {
					printf("\nEnter your choice : \n");
					printf("1.Delete from head\n");
					printf("2.Delete from tail\n");
					printf("3.Delete a particular element\n");
					scanf("%d",&choice);
					switch(choice) {
						case 1:
							el = deleteFromHead();
							printf("\nElement deleted is : %d", el);
							break;
						case 2:
							el = deleteFromTail();
							printf("\nElement deleted is : %d", el);
							break;
						case 3:
							printf("Enter the number to delete : ");
							scanf("%d", &el);
							if(delete(el))
								printf("Element deleted");
							else
								printf("Not found");
							break;
						default:
							printf("Invalid argument");
					}
				}
				break;
			case 5:
				printf("Size is : %d", size());
				break;
			case 6:
				if(head == NULL) {
					printf("List is Empty\n");
				}
        else {
					printf("\nEnter your choice : \n");
					printf("1.Reverse the list iteratively\n");
					printf("2.Reverse the list recursively\n");
					scanf("%d",&choice);
					switch(choice) {
						case 1:
							reverseList();
							printf("Elements of the list (serially after reversing are : \n");
							printAll();
							break;
						case 2:
					    reverseListRecursive(head);
				      printf("Elements of the list (serially after reversing are : \n");
							printAll();
							break;
						default:
							printf("Invalid argument");
					}
				}
				break;
			case 7:
				break;
			default:
				printf("Invalid option\n");
		}
	} while(choice != 7);
	return 0;
}
