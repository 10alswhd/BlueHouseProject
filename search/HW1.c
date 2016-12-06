/* Name:
 * Section:
 * Date:
 * Assignment: 
 * */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_NAME_LEN 25
#define START_DEPTH 0

/*
 * Basic Tree Node Structure
 * */
typedef struct TreeNode_ {
	char name[MAX_NAME_LEN];
	struct TreeNode_ *left;
	struct TreeNode_ *right;
}TreeNode;

/*
 * Basic Stack Structure
 * */
typedef struct StackNode_ {
	TreeNode *t;
	struct StackNode_ *next;
}StackNode;

/*
 * Binary Tree Prototypes
 * */
TreeNode* read_from_file(const char* file);
TreeNode* insert(TreeNode* node, const char *name);
TreeNode* create_node(const char *name);
int size(TreeNode* node);
void display_tree(TreeNode* node, int depth);
int search_name(TreeNode* node, const char *target);
int max_depth(TreeNode* node);
const char* first_name(TreeNode* node);
void mirror_tree(TreeNode* node);
TreeNode* trim_tree(TreeNode* node, const char* start_name, const char* end_name);
void destroy_tree(TreeNode* node);
int number_of_leaves(TreeNode* node);
int is_tree_balanced(TreeNode* node);
char** flatten_tree(TreeNode* node, int *len_strings);
/*
 * Stack Prototypes
 * */
void push_node(StackNode** top, TreeNode* t);
TreeNode* pop_node(StackNode** top);

int main (int argc, char *argv[]) {
	/*
	 * Check command line parameters
	 * */
	if (argc < 2) {
		printf("%s is missing parameters to run properly\n", argv[0]);
		return 1;
	}
	TreeNode* root = NULL;
	root = read_from_file(argv[1]);
	char buffer[MAX_NAME_LEN];
	printf("Would you like to search for a name? (yes or no): ");
	scanf("%s", buffer);
	getchar();
	
	/*
	 * Query the databse (binary tree)
	 * */

	while (strcmp(buffer,"yes") == 0) {
		printf("Name: ");
		scanf("%s", buffer);
		getchar();
		int result = search_name(root,buffer);
		if (result) {
			printf("\n%s is present in the database", buffer);
		}
		else {
			printf("\n%s is not present in the database", buffer);
		}
		
		printf("\nWould you like to search for a name? (yes or no): ");
		scanf("%s", buffer);
		getchar();
	}
	
	display_tree(root,START_DEPTH);
	/*
	 * Display information about the database
	 * */

	printf("The number of records in the database is %d", size(root));
	printf("\nThe max depth of the database is %d\n", max_depth(root));
	printf("The number of leaf records are %d\n", number_of_leaves(root));
	printf("Is the database balanced (%s)\n", is_tree_balanced(root) ? "yes" : "no");
	printf("The tree mirrored looks like this\n\n");
	/*
	 * Change or flip databse
	 * */

	mirror_tree(root);
	display_tree(root,START_DEPTH);
	mirror_tree(root);
	char buffer2[MAX_NAME_LEN];
	printf("\n\nEnter the lower bound name and upper bound name: ");
	scanf("%s %s", buffer,buffer2);
	printf("Trimming the database from %s to %s\n\n", buffer, buffer2);
	root = trim_tree(root,buffer,buffer2);
	display_tree(root,START_DEPTH);
	int size = 0;
	char** strings = flatten_tree(root,&size);
	int i = 0;
	printf("\nFlattened databse is:\n");

	/*
	 * Memory deallocations
	 * */
	for (i = 0; i < size; ++i) {
		printf("%s\n", strings[i]);
		free(strings[i]);
	}
	free(strings);
	destroy_tree(root);
	return 0;
}





TreeNode* read_from_file(const char* file) {
	/* HINT
	 *	TreeNode *t = NULL;
	 *  t = insert(t,buffer);
	 * loop check the return type on fscanf
	 *  insert(t,buffer);
	 */
}
TreeNode* insert(TreeNode* node, const char *name) {

}
TreeNode* create_node(const char *name) {

}
int size(TreeNode* node) {

}

int search_name(TreeNode* node, const char *target) {

}
int max_depth(TreeNode* node) {

}

void mirror_tree(TreeNode* node) {

}
TreeNode* trim_tree(TreeNode* node, const char* start_name, const char* end_name) {	

}
void destroy_tree(TreeNode* node) {

}
int number_of_leaves(TreeNode* node) {

}

int is_tree_balanced(TreeNode* node) {

}
char** flatten_tree(TreeNode* node, int *len_strings) {

}

void push_node(StackNode** top, TreeNode* t) {
}

TreeNode* pop_node(StackNode** top_ref) {

}

/*
 * Used only for padding in the display tree, makes it look pretty
 * */
void padding (char ch, int n){

    	int i;
    	for (i = 0; i < n; i++)
        	printf("%c%c%c%c", ch, ch ,ch, ch);

}

/*
 * A Beautiful way to display various sorts of trees, passing this from one generation of students
 * to the next.
 * */
void display_tree (TreeNode *root, int depth) {
	TreeNode *current = root;
	if (root == NULL) {
        	padding (' ', depth);
        	printf("-\n");
    	}
    else {
		display_tree(current->left, depth+1);
       	padding(' ', depth);
       	printf ( "%s\n", root->name);
       	display_tree(current->right, depth+1);
    }
}
