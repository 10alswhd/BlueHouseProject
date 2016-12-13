#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MinScore 0
#define MaxScore 50

typedef int Score;
typedef struct node {Score data; struct node *next;} Node;
typedef Node *List;

/* Creates a new Node and inserts in at the beginning of a List. */
List insertScore(Score score, List tail)
{
    List head = (List) malloc(sizeof(Node));
    if (head != NULL) {
        head->data = score;
        head->next = tail;
    }
    return head;
}

/* Creates a List with a single element. */
List singletonList(Score score)
{
    return insertScore(score, NULL);
}

/* appendList(x, y) attaches y at the end of x */
List appendList(List x, List y) {
    if (x == NULL) {
        return y;
    } else {
        x->next = appendList(x->next, y);
        return x;
    }
}

/* Checkes whether a Score is valid. */
int isValidScore(Score score) {
    return ((score >= MinScore) && (score <= MaxScore));
}

/* Prints a human readable representation of a List. */
void printList(List l)
{
    printf("[");
    while (l != NULL) {
        printf("%d", l->data);
        if (l->next != NULL)
            printf(", ");
        l = l->next;
    }
    printf("]");
}

/* Counts the number of elements in a List. */
int ListSize(List l)
{
    int size = 0;
    while (l != NULL) {
        size++;
        l = l->next;
    }
    return size;
}

void output_histogram(List scores)
{
    List l;
    int histogram[MaxScore + 1];
    printf("5\tHistogram:\n\n");
    printf("\tScore   Frequency\n");
    printf("\t-----   ---------\n");
    {
        int i;
        for (i = 0; i <= MaxScore; i++)
            histogram[i] = 0;
    }
    for (l = scores; l != NULL; l = l->next)
        histogram[l->data]++;
    {
        int i, j;
        for (i = 0; i <= MaxScore; i++) {
            printf("\t%5d   ", i);
            for (j = 0; j < histogram[i]; j++)
                printf("#");
            printf("\n");
        }
    }
    printf("\n");
}

void output_stats(List scores)
{
    List l;
    Score total = 0, highest, lowest;
    int n = 0;

    for (l = scores; l != NULL; l = l->next) {
        if ((n && (l->data > highest)) || !n)
            highest = l->data;
        if ((n && (l->data < lowest)) || !n)
            lowest = l->data;
        total += l->data;
        n++;
    }
    printf("3\tAverage score: %.2f\n\n", n ? (((float) total) / n) : 0);
    printf("4.1\tLowest score: %d\n", n ? lowest : 0);
    printf("4.2\tHighest score: %d\n\n", n ? highest : 0);
}

int main()
{
    List scores = NULL;
    char command[1024], selection[1024];
    
    printf("Type \"h\" for help.\n");
    while (1) {
        printf("Command: ");
        fgets(command, 1024, stdin);
        if (sscanf(command, "%s", selection) == 1) {
            int i;
            
            for (i = 0; selection[i] != '\0'; i++) {
                selection[i] = tolower(selection[i]);
            }
            if (!strcmp(selection, "i") || !strcmp(selection, "insert")) {
                Score score;
                printf("Insert multiple scores. Leave blank and enter when done"
                    ".\n");
                while (1) {
                    int results;
                    
                    printf("Insert next score: ");
                    fgets(command, 1024, stdin);
                    results = sscanf(command, "%d", &score);
                    if (results == EOF)
                        break;
                    if (results) {
                        scores = appendList(scores, singletonList(score));
                        printf("Value %d inserted successfully.\n", score);
                        continue;
                    }
                    printf("Invalid value.\n");
                }
                continue;
            }
            if (!strcmp(selection, "d") || !strcmp(selection, "display")) {
                printf("Main linked-list: ");
                printList(scores);
                printf("\n");
                continue;
            }
            if (!strcmp(selection, "h") || !strcmp(selection, "help")) {
                printf(
                    "List of commands:\n"
                    "[i]nsert   insert value\n"
                    "[r]emove   delete value\n"
                    "[s]earch   search for a value\n"
                    "[d]isplay  display data\n"
                    "[p]rocess  process data\n"
                    "[h]elp     display this help text\n"
                    "[q]uit     terminate the program\n");
                continue;
            }
            if (!strcmp(selection, "r") || !strcmp(selection, "remove")) {
                List *p = &scores;
                int i = 0;
                int pos;
                printf("Enter position of value to remove: ");
                fgets(command, 1024, stdin);
                sscanf(command, "%d", &pos);
                while (1) {
                    if (*p == NULL) {
                        printf("There is no position %d.\n", pos);
                        break;
                    }
                    if (i == pos) {
                        Score score = (*p)->data;
                        List q = *p;
                        *p = (*p)->next;
                        free(q);
                        printf("Value %d at position %d removed successfully.\n"
                            "", score, pos);
                        break;
                    }
                    p = &((*p)->next);
                    i++;
                }
                continue;
            }
            if (!strcmp(selection, "s") || !strcmp(selection, "search")) {
                Score score;
                int i;
                List l;
                printf("Enter value to search: ");
                fgets(command, 1024, stdin);
                if (sscanf(command, "%d", &score)) {
                    l = scores;
                    i = 0;
                    while (1) {
                        if (l == NULL) {
                            printf("Value %d is not found.\n", score);
                            break;
                        }
                        if (l->data == score) {
                            printf("Value %d is located at position %d.\n",
                                score, i);
                            break;
                        }
                        l = l->next;
                        i++;
                    }
                } else {
                    printf("Error.");
                }
                continue;
                
            }
            if (!strcmp(selection, "p") || !strcmp(selection, "process")) {
                List invalid = NULL, *p = &scores;
                
                while (*p != NULL) {
                    if (!isValidScore((*p)->data)) {
                        List q = *p;
                        *p = (*p)->next;
                        q->next = NULL;
                        invalid = appendList(invalid, q);
                    } else {
                        p = &((*p)->next);
                    }
                }
                printf("1\tValid scores: ");
                printList(scores);
                printf("\n\n");
                printf("2\tInvalid scores: ");
                printList(invalid);
                printf("\n\n");
                output_stats(scores);
                output_histogram(scores);
                printf("6\tNumber of invalid scores (removed from main linked-l"
                    "ist): %d\n\n", ListSize(invalid));
                continue;
            }
            if (!strcmp(selection, "q") || !strcmp(selection, "quit")) {
                printf("Goodbye!\n");
                break;
            }
            if (!strcmp(command, "\n")) {
                continue;
            }
            printf("Invalid command (try \"h\").\n");
        }
    }
    return 0;
}
