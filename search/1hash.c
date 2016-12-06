// Luke Mitchell lm0466
// Principles of programming CW2
// Hash table/Linked list assignment
 
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
 
/* Helper functions not exposed in header file */
 
// creates an array of linked lists of specified size
// and initilises them all to NULL
// returns pointer to the array or NULL if insufficient memory
list** create_table (int size)
{
    int i;
    list** l;
 
    // allocate memory for the array
    l = calloc (size, sizeof(list));
     
    // initialise each list to NULL
    // assuming we were able to allocate enough memory
    if (l)
        for (i = 0; i < size; i++)
            l[i] = NULL;
     
    // return the list, or NULL, if OOM
    return l;
}
 
// resizes the table in h to specified size
// also rehashes the existing occupants and adds them to the new table
// returns 0 if successful, with h->table resized
// returns -1 if not, leaving h->table intact
int resize_table (hashtable* h, int size)
{
    int i, old_size;
    list** old_table;
    list** new_table;
    list* l;
 
    // copy pointer to old table
    old_table = h->table;
    old_size = h->size;
 
    // ask for enough memory for the new table
    new_table = calloc (size, sizeof (list));
 
    // was memory allocated?
    if (!new_table)
        return -1; // no, return failure
 
    // modify the pointer in the structure to point
    // to the new table
    h->table = new_table;
 
    h->size = size;
    h->in_use = 0;
 
    // add each existing element to the new table
    // and free the old memory
    for (i = 0; i < old_size; i++)
    {
        // does a list exist
        l = old_table[i];
 
        if (l)
        {
            list_reset (l);
 
            // add each item in the list
            do
            {
                hashtable_add_node (h, l->current->data, l->current->count);
            } while (list_advance (l) != -1);
 
            list_destroy (l);
        }
    }
 
    // free memory from old table
    free (old_table);
 
    // and return success
    return 0;
}
 
// this function contains an array of prime numbers to be used for size of table
// i'm aware that this isn't a truly dynamic approach however i feel that
// that implementing a 'proper' find next prime function may be beyond
// the scope of this assignment. another method would be to include
// a file with a list of prime numbers to use.
// returns a prime number of greater or lesser value than the specified 'current' value
// this is dependant upon the value of 'higher'
// when higher is 1, the function returns the next prime in the list
// when higher is not 1, the function returns the previous value
// returns the new value on success, or the old one on failure
int adjacent_prime (int current, int higher)
{
    int i;
 
        // the slightly sporadic nature of this list is due to desiring
        // a change of ~50% over the previous value for each element
        const int primes[21] = { 2, 3, 5, 7, 11, 19, 29, 37, 53, 79,
                                127, 211, 311, 457, 683, 1013, 1499,
                                2207, 3329, 4451, 6709};
 
        for (i = 0; i < 21; i++)
    {
                if (primes[i] == current)
        {
            if (higher == 1)            
                            return primes[++i];
            else
                return primes[--i];
        }
    }
 
    // another prime cannot be found, return previous
    return current;
}
 
// returns the next prime number in the list after 'previous'
// returns the same number, 'previous', if the end of the list is reached.
int next_prime (int previous)
{
        return adjacent_prime (previous, 1);
}
 
// returns the prime number in the list before 'previous'
// returns the same number, 'previous', if the start of the list is reached.
int previous_prime (int previous)
{
    return adjacent_prime (previous, 0);
}
   
 
// rotates an integer, h, by n bits
// this uses the 'barrel shift' method
unsigned int rotate_left (unsigned int h, int n)
{
        return ((h << n) ^ (h >> ((sizeof(unsigned int) * 8) - n)));
}
 
 
// takes a string, data, and hashes it to produce an integer key
// performs a 'rotated XOR hash'
// i.e. the ASCII value of each character is XOR'd with a rotated
// XOR of each of the previous characters.
// the value is then modulo'd with the table size (table_size)
// to ensure it does not exceed the maximum key value
int hash (int table_size, char* data)
{
    int i;
        unsigned int hash_value = 0;
 
        while ((i = *data++))
        {
        // rotate by 5 bits each time
                hash_value = rotate_left (hash_value, 5);
                 
        // XOR ASCII value
        hash_value ^= i;
        }
 
    // perform modulo operation
        return (hash_value % table_size);
}
 
/* Abstract Data Structure functions */
 
// adds a new node to the hashtable, h, with the data specified, data and count,
// returns the call to list_add_node (see list.c)
int hashtable_add_node (hashtable* h, char* data, int count)
{
    // does the table need resizing?
        float empty = (h->size - h->in_use);
 
        float utilised = (1 - (empty / h->size)) * 100; // note that empty is float to ensure fp divis
     
    if (utilised >= h->threshold)
        resize_table (h, next_prime (h->size));
 
    // compute the hash for the data
    int hash_value = hash (h->size, data);
 
    // does a list for this key exist?
    if (!h->table[hash_value])
    {
        // no, create one
        h->table[hash_value] = list_create ();
         
        // increment in-use counter
        h->in_use++;
    }
 
    return list_add_node (h->table[hash_value], data, count);    
}
 
// removes a node from the hashtable, h, where the node contains specified data
// returns 0 on success, -1 on failure (not found)
int hashtable_remove_node (hashtable* h, char* data)
{
    list* l;
 
    // does the table need resizing?
        float empty = (h->size - h->in_use);
 
        float utilised = (1 - (empty / h->size)) * 100; // note that empty is float to ensure fp divis
     
    // we use (100 - threshold)% as the lower bound 
    if (utilised <= (100 - h->threshold))
        resize_table (h, previous_prime (h->size));
 
    // compute the hash value
    int hash_value = hash (h->size, data);
     
    // find the node in the table
    node* n = hashtable_search (h, data);
 
    if (!n)
        return -1; // not found
     
    // remove the node from the list
    l = h->table[hash_value];
 
    list_remove_node (l, n);
 
    // check whether the list is empty
    if (l->size == 0)
    {
        // empty, free the memory
        free (l);
 
        // and decrement in-use counter
        h->in_use--;
    }
 
    // return success
    return 0;
}
 
// returns the number of comparisons taken to retrieve the
// specified data from the hashtable, h.
// returns 0 for 'not found'
int hashtable_get_comparisons (hashtable* h, char* data)
{
    // compute the hash value and get the list location
    int hash_value = hash (h->size, data);
        list* l = h->table[hash_value];
 
        // if the list is NULL, return so
        if (!l)
                return 0;
 
        // search the list for the data
        return list_get_comparisons (l, data);
}
 
// function to search the hashtable, h, for specified data
// returns the list node for the data specified
// returns NULL for 'not found'
node* hashtable_search (hashtable* h, char* data)
{
    // compute the hash value and get the list location
    int hash_value = hash (h->size, data);
        list* l = h->table[hash_value];
 
        // if the list is NULL, return so
        if (!l)
                return NULL;
 
        // return the value for list_search
        // this is the node if found, or NULL if not
        return list_search (l, data);
}
 
// create a new hashtable
// allocates memory for a table and initialises
// to an initial size, declared in hash.h
hashtable* hashtable_create (void)
{
    hashtable* h = malloc (sizeof (hashtable));
 
    // fill in the initial values for size and threshold fields
    h->size = HASHTABLE_INITIAL_SIZE;
 
    h->threshold = HASHTABLE_UTILISATION_THRESHOLD;
 
    // initialise the in-use counter to 0
    h->in_use = 0;
 
    // allocate some memory for the table
    h->table = create_table (h->size);
 
    // return pointer to the hashtable structure
    return h;
}
 
// destroys the specified hashtable and frees all memory used by it
void hashtable_destroy (hashtable* h)
{   
    // iterator
    int i;
     
    // destroy each list in the table, if it exists
    for (i = 0; i < h->size; i++)
    {
        if (h->table[i])
        {
            list_destroy (h->table[i]);
        }
    }
 
    // free memory from table
    free (h->table);
     
    // and free the memory from the structure itself
    free (h);
}
