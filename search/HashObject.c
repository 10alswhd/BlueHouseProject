/*
 * HashObject.c
 *
 *  Created on: Apr 11, 2012
 *      Author: johnotander
 */


#include "HashObject.h"


//The HashObject that is pointed to by the Node in the chain. Holds key and value.
HashObjectPtr newHashObject(char *key, char *value)
{
  if(!key) return NULL;

	HashObjectPtr obj;
	if((obj = malloc(sizeof(HashObject))) == NULL)
		printf("Couldn't Allocate Memory.");
	if((obj->key = malloc(sizeof(char)*strlen(key)+1)) == NULL)
		printf("Couldn't Allocate Memory.");
	strcpy(obj->key, key);

	if(value)
	{
		obj->value = malloc(sizeof(char)*strlen(value)+1);
		strcpy(obj->value, value);
	}
	else
	{
		obj->value = NULL;
	}

	return obj;
}


void freeHashObject(HashObjectPtr obj)
{
	if(!obj) return;

	if(obj->value)
		free(obj->value);

	free(obj->key);
	free(obj);
}
