#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

void ADD(char *, char *, char *);
void DELETE(char *, char *, char *);

struct contacts		//Structure for contacts in a phone book
{
	char name[20];
	char surname[30];
	char phone[12];
};

int i; //counter (global variable)
	
int main(void)
{
	FILE *f;
	f = fopen("Contacts.txt", "a");	//Creating a Contacts.txt file in case it doesn't exists
	fclose(f);
	struct contacts contact; 	//initializing a structure variable called "contact"
	memset(contact.name, 0, sizeof(contact.name));
	memset(contact.surname, 0, sizeof(contact.surname));
	memset(contact.phone, 0, sizeof(contact.phone));
	int choice;	
	printf("\n\nWelcome to the e-PhoneBook!\n\n");
	do
	{
		printf("Menu:\n\n1.Add contact\n2.Delete contact\n3.Show all contacts\n4.How many contacts?\n5.Exit\n\n");
		printf("Your choice[ENTER]:");
		scanf("%i", &choice);
		switch(choice)
		{
			case 1:
				printf("\nWelcome to a Contact Creator!\n\n");	

				printf("Name:");
				scanf( "%s",contact.name);	//Gather informations about the contact and place them in a structure
				printf("\n");

				printf("Surname:");
				scanf("%s",contact.surname);
				printf("\n");		
			
				printf("Phone Number:"); 
				scanf("%s",contact.phone);
				printf("\n");

				ADD(contact.name, contact.surname, contact.phone); //sending pointers to a variables to a function ADD
				break;
			case 2:
				printf("\nDeleting a contact\n\n");
				printf("Name:");
				scanf( "%s",contact.name);	//Gather informations about the contact and place them in a structure
				printf("\n");

				printf("Surname:");
				scanf("%s",contact.surname);
				printf("\n");	
			
				printf("Phone Number:"); 
				scanf("%s",contact.phone);
				printf("\n");

				DELETE(contact.name, contact.surname, contact.phone);
				break;
			case 3:
				printf("\nAll contatcs:\n\n");
				FILE *f;
				f = fopen("Contacts.txt", "r");
				char all[400];
				memset(all, 0, sizeof(all));
				char ch;
				for(i=0;(i<sizeof(all)-1) && ((ch = fgetc(f))!=EOF); i++)
					all[i] = ch;
				printf("%s\n\n", all);
				fclose(f);
				break;
			case 4:
				f = fopen("Contacts.txt", "r");
				char all1[400];
				char ch1;
				int c = 0;
				for(i=0;(i<sizeof(all1)-1) && ((ch1 = fgetc(f))!=EOF); i++)	//reading all characters
					if(ch1 == 42)						//if there is '*' 
						c++;						//increase the counter
				fclose(f);
				if(c>1)
					printf("\nThere are %d contacts\n\n", c);
				if(c==1)					
					printf("\nThere is 1 contact\n\n");
				if(c==0)
					printf("\nThere are no contacts\n\n");
				break;
			case 5:
				printf("\nGood Bye!\n\n");
				break;
			default:
				printf("Please choose the digit given in a menu...\n\n");
				continue;
		}
	}while(choice!=5);	
	return 0;
}
		
void ADD(char *name, char *surname, char *phone)
{
	FILE *f;				//pointer of a type FILE
	f = fopen("Contacts.txt", "r");		//initializing a pointer and opening a file Contacts.txt
	if(f==NULL)				//if it can't be opened print an ERORR
	{
		printf("Can't open a file 'Contacts.txt', please create it manualy if it doesn't exist\n\n");
	};
	char tab[3];
	memset(tab,0,sizeof(tab));
	fread(tab, sizeof(tab), 1, f); 		//read a string from a file to check if there is something inside
	if(tab[0]!=67)
	{
		fclose(f);
		f = fopen("Contacts.txt", "w");
		fprintf(f,"Contacts list:\n");
	};
	fclose(f);
	
	
	f = fopen("Contacts.txt", "a");			//reopenning the Contacts to have a oprtunity to append instead of rewrite
	fprintf(f,"\nContact:\nName: %s\nSurname: %s\nPhone Number: %s\n\n*\n", name, surname, phone); //printing a text to a file "Contacts.txt"
	printf("Contact has been added to a contacts list\n\nYou can check it in Contact.txt file\n\n");
	fclose(f);
}	

void DELETE(char *name, char *surname, char *phone)
{
	FILE *f;
	f = fopen("Contacts.txt", "r");
	char all[400];
	memset(all, 0, sizeof(all));
	char ch;
	for(i=0;(i<sizeof(all)-1) && ((ch = fgetc(f))!=EOF); i++)	//copying a contacts list to a string "all"
		all[i] = ch;
	char *pall = &all[0];			//making and initializing pointer to all
	char *pphone = phone;			//making and initializing pointer to struct.phone (here phone)
	char *search;				//making a pointer "search"
	search = strstr(pall, pphone);	//Giving that pointer a return value so a pointer where there is a first occurance of phone in a string all
	int d = 0;
	int counter = 0;
	for(i=0;i<sizeof(name);i++)
		if(name[i]!=0)			//counting all characters in a strin name
			counter++;
	
	d+= counter;
	counter = 0;
	for(i=0;i<sizeof(surname);i++)
		if(surname[i]!=0)		//counting all characters in a string surname
			counter++;	
	d+=counter;
	counter = 0;
	for(i=0;i<sizeof(phone);i++)
		if(phone[i]!=0)			//counting all characters in a string phone
			counter++;	
	d+=42;					//adding all remains characters to d
	memset(search-d, 32, d+counter+6);	//Clearing the area connected with that contact with spaces
	fclose(f);			
	f = fopen("Contacts.txt", "w");	
	fprintf(f, "%s", all);		//Rewriting a new contacts list to our file
	fclose(f);
	printf("Contact has been deleted\n\n");
	
}
