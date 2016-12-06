#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct node_container {
	char element;
	int count;
	struct node_container * left;
	struct node_container * right; 
} node;


node * root = NULL;

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void insert(node ** leaf, char element, int count) {
	if ((*leaf) == NULL) {
		(*leaf) = (node *)malloc(sizeof(node));
		(*leaf)->element = element;
		(*leaf)->count = count;
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
	} else if (element < (*leaf)->element) {
		insert(&(*leaf)->left, element, count);
	} else if (element > (*leaf)->element) {
		insert(&(*leaf)->right, element, count);
	} else {
		(*leaf)->count += count;
	}
}

node ** search(node ** leaf, char element) {
	if(leaf != NULL) {
		if(element == (*leaf)->element) {
			return leaf;
		} else if(element < (*leaf)->element) {
			return search(&(*leaf)->left, element);
		} else {
			return search(&(*leaf)->right, element);
		}
	} else {
		return NULL;
	}
}

void remove_node(node ** leaf) {
	if((*leaf) != NULL) {
		remove_node(&(*leaf)->left);
		remove_node(&(*leaf)->right);
		free((*leaf));
	}
}


/*void remove_node_by_element(char element) {
	node ** finded = search(&root, element);
	if ((*finded) != NULL) {
		remove_node(finded);
		(*finded) = NULL;
		printf("SUCCESFULY DELETED.\n");
	} else {
		printf("NOT FOUND.\n");
	}
}*/

void print (node *tree, int level) {
	int i;

	if ( tree == NULL ) {
		for ( i = 0; i < level; ++i) {
			printf ("\t");
		}
		printf ("{\n");
		return;
	}

	print (tree->right, level + 1);

	for ( i = 0; i < level; ++i) {
		printf ("\t");
	}
	printf ("%c\n", tree->element);

	print (tree->left, level + 1);
}

void print_tree() {
	//lab8_view_tree(root, 80, 0, 0);
	print(root, 1);
}

void task (node * tree, int count, int * finded) {
	if ( tree == NULL ) {
		return;
	}
	if (tree->count == count) {
		printf("%c ", tree->element);
		++(*finded);
	}
	task (tree->right, count, finded);
	task (tree->left, count, finded);
}

void task_tree() {
	printf("Enter cnt: \n");
	int count, finded = 0;
	scanf("%d", &count);
	task(root, count, &finded);
	printf("\n");
	if (finded == 0) {
		printf("NOT FOUND.\n");
	}
}

void build_tree(const char * file_name) {
	FILE * stream = fopen(file_name, "rt");
	char line[256];
	if (fscanf(stream, " %[^\n]", line) == 1) {
		int i, limit = strlen(line);
		for (i = 0; i < limit; ++i) {
			insert(&root, line[i], 1);
		}
		fclose(stream);
	} else {
		printf("COULDN'T OPEN FILE WITH SPECIFIED ELEMENT.\n");
	}
}

void make_tree_default() {
	remove_node(&root);
	build_tree("default.db");
}

void backup_str(FILE * buffer, node * leaf) {
	if (leaf != NULL) {
		fprintf(buffer, "%c %d\n", leaf->element, leaf->count);
		backup_str(buffer, leaf->left);
		backup_str(buffer, leaf->right);
	}
}

void make_backup_file() {
	FILE * buf = fopen("backup.db", "wt");
	backup_str(buf, root);
	fclose(buf);
}

void restore_backup_file() {
	FILE * buf = fopen("backup.db", "rt");
	if (buf != NULL) {
		remove_node(&root);
		char element;
		int count;
		while (fscanf(buf, "%c %d\n", &element, &count) == 2) {
			insert(&root, element, count);
		}
		fclose(buf);		
	} else {
		printf("ERROR.\n");
	}
}

void terminate() {
	remove_node(&root);
	printf("Bye.\n");
	exit(0);
}


node ** minimum(node ** leaf) {
	if ((*leaf)->left == NULL) {
		return leaf;
	} else {
		return minimum(&(*leaf)->left);
	}
}


node ** maximum(node ** leaf) {
	if ((*leaf)->right == NULL) {
		return leaf;
	} else {
		return minimum(&(*leaf)->right);
	}
}






/*node ** search(node ** leaf, char element) {
	if(leaf != NULL) {
		if(element == (*leaf)->element) {
			return leaf;
		} else if(element < (*leaf)->element) {
			return search(&(*leaf)->left, element);
		} else {
			return search(&(*leaf)->right, element);
		}
	} else {
		return NULL;
	}
}*/

void remove_nodes(node ** leaf) {
	if ((*leaf)->right != NULL) {
		node ** change = minimum(&(*leaf)->right);
		(*leaf)->element = (*change)->element;
		(*leaf)->count = (*change)->count;
		remove_nodes(change);
	} else if ((*leaf)->left != NULL) {
		node ** change = maximum(&(*leaf)->left);
		(*leaf)->element = (*change)->element;
		(*leaf)->count = (*change)->count;
		remove_nodes(change);	
	} else {
		free((*leaf));
		(*leaf) = NULL;
	}
}

void remove_node_by_element(char element) {
	node ** finded = search(&root, element);
	if ((*finded) != NULL) {
		remove_nodes(finded);
	} else {
		printf("NOT FOUND.\n");
	}
}

void delete_tree() {
	printf("Enter element:\n");
	char element;
	scanf(" %c", &element);
	remove_node_by_element(element);
}

int main() {
	typedef struct {
		char description[50];
		void (*go)(void);
	} menu;
	menu elements[] = {
		{"Make tree", make_tree_default},
		{"Backup tree", make_backup_file},
		{"Restore tree", restore_backup_file},
		{"Print tree", print_tree},
		{"Delete", delete_tree},
		{"Task", task_tree},
		{"Exit", terminate}
	};
	int count = sizeof (elements) / sizeof (elements[0]), i;
	while (1) {
		system("cls");
		for (i = 0; i < count; ++i) {
			printf("%d: %s\n", i + 1, elements[i].description);
		}
		printf(">> ");
		int choose;
		scanf(" %d", &choose);
		system("cls");
		elements[choose - 1].go();
		system("pause");
		system("cls");
	}
	return 0;
}
