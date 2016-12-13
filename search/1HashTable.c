/*
 * HashTable.c
 *
 *  Created on: Apr 11, 2012
 *      Author: johnotander
 */


#include"HashTable.h"


HashTablePtr createTable(int size) {
  HashTablePtr table;
	if((table = malloc(sizeof(HashTable))) == NULL)
		printf("Couldn't Allocate Memory.");
	if((table->buckets = malloc(sizeof(ListPtr)*size)) == NULL)
		printf("Couldn't Allocate Memory.");

	int i;
	for (i = 0; i < size; i++) {
		table->buckets[i] = createList();
	}

	table->size = size;
	table->h = hashFunction;
	table->p = printTable;

	return table;
}

//Insert a HashObject to the table.
HashTablePtr insert(HashTablePtr table, HashObjectPtr obj) {
	if (!table)
		return NULL;
	if (!obj)
		return NULL;

	int mapping;
	mapping = table->h(table, obj->key);
	if(mapping < 0 || mapping > table->size) return NULL;

	table->buckets[mapping] = addAtFront((ListPtr)(table->buckets[mapping]), createNode(obj)); //Adds HashObjectPtr to the Node which is inserted.

	return table;
}


//Bernstein Hash
unsigned int hashFunction(HashTablePtr table, char *key) {
	if (!table)
		return -1;
	if (!key)
		return -1;

	unsigned int hash = 0;

	int c;
	while((c = *key++))
		hash = ((hash << 5) + hash) ^ c;

	return(hash % table->size);
}


NodePtr searchTable(HashTablePtr table, char *key) {
	if (!table)
		return NULL;
	if (!key)
		return NULL;

	int index;
	index = (table->h)(table, key);

	if (!table->buckets[index] || isEmpty((ListPtr)(table->buckets[index])))
		return 0; //No list in bucket.
	
	NodePtr found;
	if((found = search(table->buckets[index], key)))
	{
		return found;
	}
	else
	{
		return 0;
	}
}


int printTable(HashTablePtr table)
{
	if(!table) return 0;

	int i;
	for(i = 0; i < table->size-1; i++)
	{
		if(!isEmpty(table->buckets[i]))
		{
			printf("Bucket at index %d: ", i);
			printList(table->buckets[i]);
			printf("\n");
		}
	}

	return 1;
}


void freeTable(HashTablePtr table)
{
	int i;
	for(i = 0; i < table->size; i++)
	{
		freeList((ListPtr)table->buckets[i]);
	}

	free(table->buckets);
	free(table);
}
