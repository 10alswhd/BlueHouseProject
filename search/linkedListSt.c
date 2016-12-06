#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "linkedListSt.h"

pLinkedList linkedlistInitDefault()
{
	pLinkedList list = (pLinkedList)malloc(sizeof(LinkedList));
	list->front = NULL;
	list->size = 0;
	return list;
}

int linkedlistGetSize(pLinkedList list)
{
	return list->size;
}

void linkedlistAddNodeBack(pLinkedList list, char* Username, char* Name)
{
	//Check if front is a single node in a list
	if(list->front == NULL)
	{
		list->front = (pMember)malloc(sizeof(Member));
		if(list->front != NULL)
		{	
			list->front->Username = Username;
			list->front->Name = Name;
			list->front->next = NULL;
			list->size++;
		}
	}
	else
    {
		//finds last member in linked list and creates a new member
		pMember current = list->front;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = (pMember) malloc(sizeof(Member));
		if(current->next != NULL)
		{
			current->next->Username = Username;
			current->next->Name = Name;
			current->next->next = NULL;
			list->size++;
		}
    }
}

void linkedlistDestroy(pLinkedList list)
{
	pMember current = list->front;//Creates current, a pointer to a Member node and assigns it to point to the front node in the list. 	pMember current = (*list)->front;
	pMember next = list->front;//Creates next, a pointer to a Member node and assigns it to point to the front node in the list 

	//checks if list is null
	if(list != NULL)
    {
		printf("list is not null\n");
		if(list->front == NULL)
		{
			list = NULL;
			free(list);
		}
		else
		{	
			printf("looping to delete all nodes\n");
			while(current != NULL)//While the node current points to is not Null
			{
				printf("I am deleting here\n");
				next = current->next;
				free(current);
				current = next; 	 
			}
			printf("setting the list to null\n");
			free(list);
			list = NULL;
		}    
    }
}

int UserMenu(pLinkedList list)
{
	int arraysize = 30;
	char c;
	int choice;
	int i = 0; //iterator
	//char buffer[1];
    int number_of_conversions = 0;
	char* Username[30]; //= (char*) malloc(arraysize * sizeof(char));
	char* Name[30];// = (char*) malloc(arraysize * sizeof(char));
	pMember Current_User = NULL;//Determines current user that is logged into system by searching through member list and comparing user input to each username

	for(i = 0; i < arraysize - 2; i++)
	{
		Username[i]= NULL;
		Name[i]= NULL;
	}
	choice = 0;

	printf("Welcome, please choose from one of the following options:\n");
		
		
	for(;;)
	{
		printf(":For User Login, press 1\n");
		printf(":For User Logout, press 2\n");
		printf(":For User Registration, press 3\n");
		printf(":To Search for a user, press 4\n");
		printf(":To Show all users, press 5\n");
		printf(":To exit, press 6\n");
		scanf("%d", &choice);
		switch(choice)
		{
			//User Login, changes current user
			case(1):
				if(Current_User != NULL)
				{
					printf("You are already logged in. If you are incorrectly logged in, please log out.\n");
					break;
				}
				printf("Login:\n");
				printf("Please enter your username:\n");
				i = 0;
				number_of_conversions = scanf(Username[i], "%c", &c);//try
				while(number_of_conversions == 1 && i < arraysize - 1 && !isspace(c))//check
					{
						i++;
						number_of_conversions = scanf(Username[i], "%c", &c);//do
					}
				Current_User = Search(list->front, *Username);//test
				if(Current_User == NULL)
				{
					break;
				}
				printf("Please enter your name:\n");
				while(number_of_conversions == 1 && i < arraysize - 1 && !isspace(c))
					{
						i++;
						number_of_conversions = scanf(Name[i], "%c", &c);
					}
				if(Current_User->Name != *Name)//Assigns output of read string function to Name, then compares Name to Name in current user
				{
					Current_User = NULL;
					printf("That username and/or name are incorrect.\n");
				}
				else
				{
					printf("Thank you, you are logged in now.\n");
				}
				break;
			//User Logout, changes current user
			case(2):
				printf("Logged out. Thank you!\n");
					Current_User = NULL;
				break;
			//User registration, creates a new Member node in linked list
			case(3):
				if(Current_User != NULL)
				{
					printf("You are already logged in. If you are incorrectly logged in, please log out to register.\n");
					break;
				}
				printf("Registration:\n");
				printf("Please enter the username less than 30 characters that you would like:\n");
				i = 0;
				number_of_conversions = scanf(Username[i], "%c", &c);//try, crash
				while(number_of_conversions == 1 && i < arraysize - 1 && !isspace(c))//check
					{
						i++;
						number_of_conversions = scanf(Username[i], "%c", &c);//do
					}
				/*
					The following if statement compares Username inputted to existing usernames and ***prevents duplicates.***
					Search(list->front, Username) returns a pMember which we then dereference to find the Username to compare.
				*/
				if(*Username == (Search(list->front, *Username)->Username))
				{
					Current_User = NULL;
					printf("That username is already taken, please try again.\n");

				}
				printf("Please enter your name, must be less than 30 characters:\n");
				i = 0;
				while(number_of_conversions == 1 && i < arraysize - 1 && !isspace(c))
					{
						i++;
						number_of_conversions = scanf(Name[i], "%c", &c);
					}
				linkedlistAddNodeBack(list, *Username, *Name);//test
				break;
			//Search for a user.
			case(4):
				printf("Please enter the username you would like to search for:\n");
				i = 0;
				number_of_conversions = scanf(Username[i], "%c", &c);//try, crash
				while(number_of_conversions == 1 && i < arraysize - 1 && !isspace(c))//check
					{
						i++;
						number_of_conversions = scanf(Username[i], "%c", &c);//do
					}
				/*
					The following if statement compares Username inputted to existing usernames and returns a match.
					Search(list->front, Username) returns a pMember which we then dereference to find the Username to compare.
				*/
				if(*Username == (Search(list->front, *Username)->Username))
				{
					printf("Found %s", Username);
				}
				else
				{
					printf("Could not find %s", Username);
				}
				break;
			//Administrative show all users, iterates through list
			case(5):
				printf("Showing all users:\n");
				Show_Users(list->front);
				break;
			//Exit option
			case(6):
				printf("Thank you! Exiting now.\n");
				exit(0);
			default:
				printf("Please choose one of the options listed.\n");	
		}
	}
}

void Show_Users(pLinkedList list)
{
	pMember current = list->front;

	while(current = list->front)//test
	{
		printf("%s\n", current->Username);
		printf("%s\n", current->Name);

		current = current->next;
	}
}

//Searches through member list and compares user input to each username. Returns a match as the current user.
pMember Search(pLinkedList list, char* Username)
{
    while (list->front != NULL)
    {
        if (list->front->Username == Username)//oops
        {
            return list->front;//If the username is found, we return it to allow the Login to set current user. 
        }
        list->front = list->front->next;
    }
	return NULL;
}

//skips over leading blanks and stops at EOF or whitespace or out of buffer space.
void clear_keyboard_buffer(void)
{
	char c;

	scanf("%c", &c);
	while(c != '\n')
	{
		scanf("%c", &c);
	}
	return;
}

//User wishes to continue 
int user_wishes_to_continue(void)
{
	char answer = 'y';
	
	printf("Do you wish to continue?(y/n): ");
	scanf(" %c", &answer);
	clear_keyboard_buffer();

	while(answer != 'y' && answer != 'n' &&
			answer != 'Y' && answer != 'N')
	{
		printf("I'm sorry, you may only type (y/n): ");
		scanf(" %c", &answer);
		clear_keyboard_buffer();
	}

	if(answer == 'y' || answer == 'Y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
