#include <stdio.h>

// FILE INPUT INFO
#define N 2420 // Number of words
#define WORD_LEN 5 // Character count of a word

// INPUTS
#define VALIDATE_GRAPH_CREATION 1
#define SRC_WORD "prove" // Word to start searching
#define DEST_WORD "guess" // Word to find
#define FIND_SHORTEST 1
#define STEP_LIMIT 11 // *Needed if FIND_SHORTEST is 0, lower length limit takes lesser time
#define PRINT_PATHS 1 // 0 for better performance

// Globals
char maxDepth = 0;
char words[N][WORD_LEN + 1];
char graph[N][N];

// Checks if there is only one character difference between two strings
int compareStrings(char* x, char* y) {
	int i, counter = 0;
	
	for(i = 0; i < WORD_LEN; ++i)
		if(x[i] != y[i] && ++counter == 2) return 0;
		
	return counter == 1;
}

// Checks if graph is created right
void validateGraphCreation() {
	printf("Graph Creation Test:\n");
	printf("qwert : qwect -> %d\n", compareStrings("qwert", "qwect"));
	printf("qwert : fwect -> %d\n", compareStrings("qwert", "fwect"));
	printf("qwert : asdfg -> %d\n", compareStrings("qwert", "asdfg"));
	printf("qwert : qwert -> %d\n\n", compareStrings("qwert", "qwert"));
}

// Returns index of the given word in the words array
int indexOf(char* word) {
	int i;
	
	for(i = 0; i < N; ++i) if(strcmp(word, words[i]) == 0) return i;
	
	return -1;
}

// Prints the path, DUHH...
void printPath(int* path, int pathLen, int dest) {
	printf("Steps: %d,  ", pathLen);
	int i;
	
	for(i = 0; i < pathLen; ++i) printf("%s -> ", words[path[i]]);
	
	printf("%s\n", words[dest]);
}

// Expands to friend nodes, keeps searching paths recursively
void findPath(int src, int dest, int* path, int pathLen, int* visited, int* pathCount) {
	int i;
	
	for(i = 0; i < N; ++i) {
		if(graph[src][i] && !visited[i]) {
			if(i == dest) { // Did we arrive to destination?
				if(PRINT_PATHS) printPath(path, pathLen, dest);
				
				++(*pathCount);
			} else if(pathLen < maxDepth) { // Create a new path by copying the old one and adding the new node
				int* newPath = (int*)malloc((pathLen + 1) * sizeof(int));
				memcpy(newPath, path, pathLen * sizeof(int));
				newPath[pathLen] = i;
				int* visitedCpy = (int*)malloc(N * sizeof(int));
				memcpy(visitedCpy, visited, N * sizeof(int));
				visitedCpy[i] = 1;
				// Continue with the new path
				findPath(i, dest, newPath, pathLen + 1, visitedCpy, pathCount);
				free(newPath);
				free(visitedCpy);
			}
		}
	}
}

int main() {
	// Get the words
	FILE* fp = fopen("kelime.txt", "r");
	
	if(fp == NULL) {
		printf("Could not open the file kelime.txt to read!");
		exit(-1);
	}
	
	// Save the words to an array
	char* lineBuffer = (char*)calloc(WORD_LEN + 2, 1);
	int i = 0, j;
	
	while(fgets(lineBuffer, WORD_LEN + 2, fp)) {
		lineBuffer[WORD_LEN] = '\0';
		strcpy(words[i++], lineBuffer);
	}
	
	free(lineBuffer);
	fclose(fp);
	
	// Create the graph
	for(i = 0; i < N; ++i)
		for(j = 0; j < N; ++j)
			graph[i][j] = compareStrings(words[i], words[j]);
			
	if(VALIDATE_GRAPH_CREATION) validateGraphCreation();
	
	char* ws = SRC_WORD, *wd = DEST_WORD; // Source and Destination Words
	int pathCount = 0; // Possible paths from source to destination
	// Create a path array, we have only source so length is 1
	int* path = (int*)calloc(1, sizeof(int));
	path[0] = indexOf(ws); // Put the source word to the path as root
	
	if(path[0] == -1) {
		printf("The word %s does not exists in the input file.", ws);
		return -1;
	}
	
	int destination = indexOf(wd); // Set the destination word
	
	if(destination == -1) {
		printf("The word %s does not exists in the input file.", wd);
		return -1;
	}
	
	// We need to keep track of which words are visited already,
	// so we make an array and initialize it with zeros
	int* visited = (int*)calloc(N, sizeof(int));
	visited[path[0]] = 1; // Set the source word as visited
	// Start the search
	printf("From: %s, To: %s\n\n", ws, wd);
	
	if(FIND_SHORTEST) {
		printf("We will search for the shortest path possible.\n\n");
		
		// If we find any path with the current max depth, that is the shortest
		while(pathCount == 0) {
			++maxDepth; // Try to find a path with current max depth
			printf("Searching paths %d nodes long...\n", maxDepth + 1);
			findPath(path[0], destination, path, 1, visited, &pathCount);
			printf("\n");
		}
	} else { // Limit the max depth to some number and find all possible paths
		maxDepth = STEP_LIMIT; // Limit is necessary so process won't take forever
		printf("Finding all possible paths with maximum of %d steps.\n", maxDepth);
		findPath(path[0], destination, path, 1, visited, &pathCount);
	}
	
	free(path);
	free(visited);
	printf("\nPath count : %d\n", pathCount);
	return 0;
}
