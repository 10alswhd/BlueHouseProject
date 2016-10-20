#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct linked_list
{
    struct linked_list *next;
    void *data;
} linked_list;

typedef void *(*fp_list_create_data)(const void *input);
typedef void (*fp_list_free_data)(const void *data);
typedef void (*fp_list_print_data)(const void *data);

linked_list *list_reorder(linked_list *list);
linked_list *list_reverse(linked_list *list);
linked_list *list_reverse_recursively(linked_list *list);
linked_list *merge_sorted_lists_recursively(linked_list *list1, linked_list *list2);
linked_list *list_create_by_array(void *array[], const int size);
void list_free(linked_list *list, fp_list_free_data free_data);
void list_print(linked_list *list, fp_list_print_data print_data);
void print_int_data(const void *data);
void free_data(const void *data);

linked_list *list_reorder(linked_list *list)
{
    if (!list || !list->next)
        return list;

    linked_list *curr, *new_list;
    linked_list *slow = list, *fast = list;

    while (fast && fast->next) // && is necessary here!
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split in the middle.
    fast = slow->next;
    slow->next = NULL;
    slow = list;

    // Reverse the bigger list.
    fast = list_reverse(fast);

    linked_list *dummy = malloc(sizeof (*dummy));
    if (!dummy)
    {
        printf("Error: out of memory!\n");
        exit(1);
    }
    curr = dummy;

    // Merge the two lists, add a less one and a greater one separetely.
    while (slow || fast)
    {
        if (slow)
        {
            curr->next = slow;
            slow = slow->next;
            curr = curr->next;
        }
        if (fast)
        {
            curr->next = fast;
            fast = fast->next;
            curr = curr->next;
        }
    }

    new_list = dummy->next;
    free(dummy);
    return new_list;
}

linked_list * list_reverse(linked_list * list)
{
    if (!list || !list->next) // Don't forget null and one-node linked list!
        return list;

    linked_list *prev = NULL;
    linked_list *curr = list;
    linked_list *next = NULL;

    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

linked_list * list_reverse_recursively(linked_list * list)
{
    if (!list || !list->next)
        return list;

    linked_list *new_head = list_reverse_recursively(list->next); // To find the reversed head.
    list->next->next = list; // Reverse and link;
    list->next = NULL; // Cut the previous connection.
    return new_head; // Always returns the reversed head.
}

void print_int_data(const void *data)
{
    printf("%-3d ", *(const int *) data);
}

void free_data(const void *data)
{
    free((int *) data);
}

linked_list * list_create_by_array(void *array[], const int size)
{
    int i;
    linked_list * head, *current, *element;

    if (!array || size <= 0)
        return NULL;

    head = current = element = NULL;
    for (i = 0; i < size; i++)
    {
        element = malloc(sizeof (*element));
        if (!element)
            return head;
        element->data = array[i];
        element->next = NULL;
        if (i == 0)
        {
            head = element;
            current = element;
        }
        else
        {
            current->next = element;
            current = element;
        }
    }
    return head;
}

void list_free(linked_list *list, fp_list_free_data free_data)
{
    if (list)
    {
        linked_list *temp;
        while (list)
        {
            temp = list;
            list = list->next;
            if (free_data)
                free_data(temp->data);
            free(temp);
        }
    }
}

void list_print(linked_list *list, fp_list_print_data print_data)
{
    linked_list *cur = list;

    if (!print_data)
    {
        printf("Print data function is not set.\n");
        return;
    }
    if (cur)
    {
        while (cur)
        {
            print_int_data(cur->data);
            cur = cur->next;
        }
        printf("\n");
    }
    else
    {
        printf("The linked list is empty.\n");
    }
}

int main(void)
{
    int *elem;
    int **array;
    int i, m, num, len = 1;
    linked_list *list, **lists, *new_list;

    lists = malloc(len * sizeof (*lists));
    if (!lists)
        exit(1);

    for (m = 0; m < len; m++)
    {
        printf("Enter the number of nodes of the list: ");
        scanf("%d", &num);
        if (num < 0)
        {
            printf("Size of nodes should be >= 0. Retry!\n");
            exit(1);
        }

        array = malloc(num * sizeof (*array));
        if (!array)
            exit(1);

        printf("Enter the values of nodes the list(separated by spaces):");
        for (i = 0; i < num; i++)
        {
            elem = malloc(sizeof (*elem));
            if (!elem)
                exit(1);
            scanf("%d", elem);
            array[i] = elem;
        }
        list = list_create_by_array((void **) array, num);
        list_print(list, print_int_data);
        lists[m] = list;
        free(array);
    }

    //new_list = list_reverse(list);
    //new_list = list_reverse_recursively(list);
    new_list = list_reorder(list);

    if (new_list)
    {
        //printf("\nReversed list:\n");
        printf("\nReordered list:\n");
        list_print(new_list, print_int_data);
        list_free(new_list, free_data);
    }
    else
    {
        printf("The list is empty!\n");
    }

    free(lists);

    return 0;
}
