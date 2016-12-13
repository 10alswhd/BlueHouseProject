#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "brilliant.h"
    #define LIMIT 10000


    typedef struct triplet {
      int a;
      int b;
      int c;
    } triplet;

    //returns a triplet, in which a < b < c
    triplet* newTriplet(const int a, const int b, const int c) {
      triplet* result = (triplet*) malloc(sizeof(triplet));
      int values[] = {a,b,c};
      qsort(values,3,sizeof(int),cmpInt);
      result->a = values[0];
      result->b = values[1];
      result->c = values[2];
      return result;
    }

    void printTriplet(const triplet* t) {
    	printf("%d,%d,%d\n",t->a,t->b,t->c);
    }

    void initTriplets(triplet* triplets[], const int size) {
      int i;
      for (i=0; i < size; i++) {
      	triplets[i] = 0;
      }
    }

    //linear search
    int hasTriplet(const triplet* t, triplet* triplets[], const int size) {
    	int i;
    	triplet* current;
    	for (i=0; i < size; i++) {
    		current = triplets[i];
    		if (current != 0 && current->a == t->a && current->b == t->b && current->c == t->c) {
    			return 1;
    		}
    	}
    	return 0;
    }

    int main(int count, char** args) {

    	int a,b,c = 0;
    	int results = 0;
    	triplet* foundTriplets[1000];
    	initTriplets(foundTriplets,1000);

    	for (a=1; a<LIMIT; a++) {
    		for (b=1; b<LIMIT; b++) {
    			for (c=1; c<LIMIT; c++) {
    				if ((b*c - 31) % a == 0 &&
    					(c*a - 31) % b == 0 &&
    					(a*b - 31) % c == 0 &&
    					gcd3(a,b,c)==1) {
    						triplet* otherTriplet = newTriplet(a,b,c);
    						if (!hasTriplet(otherTriplet,foundTriplets,1000)) {
    							foundTriplets[results] = otherTriplet;
    							results++;
    							printf("(%d,%d,%d) %d\n\n",
    								otherTriplet->a,
    								otherTriplet->b,
    								otherTriplet->c,
    								results);
    						}
    				}
    			}
    		}
    	}

    	return 0;
    } 
