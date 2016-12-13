#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_WORDS 10
#define NUM_CHAR 4 
#define true 1
#define false 0

typedef struct node_s{
        char value[NUM_CHAR];
        int wt;
        struct node_s *next;
}Node_S;

Node_S *graph_s[NUM_WORDS + 1];

Node_S * create_node_s(char *temp){

    Node_S * new_node = (Node_S *)malloc(sizeof(Node_S));
    if(new_node){
        strcpy(new_node->value, temp);
        new_node->next = NULL;
    }
    else{
        printf("\n Node cannot be allocated");
    }
    return new_node;
}
void add_edge_3(int i, char *str){

    Node_S * temp = graph_s[i];
    if(temp == NULL){
        graph_s[i] = create_node_s(str);
    }
    else{
        while(temp->next){
            temp = temp->next;
        }
        temp->next = create_node_s(str);
    }
}
/* Check if there is already exisitng bucket */
int search_buckets(char buckets[NUM_WORDS * NUM_CHAR][NUM_CHAR], int count, char *temp){
    int i;
    for(i=0; i<count; i++){
        if(!strcmp(buckets[i], temp))
            return i;
    }
    return -1;
}

/* This adds string to a bucket */
void  add_string(Node_S *pre_graph[], int index, char * str){

    Node_S * temp = pre_graph[index];

    if(!temp){
        pre_graph[index] = create_node_s(str);
    }
    else{
        while(temp->next){
            temp  = temp->next;
        }
        temp->next = create_node_s(str);
    }
}

/* This function finds the index of the word in dictionary
Inefficient, can be done using binary search as words are in sorted 
order in dictionary */

int find_index(char dict[NUM_WORDS][NUM_CHAR], char * temp){
    int i;
    for(i=0; i<NUM_WORDS; i++){
        if(!strcmp(dict[i], temp))
            return i;
        }
    return -1;
}

/* This function links all words in buckets to create edges of graph */

void create_graph(Node_S *pre_graph[NUM_WORDS * NUM_CHAR],
                        char dict[NUM_WORDS][NUM_CHAR], int count){
    int i;
    int index, index_1, index_2;
    for(i=0; i<count; i++){
        Node_S * current =  pre_graph[i];
        while(current){
            index  = find_index(dict, current->value);
                if(!graph_s[index]){
                    add_edge_3(index, current->value);
                }

                next = current->next;
                while(next){
                    index_1  = find_index(dict, next->value);
                    if(!graph_s[index_1])
                        add_edge_3(index_1, next->value);
                    add_edge_3(index_1, current->value);
                    add_edge_3(index, next->value);
                    next = next->next;
                }
                current = current->next;
        }
    }
}

/*This function creates buckets and using those buckets also
creates graph where all neighbour nodes differ by at most one
character */
void create_buckets(char buckets[NUM_WORDS * NUM_CHAR][NUM_CHAR],
                        char dict[NUM_WORDS][NUM_CHAR]){

    int i,j;
    int count = 0;
    Node_S * pre_graph[NUM_WORDS * NUM_CHAR];

    int key[NUM_WORDS * NUM_CHAR];

    for(i=0; i<NUM_WORDS * NUM_CHAR; i++){
        pre_graph[i] = NULL;
    }
    for(i=0; i<NUM_WORDS; i++){
        for(j = 0; j<NUM_CHAR-1; j++ ){
            char temp[NUM_CHAR];
            strcpy(temp, dict[i]);
            temp[j] = '_';

            int index = search_buckets(buckets, count, temp);
            if(index != -1){
                add_string(pre_graph, index, dict[i]);
            }
            else{
                strcpy(buckets[count], temp);
                add_string(pre_graph, count,dict[i]);
                count++;
            }
        }
    }
    create_graph(pre_graph, dict, count);
    // Adjancancy matrix based representation       
    for(i=0; i<NUM_WORDS; i++){
        printf("Nodes adjacent to %d : ", i);

        Node_S * current  = graph_s[i];
        while(current){
            printf("%s ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}


//Driver program
int main(){
    char buckets[NUM_WORDS * NUM_CHAR][NUM_CHAR];
    char dict[NUM_WORDS][NUM_CHAR] = {"CAT", "BAT", "COT", "COG", "COW", 
                                        "RAT", "BUT","CUT", "DOG", "WEB"};
    
    create_buckets(buckets, dict);

    bfs(graph_s[0]);
    return 0;
}
