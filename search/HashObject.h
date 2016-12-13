/*
 * HashObject.h
 *
 *  Created on: Apr 11, 2012
 *      Author: johnotander
 */


#ifndef HASHOBJECT_H_
#define HASHOBJECT_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"


typedef struct hashobject HashObject;
typedef struct hashobject *HashObjectPtr;


struct hashobject{
  char *key;
	void *value;
	
	void (*f)(HashObjectPtr obj);
};


HashObjectPtr newHashObject(char *key, char *value);


void freeHashObject(HashObjectPtr obj);

#endif /* HASHOBJECT_H_ */
