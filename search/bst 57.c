#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;
void hunter_input();
void BST();
Node *BST_insert(Node *head, int insert);
Node *first_head(int insert);
Node *min(Node *now);
Node *BST_delete(Node *now, int insert);
Node *BST_search(Node *now, int insert);
void BST_printf_inorder(Node *now);
void BST_printf_levelorder(Node *now);
bool queue_empty(int start, int end);
void queue_push(Node *queue[], int *end, Node *enqueue);
Node *queue_front(Node *queue[], int *start);

Node *BST_free(Node *head)
{
    if (head == NULL)
        return NULL;
    BST_free(head->left);
    BST_free(head->right);
    free(head);
    return NULL;
}
Node *BST_insert(Node *head, int insert)
{
    if (head == NULL) /*first*/
        return first_head(insert);
    if (insert < head->data)
        head->left = BST_insert(head->left, insert);
    else if (insert > head->data)
        head->right = BST_insert(head->right, insert);
    else if (insert == head->data) {
        printf("The number %d has already exist.\n", insert);
        return head;
    }
    return head;
}
Node *first_head(int insert)
{
    Node *new_data = (Node *)malloc(sizeof(Node));
    new_data->data = insert;
    new_data->left = NULL;
    new_data->right = NULL;
    return new_data;
}
Node *min(Node *now)
{
    if (now->left == NULL)
        return now;
    return min(now->left);
}
Node *BST_delete(Node *now, int insert)
{
    if (now == NULL) {
        printf("The numder %d doesn't exsit.\n", insert);
        return now;
    }
    if (insert < now->data) {
        now->left = BST_delete(now->left, insert);
    } else if (insert > now->data)
        now->right = BST_delete(now->right, insert);
    else {
        if (now->left == NULL) {
            Node *temp = now->right;
            free(now);
            return temp;
        }
        if (now->right == NULL) {
            Node *temp = now->left;
            free(now);
            return temp;
        }
        Node *temp = min(now->right);
        now->data = temp->data;
        now->right = BST_delete(now->right, temp->data);
    }
    return now;
}
Node *BST_search(Node *now, int insert)
{
    if (now == NULL)
        return NULL;
    else if (now->data == insert)
        return now;
    else {
        if (insert > now->data)
            return BST_search(now->right, insert);
        else
            return BST_search(now->left, insert);
    }
}
void BST_printf_inorder(Node *now)
{
    if (now == NULL)
        return;
    BST_printf_inorder(now->left);
    printf("%d ", now->data);
    BST_printf_inorder(now->right);
}
bool queue_empty(int start, int end)
{
    return start == end;
}
Node *queue_front(Node *queue[], int *start)
{
    return queue[(*start)++];
}
void queue_push(Node *queue[], int *end, Node *enqueue)
{
    queue[(*end)++] = enqueue;
}
void BST_printf_levelorder(Node *now)
{
    if (now == NULL)
        return;
    int max = 10000;
    Node *queue[max];
    int start = 0, end = 0;
    queue_push(queue, &end, now);
    while (queue_empty(start, end) == false) {
        Node *top = queue_front(queue, &start);
        printf("%d ", top->data);
        if (top->left != NULL)
            queue_push(queue, &end, top->left);
        if (top->right != NULL)
            queue_push(queue, &end, top->right);
    }
}
void BST()
{
    Node *head = NULL;

    while (1) {
        printf("(I)nsert a number\n");
        printf("(D)elete a number\n");
        printf("(S)earch a number\n");
        printf("(P)rint in infex&level order\n");
        printf("(R)eturn\n");
        char command2;
        getchar();
        scanf("%c", &command2);
        if (command2 == 'i' || command2 == 'I') {
            printf("Enter a number : ");
            int insert;
            scanf("%d", &insert);
            head = BST_insert(head, insert);
        } else if (command2 == 'd' || command2 == 'D') {
            printf("Enter a munber to delete : ");
            int insert;
            scanf("%d", &insert);
            head = BST_delete(head, insert);
        } else if (command2 == 's' || command2 == 'S') {
            printf("Enter a munber to search : ");
            int insert;
            scanf("%d", &insert);
            if (BST_search(head, insert) == NULL)
                printf("The number %d doesn't exist.\n", insert);
            else
                printf("The number %d exists.\n", insert);
        } else if (command2 == 'p' || command2 == 'P') {
            printf("The tree in infix order : ");
            BST_printf_inorder(head);
            printf("\n");
            printf("The tree in level order : ");
            BST_printf_levelorder(head);
            printf("\n");
        } else if (command2 == 'r' || command2 == 'R')
            return;
        else
            printf("wrong commmand.\n\n");
    }
}
bool eight(int val)
{
    while (val) {
        if (val % 10 == 8)
            return true;
        val /= 10;
    }
    return false;
}
Node *KT_BST_search(Node *now, int target, int way[], int i)
{
    if (now == NULL)
        return NULL;
    way[i++] = now->data;
    if (eight(now->data)) {
        if (now->left == NULL) {
            if (now->right != NULL)
                now = BST_delete(now, now->right->data);
        }
    }
    if (now->data == target)
        return now;
    else {
        if (target > now->data)
            return KT_BST_search(now->right, target, way, i);
        else
            return KT_BST_search(now->left, target, way, i);
    }
}
void treasure_hunter()
{
    printf("please input the name of map : ");
    char mapname[100];
    scanf("%s", mapname);
    FILE *fpr = fopen(mapname, "r");
    if (fpr == NULL) {
        printf("the name you input isn't exist.  please input again.\n\n");
        return;
    } else {
        printf("the name is exsit.\n\n");
    }

    Node *head = NULL;
    int insert;
    while (fscanf(fpr, "%d", &insert) != EOF)
        head = BST_insert(head, insert);
    fclose(fpr);

    printf("Please input the key location : ");
    int key;
    scanf("%d", &key);
    printf("Please input the treasure location : ");
    int treasure;
    scanf("%d", &treasure);
    int way_key[10000], way_treasure[10000], i;
    for (i = 0; i < 10000; i++) {
        way_key[i] = -1;
        way_treasure[i] = -1;
    }
    if (KT_BST_search(head, key, way_key, 0) == NULL) {
        printf("The key doesn't exsit.\n\n");
        return;
    }
    if (KT_BST_search(head, treasure, way_treasure, 0) == NULL) {
        printf("The treasure doesn't exsit.\n\n");
        return;
    }
    int count = 0;
    while (way_key[count] != -1)
        count++;
    int count_treasure = 0;
    i = 0;
    for (i = 0; way_treasure[i] != -1; i++)
        count_treasure++;
    int length = 0;
    for (i = 0; way_key[i] != -1 && way_treasure[i] != -1; i++) {
        if (way_key[i] == way_treasure[i])
            length++;
        else
            break;
    }
    if (length < count && length < count_treasure) {
        for (i = 0; i < count_treasure; i++)
            printf("%d->", way_key[i]);
        for (i = count - 2; i >= length - 1; i--)
            printf("%d->", way_key[i]);
        for (i = length; way_treasure[i] != -1; i++)
            printf("%d%s", way_key[i], way_treasure[i + 1] == -1 ? "\n" : "->");
    } else {
        if (count < count_treasure) {
            for (i = 0; i < count_treasure; i++)
                printf("%d%s", way_treasure[i], i == count_treasure - 1 ? "\n" : "->");
        } else if (count > count_treasure) {
            for (i = 0; i < count; i++)
                printf("%d->", way_key[i]);
            for (i = count - 2; i > length - 1; i--)
                printf("%d%s", way_key[i], i == length - 1 ? "\n" : "->");
        } else {
            for (i = 0; i < count; i++)
                printf("%d%s", way_key[i], i == count - 1 ? "\n" : "->");
        }
        printf("\n");
    }
    head = BST_free(head);
    return;
}

int main()
{
    while (1) {
        printf("(B)inery Search Tree.\n");
        printf("(T)reasure Hunter.\n");
        printf("(E)xit.\n");
        char command1;
        scanf("%c", &command1);
        if (command1 == 'b' || command1 == 'B') {
            BST();
        } else if (command1 == 't' || command1 == 'T') {
            treasure_hunter();
        } else if (command1 == 'e' || command1 == 'E')
            break;
        else
            printf("wrong commmand.\n");
        getchar();
    }
    return 0;
}
