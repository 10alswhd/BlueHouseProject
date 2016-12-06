#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <windows.h>

// Structure used to store info regarding each plane.
typedef struct plane_info {
	char name[20];
	char flight_number[10];
	char org_airport[5];
	char dest_airport[5];
	int start_time;
	int end_time;
	struct plane_info *next;
}plane_info;

// Global vars to store user input, user search code, and number of planes to be entered
char line[100];
char user_code[5];
int number_of_planes;

// Create new project. Returns a pointer to the first node in the project.
plane_info * create_new_project();

// Add flights to a new project.
void add_2_project(plane_info *root);

// Delete all nodes for exiting program.
void clean_exit(plane_info *root);

// Project menu is used to search linked list, add nodes, and delete nodes
void project_menu(plane_info *root);

// Initial load screen asking to load a project or start a new project
void project_selection();

// Print all flight on the list.
void print_all_flights(plane_info *root);

// Search list by flight number
void search_by_flight_number(plane_info *root);

// Delete flight by flight number.
void delete_by_flight_number(plane_info *root);

// Find number of nodes
int find_height(plane_info *root);

// Load from text file
void load_from_text();

// Save project to a text file
void save_2_text(plane_info *root);

int main(void){
	
    project_selection();

}

// Create new project. Returns a pointer to the first node in the project. Empty node is root for holding project name.
plane_info * create_new_project(){

    // Create root and add name.
    plane_info *root = (plane_info *) malloc( sizeof(plane_info));
    root->next = NULL;
	
    // Get project name
    printf("What is the projects name?\n");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s", &root->name);
	
    return root;
}

// Add flights to a new project.
void add_2_project(plane_info *root){
	
    int count, n;
	
    // Move temp to last node
    plane_info *temp = root;
    while(temp->next != NULL){
	temp = temp->next;
    }
	
    while(1){
	// Ask number of flights to be added then store to n
	printf("How many flights will be added?\n");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%d", &n);
	
	// For loop used to store info for each entry
	if(n > 0 && n < 21){
            for(count = 1; count <= n; count++){
                printf("-----------------------------------\n");
                printf("flight %d\n", count);
		printf("Please enter the flight number:\n");
		fgets(line, sizeof(line), stdin);
		sscanf(line, "%s", &temp->flight_number);
	
		printf("Please enter the orgin airport code:\n");
		fgets(line, sizeof(line), stdin);
		sscanf(line, "%s", &temp->org_airport);
	
		printf("Please enter the destination airport code:\n");
		fgets(line, sizeof(line), stdin);
		sscanf(line, "%s", &temp->dest_airport);
	
		printf("Please enter the start time:\n");
		fgets(line, sizeof(line), stdin);
		sscanf(line, "%d", &temp->start_time);
	
		printf("Please enter the arrival time:\n");
		fgets(line, sizeof(line), stdin);
		sscanf(line, "%d", &temp->end_time);
				
		// Create new node and point temp at the empty node
		temp->next = (plane_info *) malloc( sizeof(plane_info));
		temp = temp->next;
		temp->next = NULL;
            }
            project_menu(root);
            break;
	}
	else{
            printf("Number must be between 1 and 20\n");
	}
    }
}

// Delete all nodes for exiting program.
void clean_exit(plane_info *root){
	
    // Create temp var to hold pointer of next to be freed
    plane_info *temp = root;
    int count = 0;
	
    // Move to next node, and free the initial node
    while(root->next != NULL){
	temp = root->next;
	free(root);
	root = temp;
	count++;
    }
    
    printf("-----------------------------------\n");
    printf("%d nodes were deleted", count);
    printf("\n-----------------------------------\n");
	
    // Free last node
    free(root);
	
}

// Project menu is used to search linked list, add nodes, and delete nodes
void project_menu(plane_info *root){
	
    char user_char;
	
    // Ask users to choice from 3 options. Search by flight number, add new flight, print all, or delete by flight number
    printf("-----------------------------------\n");
    printf("Project: %s has %d flights\nPlease enter the first letter of one of these options\n", root->name, find_height(root));
    printf("-----------------------------------\n");
    printf("F = SEARCH BY FLIGHT NUMBER\n");
    printf("A = ADD NEW FLIGHT(S)\n");
    printf("D = DELETE BY FLIGHT NUMBER\n");
    printf("P = PRINT ALL\n");
    printf("S = SAVE IN TEXT FILE\n");
    printf("W = SWITCH PROJECTS\n");
    printf("E = EXIT FROM PROGRAM\n");
	
	
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s", &user_char);
    
	
    if(user_char == 'E'){
        printf("-----------------------------------\n");
	printf("Good Bye\n");
	clean_exit(root);
    }
	
    else if(user_char == 'A'){
        printf("-----------------------------------\n");
	add_2_project(root);
    }
	
    else if(user_char == 'P'){
        printf("-----------------------------------\n");
	print_all_flights(root);
    }
	
    else if(user_char == 'F'){
        printf("-----------------------------------\n");
	search_by_flight_number(root);
    }
	
    else if(user_char == 'D'){
        printf("-----------------------------------\n");
        delete_by_flight_number(root);
    }
	
    else if(user_char == 'S'){
        printf("-----------------------------------\n");
	save_2_text(root);
    }
	
	else if(user_char == 'W'){
        printf("-----------------------------------\n");
	project_selection();
    }
	
    else{
        printf("-----------------------------------\n");
        project_menu(root);
    }
	
}

// Initial load screen asking to load a project or start a new project
void project_selection(){
    
    char user_char;
    
    // Title info
    printf("-----------------------------------\n");
    printf("---------Adams Flight Log----------\n");
    printf("-----------------------------------\n");
    
    // Ask users to choice from 3 options. Exit, Load project, or New project
    printf("Please enter the first letter of one of these 3 options:\n");
    printf("N = NEW PROJECT\n");
    printf("L = LOAD PROJECT\n");
    printf("E = EXIT PROGRAM\n");
	
    // Scan user input and store in user_char
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s", &user_char);
	
    if(user_char == 'E'){
	printf("Good Bye");
        printf("-----------------------------------\n");
    }
	
    else if(user_char == 'N'){
        printf("-----------------------------------\n");
	plane_info *temp = create_new_project();
	project_menu(temp);
    }
	
    else if(user_char == 'L'){
        printf("-----------------------------------\n");
	load_from_text();
    }
}

// Print all flight on the list.
void print_all_flights(plane_info *root){
	
    printf("flight number\t orgin\t dest\t depart\t arrives\n");
    printf("--------------------------------------------------\n");
	
    // Print all nodes nut the root
    plane_info *temp = root;
    while(temp->next != NULL){
	printf("\t%s \t %s \t %s \t %d \t %d\n", temp->flight_number, temp->org_airport, temp->dest_airport, temp->start_time, temp->end_time);
	printf("--------------------------------------------------\n");
	temp = temp->next;
    }
	
    // send back to project menu
    project_menu(root);
}

// Search list by flight number
void search_by_flight_number(plane_info *root){
	
    // Get and store user input
    char number[10];
    printf("Enter the flight number to search:\n");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s", &number);
	
    // Move thru list print any nodes that match flight number
    int print_count = 0;
    plane_info *temp = root;
    while(temp->next != NULL){
	if(strcmp(temp->flight_number, number) == 0){
            printf("flight number\t orgin\t dest\t depart\t arrives\n");
            printf("--------------------------------------------------\n");
            printf("\t%s \t %s \t %s \t %d \t %d\n", temp->flight_number, temp->org_airport, temp->dest_airport, temp->start_time, temp->end_time);
            printf("--------------------------------------------------\n");
            print_count++;
	}
	temp = temp->next;
    }
	
    // Handle number not found
    if(print_count == 0){
	printf("No flights with flight number %s", number);
    }
	
    // send back to project menu
    project_menu(root);
}

// Delete light by flight number.
void delete_by_flight_number(plane_info *root){
	
    plane_info *child = root->next, *parent = root;		/* Temp pointers to move and save parent*/
    char number[10];						/* Store flight number to be searched*/
	
    // Get and Store user input
    printf("Enter the flight number to Delete:\n");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s", &number);
	
    // If node is the root delete move root pointer to next node
    if(strcmp(parent->flight_number, number) == 0){
	char pname[20];
	sscanf(root->name, "%s", pname);
	root = root->next;
	sscanf(pname, "%s", &root->name);
	free(parent);
    }
    else{
	// Move thru list delete any nodes that match flight number except the root
	while(parent->next != NULL){
            if(strcmp(child->flight_number, number) == 0){
		parent->next = child->next;
		free(child);
		parent = parent->next;
            }
            else{
		parent = parent->next;
            }
            child = parent->next;
	}
    }
    // send back to project menu
    project_menu(root);
}

// Find number of nodes
int find_height(plane_info *root){
	
    int count = 0;
    while(root->next != NULL){
	count++;
	root = root->next;
    }
	
    return count;
}

// Save list to text file
void save_2_text(plane_info *root){
	
    // Get and store name for file
    char file_name[50];
    printf("Enter the file name(must be one word):\n");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s", &file_name);
	
    // Create String with full file name
    char file_type[5] = ".txt";
    strcat(file_name, file_type);
	
    // Open stream
    FILE *out;
    if((out =  fopen( file_name,"wt"))  == NULL){
        printf("Output File could not be opened: %s\n",strerror(errno));
	project_menu(root);
    }
    else{
        printf("Stream is open!!\n");
    }
	
	
    // Copy title and nodes to text doc
    plane_info *temp = root;
    fprintf(out, "%s", temp->name);
    while(temp->next != NULL){
	fprintf(out, "\n\t%s \t %s \t %s \t %d \t %d", temp->flight_number, temp->org_airport, temp->dest_airport, temp->start_time, temp->end_time);
	temp = temp->next;
    }
	
    // Close stream
    fclose(out);
    printf("Stream is closed!!\n");
	
    // Send back to project menu
    project_menu(root);
	
	
}

// Load from text file
void load_from_text(){
	
    // Get and store name for file
    char file_name[50];
    printf("Enter the file name(must be one word):\n");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s", &file_name);
	
    // Create String with full file name
    char file_type[5] = ".txt";
    strcat(file_name, file_type);
	
    // Open stream
    FILE *in;
    if((in =  fopen( file_name,"rt"))  == NULL){
        printf("Output File could not be opened: %s\n",strerror(errno));
	project_selection();
    }
    else{
        printf("Stream is open!!\n");
    }
	
    // Create first node and get name
    plane_info *root = (plane_info *) malloc( sizeof(plane_info));
    root->next = NULL;
    fscanf(in, "%s\n", &root->name);
	
    // Create new node
    fscanf(in, "\t%s \t %s \t %s \t %d \t %d", &root->flight_number, &root->org_airport, &root->dest_airport, &root->start_time, &root->end_time);
    plane_info *temp = (plane_info *) malloc( sizeof(plane_info));
    root->next = temp;
    temp->next = NULL;
	
    // Store all other nodes till EOF
    int c;
    while((c = getc(in)) != EOF){
	if(c == '\n'){
            fscanf(in,"\t%s \t %s \t %s \t %d \t %d", &temp->flight_number, &temp->org_airport, &temp->dest_airport, &temp->start_time, &temp->end_time);
            temp->next = (plane_info *) malloc( sizeof(plane_info));
            temp = temp->next;
            temp->next = NULL;
	}
    }

	
    // Close stream
    fclose(in);
    printf("Stream is closed!!\n");
	
    // Send back to project menu
    project_menu(root);
}
