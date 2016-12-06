#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
*	Interative binary search implementation
*/
bool search(int value, int values[], int n)
{
	
	int beginning = 0;
	int ending = n - 1;

	while (ending >= beginning)
	{
		//look at the middle of the list
		int middle = (beginning + ending) / 2;

		//if value found, return true
		if (value == values[middle])
			return true;

		//else if middle is higher, search left
		else if (values[middle] > value)
			ending = middle - 1;

		//else if middle is lower, search righ;
		else
			beginning = middle + 1;
		
	}
		//Value not found
		return false;
}


/*
* Selection Sort implementation.
*/
void sort(int values[], int n)
{
	//while the list is out of order
	for (int i = 0; i < n; i++)
	{
		int smallest = values[i];
		int smallest_location = i;

		//go through the entire list
		for (int j = i + 1; j < n; j++)
		{
			//find the smallest number
			if (smallest > values[j]){
				smallest = values[j];
				smallest_location = j;
			}
		}
		//put the beginning of the list where the smallest number was
		values[smallest_location] = values[i];

		//place it on the beginning of the list
		values[i] = smallest;
	
	}
}

int main(int argc, char const *argv[])
{
	int list[] = {1,2,3,4,5,6,8,7,9,10};
	//The lists gets ordered.
	sort(list, 10);

	if(search(atoi(argv[1]), list, 10))
		printf("Encontrado, la busqueda fue exitosa\n");
	else
		printf("No encontrado, no hubo resultados\n");

	return 0;
}
