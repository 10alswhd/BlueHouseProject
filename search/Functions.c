#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

/*
WARNING: Does not allocate the student array
*/
int init(student_t *array, size_t n)
{
	if (!array)
		return -1;

	int i; // size_t ???
	for (i = 0; i < n; ++i) {
		printf("Entering information for student number %d:\n", i);
		printf("First name (maximum 31 chars): ");
		scanf("%s", &array[i].fn);
		printf("Last name (maximum 31 chars): ");
		scanf("%s", &array[i].ln);
		printf("Year of birth: ");
		scanf("%d", &array[i].yob);
		printf("Has paid? (1 for yes, 0 for no): ");
		scanf("%d", &array[i].paid);
	}

	return 1;
}

int do_menu()
{
	int choice = -1;
	do {
		printf("[%d] Quit\n", MENU_QUIT);
		printf("[%d] Show all\n", MENU_SHOW_ALL);
		printf("[%d] Show unpaid\n", MENU_SHOW_UNPAID);
		printf("[%d] Search name\n", MENU_SEARCH);
		printf("[%d] Edit student\n", MENU_EDIT);
		printf("[%d] Save\n", MENU_SAVE);
		printf("[%d] Load\n", MENU_LOAD);
		printf("> ");
		scanf("%d", &choice);
	} while (choice < 0 || choice > 7);

	return choice;
}

void show_student(student_t s)
{
	printf("Student first name: %s\n", s.fn);
	printf("Student last name: %s\n", s.ln);
	printf("Student year of birth: %d\n", s.yob);
	printf("Has paid?: %s\n", s.paid ? "yes" : "no");
}

void show_details(student_t *array, size_t n)
{
	int i;
	printf("Listing student details\n\n");
	for (i = 0; i < n; ++i) {
		printf("Details for student number %d:\n", i);
		show_student(array[i]);
	}
}

void show_unpaid(student_t *array, size_t n)
{
	int i;
	printf("Listing unpaid student details\n\n");
	for (i = 0; i < n; ++i) {
		if (array[i].paid)
			continue;

		show_student(array[i]);
	}
}

void search(student_t *array, size_t n)
{
	int i, found = 0;
	char fn[STUDENT_NAME_MAX];
	char ln[STUDENT_NAME_MAX];
	printf("Enter student first name: ");
	scanf("%s", &fn);
	printf("Enter student last name: ");
	scanf("%s", &ln);

	for (i = 0; i < n; ++i) {
		if (!strcmp(array[i].fn, fn) && !strcmp(array[i].ln, ln)) {
			show_student(array[i]);
			found = 1;
		}
	}

	if (!found)
		printf("Could not find student \"%s %s\"\n", fn, ln);
}

void edit(student_t *array, size_t n)
{
	int i, found = 0, id;
	char fn[STUDENT_NAME_MAX];
	char ln[STUDENT_NAME_MAX];
	printf("Enter student first name: ");
	scanf("%s", &fn);
	printf("Enter student last name: ");
	scanf("%s", &ln);

	for (i = 0; i < n; ++i) {
		if (!strcmp(array[i].fn, fn) && !strcmp(array[i].ln, ln)) {
			found = 1;
			id = i;
			break;
		}
	}

	if (!found) {
		printf("Could not find student \"%s %s\"\n", fn, ln);
		return;
	}

	show_student(array[id]);
	printf("First name (maximum 31 chars): ");
	scanf("%s", &array[id].fn);
	printf("Last name (maximum 31 chars): ");
	scanf("%s", &array[id].ln);
	printf("Year of birth: ");
	scanf("%d", &array[id].yob);
	printf("Has paid? (1 for yes, 0 for no): ");
	scanf("%d", &array[id].paid);
}

void save(student_t *array, size_t n)
{
	char filename[FILENAME_MAX]; /* Filename max is standard apparently */
	printf("Saving students to file.\n");
	printf("Enter file name: ");
	scanf("%s", &filename);

	FILE *out = fopen(filename, "wb");

	if (!out) {
		fprintf(stderr, "ERROR: Could not open file \"%s\" for saving\n", filename);
		return;
	}

	fwrite(&n, sizeof(int), 1, out); /* Number of students */

	fwrite(array, sizeof(student_t), n, out);

	fclose(out);
}

void load(student_t *array, size_t n)
{
	int new_n;
	char filename[FILENAME_MAX]; /* Filename max is standard apparently */
	printf("Loading students from file.\n");
	printf("Enter file name: ");
	scanf("%s", &filename);

	FILE *in = fopen(filename, "rb");

	if (!in) {
		fprintf(stderr, "ERROR: Could not open file \"%s\" for loading\n", filename);
		return;
	}

	fread(&new_n, sizeof(int), 1, in);

	if (n < new_n) {
		printf("WARNING: Only loading %d students of %d from file, array not large enough!\n", n, new_n);
	}

	fread(array, sizeof(student_t), n, in);
}


void process_choice(int choice, student_t *array, size_t n)
{
	switch (choice){
	case MENU_QUIT:
		exit(0);
		break;

	case MENU_SHOW_ALL:
		show_details(array, n);
		break;

	case MENU_SHOW_UNPAID:
		show_unpaid(array, n);
		break;

	case MENU_SEARCH:
		search(array, n);
		break;

	case MENU_EDIT:
		edit(array, n);
		break;

	case MENU_SAVE:
		save(array, n);
		break;

	case MENU_LOAD:
		load(array, n);
		break;

	default:
		break;
	}
}
Raw
 Functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define STUDENT_NAME_MAX 32 

enum MENU_OPTION
{
	MENU_QUIT = 1,
	MENU_SHOW_ALL = 2,
	MENU_SHOW_UNPAID = 3,
	MENU_SEARCH = 4,
	MENU_EDIT = 5,
	MENU_SAVE = 6,
	MENU_LOAD = 7
};

typedef struct student
{
	char fn[STUDENT_NAME_MAX];
	char ln[STUDENT_NAME_MAX];
	int yob;
	int paid;
} student_t;

int init(student_t *array, size_t n);

int do_menu();

void show_student(student_t s);

void show_details(student_t *array, size_t n);

void show_unpaid(student_t *array, size_t n);

void search(student_t *array, size_t n);

void edit(student_t *array, size_t n);

void save(student_t *array, size_t n);

void load(student_t *array, size_t n);

void process_choice(int choice, student_t *array, size_t n);

#endif
