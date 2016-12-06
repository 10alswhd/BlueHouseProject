/*
 * Author: Tad DeVries <tad@splunk.net>
 * Date: 2013/02/27
 * 
 * Language: C
 * 
 * Description: This program demonstrates a simple doubly linked list 
 * used to store names and phone numbers. There are methods to add, search,
 * edit, delete, and print records. This program ignores user input validation
 * since pointer and memory manipulation are the key goals.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Structure: account
 *
 * Description: This structure contains a template for records.
 * Each record holds a Name, Phone number, and pointer to the next
 * item in the list.
 *
 */
struct account {
	int accountNumber;
	char *accountName;
	char *accountPhone;
	struct account *prev;
	struct account *next;
};

/* Linked List pointers to head and current items */
struct account *head = NULL;
struct account *tail = NULL;

/*
 * Function: flushInput
 *
 * Description: The will clear everything from STDIN.
 *
 * NOT USED
 */
//void flushInput() {
//	int c;
//	
//	while(c != '\n' && c != EOF) {
//		c = getchar();
//	}
//}

/*
 * Function: printMenu
 *
 * Description: Prints a menu to the user and asks for letter
 * choices based on the menu.
 *
 * Return: A single Character from the user;
 */
char printMenu() {
	char input;

	printf("*** Menu ***\n");
	printf("A: Add Record\n");
	printf("P: Print Records\n");
	printf("F: Find Record\n");
	printf("E: Edit Record\n");
	printf("D: Delete Record\n");
	printf("Q: Quit\n");
	printf("\nEnter Choice: ");
	input = getchar(); //get character input
	getchar(); //flush the newline/carrage return

	return input;
}

/*
 * Function: getInput
 *
 * Description: Grabs an input string from the user and stores it
 * into a dynamically allocated memory location.
 *
 * Variables: char* - String to output to the user describing what to input
 *
 * Return: A pointer to the string location in memory
 */ 
char *getInput(char *outputString) {
	char *userInput = NULL;
	size_t inputBuffer = 0;
	int inputCount = 0;

	//allocate the userInput
	//userInput = (char *)malloc(inputBytes+1);
	//not needed with the getline function since it
	//automatically calls realloc to manage the memory

	printf("%s", outputString);
	inputCount = getline(&userInput, &inputBuffer, stdin);

	//remove the newline character from the string
	userInput[inputCount-1] = '\0';

	//return the user input
	return userInput;
}
	
/*
 * Function: insertRecord
 *
 * Descprition: Allocates a new record then stores the user input
 * for the record name and phone number. This new item is then added to
 * the end of the list.
 */ 
void insertRecord(){
	struct account *newAccount = NULL;

	//allocate memory for the new record
	newAccount = (struct account*)malloc(sizeof(struct account));

	//get input and store it into each record variable
	newAccount->accountName = getInput("Input Name: ");
	newAccount->accountPhone = getInput("Input Phone Number: ");
	newAccount->next = NULL;

	//set this item as the start of a new list or
	//add it to the end of an existing list
	if(head == NULL) {
		newAccount->accountNumber = 1;
		newAccount->prev = NULL;
		head = newAccount;
		tail = head;
	}
	else {
		newAccount->accountNumber = tail->accountNumber + 1;
		newAccount->prev = tail;
		tail->next = newAccount;
		tail = tail->next;
	}
}

/*
 * Function: printOneRecord
 *
 * Description: Prints the record associated with the pointer passed in
 */
void printOneRecord(struct account *currentPointer){
	printf("*** Record: %d ***\n", currentPointer->accountNumber);
	printf("Name: %s\n", currentPointer->accountName);
	printf("Phone: %s\n", currentPointer->accountPhone);
}

/*
 * Function: printRecords
 *
 * Description: Traverses the linked list and prints each records contents
 */
void printAllRecords() {
	struct account *listPointer = NULL;

	//if the head pointer is NULL then it's an empty list
	//else print each record in order
	if(head == NULL){
		printf("No Records found\n");
	}
	else {
		//set a temp pointer to traverse the list with
		listPointer = head;

		printf("\n");

		//move through the list printing each record until
		//we reach the end
		while(listPointer != NULL) {
			printOneRecord(listPointer);
			listPointer = listPointer->next;
		}

		printf("\n");
	}
}

/*
 * Function: searchRecords
 *
 * Description: Searchs the list comparing each records name entry
 * with a search string. When a match is found the pointer to that 
 * entry is returned.
 *
 * Return: pointer to the found list entry or NULL if nothing is found
 */
struct account *searchRecords(char* searchName){
	struct account *listPointer = NULL;
	int temp;

	//if head is null then the list is empty
	if(head == NULL) {
		printf("Records empty\n");
	}
	else {
		listPointer = head; //start at the beginning
		
		//loop through the list looking for a match
		//if a match is found return the pointer
		//if not print an error and return NULL
		while(listPointer != NULL) {
			if(strcmp(listPointer->accountName, searchName) == 0) {
				return listPointer;
			}
			else {
				listPointer = listPointer->next;
			}
		}
		printf("Record %s not found\n", searchName);
	}
	
	return NULL;
}

/*
 * Function: editOneRecord
 *
 * Description: Allows a single record to be changed. This functions is 
 * extremely simplfied and lacks any serious error correction. It is intended
 * as a proof of concept only.
 */
void editOneRecord(struct account *listPointer) {
	char menuInput = '\0';	
	char *newName = NULL;
	char *newPhone = NULL;
	
	//print out the current record information
	printf("Current Record Information\n");
	printOneRecord(listPointer);

	//loop to display menu and process options
	do {
		printf("*** Edit Menu ***\n");
		printf("N: Change Record Name\n");
		printf("P: Change Record Phone Number\n");
		printf("S: Save Changes\n");
		printf("Selection: ");
		menuInput = getchar();
		getchar();

		switch(menuInput) {
			case 'n':
			case 'N': //change get a new name
				printf("Changing Name...\n");
				newName = getInput("Enter New Name: ");	
				break;
			
			case 'p':
			case 'P': //get a new phone number
				printf("Changing Phone Number...\n");
				newPhone = getInput("Enter New Phone Number: ");
				break;

			case 's': //verify that new items have been stored
			case 'S': //and save them to the record
				printf("Saving Record...\n");
				if(newName != NULL) {
					listPointer->accountName = newName;
				}

				if(newPhone != NULL) {
					listPointer->accountPhone = newPhone;
				}
				break;

			default:
				printf("Invalid Input\n");
		}
	}
	while(menuInput != 's' && menuInput != 'S'); 
}

/*
 * Function: deleteOneRecord
 * 
 * Description: Delete record entry referenced by pointer.  
 */
void deleteOneRecord(struct account *listPointer) {

	if(head == tail) {
		//delete single item list
		head = NULL;
		tail = NULL;
	}
	else if(listPointer == head) {
		//delete head
		head = listPointer->next;		
		head->prev = NULL;
	} 
	else if(listPointer == tail) {
		//delete tail
		tail = listPointer->prev;
		tail->next = NULL;
	}
	else {
		//delete non head/tail record
		listPointer->next->prev = listPointer->prev;
		listPointer->prev->next = listPointer->next;
	}	

	//free the memory location
	free(listPointer);
}

/*
 * Function: cleanupList
 * 
 * Description: Moves through a linked list freeing all memory locations
 */
void cleanupList() {
	struct account *tempPointer = NULL;

	//loop through the list clearing each record
	while(head != NULL) {
		tempPointer = head;
		head = head->next;
		free(tempPointer);
	}
}
		

/*
 * Function: main
 * 
 * Description: Handles menu options and calls all worker function
 */
int main() {
	char menuInput = '\0';
	struct account *tempPointer = NULL;
	char *searchName;

	//loop through the program until the user selects Q
	do {
		//get the user input
		menuInput = printMenu();	

		//work on the user input
		switch(menuInput) {
			case 'a':
			case 'A': //add a record to the list
				printf("Adding User...\n");
				insertRecord();	
				break;	
	
			case 'p':
			case 'P': //print all records in the list
				printf("Printing Records...\n");	
				printAllRecords();
				break;	

			case 'f':
			case 'F': //search by name matching
				printf("Finding Record...\n");
				if(head == NULL) {
					printf("Empty List\n");
				}
				else {
					searchName = getInput("Search Name: ");
					tempPointer = searchRecords(searchName);
					
					//if the pointer is null, nothing was returned 
					//so don't try to print
					if(tempPointer != NULL) {
						printOneRecord(tempPointer);
						tempPointer = NULL;
					}
				}
				break;	

			case 'e':
			case 'E': //edit a record
				printf("Editing Record...\n");	
				if(head == NULL) {
					printf("Empty List\n");
				}
				else {
					searchName = getInput("Search Name: ");
					tempPointer = searchRecords(searchName);
					
					//if the pointer is null, nothing was returned 
					//so don't try to print
					if(tempPointer != NULL) {
						editOneRecord(tempPointer);
						printOneRecord(tempPointer);
						tempPointer = NULL;
					}
				}
				break;	

			case 'd':
			case 'D'://delete a record
				printf("Deleting Record...\n");	
				if(head == NULL) {
					printf("Empty List\n");
				}
				else {
					searchName = getInput("Delete Name: ");
					tempPointer = searchRecords(searchName);
					
					//if the pointer is null, nothing was returned 
					//so don't try to print
					if(tempPointer != NULL) {
						deleteOneRecord(tempPointer);
						tempPointer = NULL;
					}
				}
				break;	

			case 'q':
			case 'Q': //quit the program loop
				printf("Goodbye!\n");	
				cleanupList();
				break;	

			default:
			 	printf("ERROR: Invalid Menu Option\n");
				break;	
		}
	}
	while(menuInput != 'q' && menuInput != 'Q');

	return 0;
}
