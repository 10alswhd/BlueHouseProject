#include <stdio.h>
#include <stdlib.h>

struct student {
	char name[20];
	char subject[20];
	int marks;
	struct student *next;
};

typedef struct student Student;

int main() {
	Student *head = NULL, *temp, *curr;
	char subject[20];
	char choice = 'Y';

	while (choice == 'Y' || choice == 'y') {
		temp = (Student*) malloc(sizeof(Student));
		printf("\nEnter Student name : ");
		scanf("%s", temp->name);
		printf("Enter Subject name : ");
		scanf("%s", temp->subject);
		printf("Enter the marks in Subject %s : ", temp->subject);
		scanf("%d", &temp->marks);

		temp->next = NULL;
		// Adding to linked list
		if (head == NULL)
			head = temp;
		else
			curr->next = temp;

		curr = temp;

		printf("Do you want to add more students? (Y/N) : ");
		scanf(" %c", &choice);
		// A space before %c skips trailing whitepaces from previous input
	}

	choice = 'Y'; // For the loop ahead
	while (choice == 'Y' || choice == 'y') {
		printf("\nEnter the subject for which the topper has to be searched : ");
		scanf("%s", subject);

		curr = head;
		temp = NULL; // Assumed topper, currently none
		while (curr != NULL) {
			if (strcmp(subject, curr->subject) == 0) { // If the subject matched
				if (temp == NULL) // If there is no topper, set the student as topper
					temp = curr;
				else if (curr->marks > temp->marks)  // Else, see if current student
					temp = curr;		     // has more marks than topper

			}
			curr = curr->next;
		}

		if (temp == NULL) // If still no one is topper, then there was no such subject
			printf("\nSubject not found!\n");
		else {
			printf("\nTopper is :  %s \n", temp->name);
			printf("who got %d marks in %s\n", temp->marks, temp->subject);
		}

		printf("Do you want to search more toppers? (Y/N) : ");
		scanf(" %c", &choice);
	}

	return 0;
}
