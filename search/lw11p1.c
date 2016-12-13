/*********************************************************/
/* lw11p1.c                                              */
/*********************************************************/
/* Author: Enes Gönültaş                                 */
/* Number: 151044030                                     */
/* Date: 05.05.2016                                      */
/*                                                       */
/* Description: Lab 11 Part 1                            */
/*                                                       */
/*********************************************************/
/* Notes:                                                */
/* References:                                           */
/*********************************************************/

/* "include" section */
#include <stdio.h>
#include <string.h>

/* Prototypes */
/*********************************************************/
/* int lwFind(Country *arr, int size, char *query)       */
/*********************************************************/
/* Parameters: Function takes three parameter(s).        */
/*     arr: Country array                                */
/*     size: Size of the array                           */
/*     query: Country name                               */
/*********************************************************/
/* Return Value: Function returns an integer.            */
/*     Index of the Country or -1 failure                */
/*********************************************************/
/* Description: lwFind(arr, size, query) --> index       */
/*     This function takes an array of countries, finds  */
/*     given country in array, returns index of the      */
/*     country or -1 on failure.                         */
/*********************************************************/
/* Notes:                                                */
/*********************************************************/
int lwFind(Country *arr, int size, char *query);

/* Functions */
/*********************************************************/
/* Description: lwFind(arr, size, query) --> index       */
/*     This function takes an array of countries, finds  */
/*     given country in array, returns index of the      */
/*     country or -1 on failure.                         */
/*********************************************************/
int lwFind(Country *arr, int size, char *query)
{
	/* Iteration variable */
	int i;
	/* Result variable */
	int index;


	/* Initialize 'index' */
	index = -1;

	/* Check input */
	if(size <= 0 || query == NULL)
	{
		return index;
	}

	/* Search */
	for(i = 0; i < size; i += 1)
	{
		if(!strcmp(arr[i].name, query))
		{
			index = i;
		}
	}

	return index;
}

/* EOF */
