#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1000

char c;
int num[MAX];
int* toSort;
int nums;

void insertion(int* toSort,int size);
void selection(int* toSort, int size);
void bubbleSort(int* toSort,int size);
void shellSort(int* toSort,int size);
void mergeSort(int* toSort,int size);
void heapSort(int* toSort,int size);
void printNums(int* nums,int size);

int main(){
	printf("\nEnter size of array to be sorted.\n\n");
	scanf("%d",&nums);
	printf("Enter series of numbers to be sorted.\n\n");

	
	for(int i = 0; i< nums;i++){
		scanf("%d",&num[i]);
	}	

	
	toSort = malloc(sizeof(int)*(nums));
	
	printf("\n");
	for(int i = 0; i<nums;i++){
		printf("%d ",num[i]);
		toSort[i] = num[i];
	}
	
	printf(
	"\n\nSelect sorting method.\n"
	"\n1: insertionSort"
	"\n2: selectionSort"
	"\n3: bubbleSort"
	"\n4: shellSort"
	"\n5: mergeSort"
	"\n6: heapSort\n");
	
	getchar();
	while(1){
		if(isdigit(c = getchar()) && c < '7' && c > '0'){
			switch(c - '0'){
				case 1:
					printf("\n");
					insertion(toSort,nums);
					break;
				case 2:
					printf("\n");
					selection(toSort,nums);
					break;
				case 3:
					bubbleSort(toSort,nums);
					break;
				case 4:
					shellSort(toSort,nums);
					break;
				case 5:
					mergeSort(toSort,nums);
					printf("\n");
					break;	
				case 6:
					heapSort(toSort,nums);
					printf("\n");
					break;
				
			}
			break;
		}else{
			printf("Invalid input.\n");
			
		}
	}
	return 0;
}

//Loops through array swapping the selected value with prior ones until it finds one smaller than it
void insertion(int* toSort,int size){
	printNums(toSort,size);
	
	int x,y;
	
	for(int i = 1;i<size;i++){
		x = toSort[i];
		y = i -1;
		//swapping with smaller numbers
		while(y >= 0 && toSort[y] > x){
			toSort[y + 1] = toSort[y];
			y--;
		}
		//fill gap
		toSort[y + 1] = x;
	
		printNums(toSort,size);
	}
	printf("\n");
}

//Loops through the array then for each position, loops thrrough following elements and checks for smallest 
//value left to be sorted and swaps it with the element currently in that position.
void selection(int* toSort,int size){
	printNums(toSort,size);
	
	int x,y,temp;
	for(int i = 0;i<size;i++){
		x = i;
		for(int j = i+1;j<size;j++){
			if(toSort[j] < toSort[x])x = j;
		}
		temp = toSort[x];
		toSort[x] = toSort[i];
		toSort[i] = temp;

		printNums(toSort,size);
	}
	printf("\n");
}

//Moves smallest values to front by swapping with value in front of it, if it is larger.
void bubbleSort(int* toSort,int size){
	int x,y; 
	
	printNums(toSort,size);
	
	for(int i = 0;i < size; i++){
		y  = 0;
		
		for(int j = size;j>i;j--){
			if(toSort[j]<toSort[j-1]){
				x = toSort[j];
				toSort[j] = toSort[j - 1];
				toSort[j-1] = x;
				y = 1;
			}
		}
		printNums(toSort,size);
		if(y == 0)break;
	}
}

//Sorts elements at gradually decreasing intervals apart, similar to insertion sort.

void shellSort(int* toSort,int size){
	printNums(toSort,size);
	
	int x,y,z;
	z = 1;
	while(z < size)z *= 2;
	while(z > 0){
		z /= 2;
		for(int i = z; i< size; i+=z){
			x = toSort[i];
			y = i - z;
			while(y >= 0 && toSort[y] > x){
				toSort[y + z] = toSort[y];
				y -=z;
			}
			toSort[y + z] = x;

			printNums(toSort,size);
		}
		if(z == 1)break;
	}
}

//Divides array in two then recursively applies itself to the resulting sub arrays,
//this is repeated until there is only one element in each array then it merges all of them in order until a final single
//sorted array is left
void mergeSort(int* toSort,int size){
	printNums(toSort,size);
	if(size == 1){
		return;
	}
	
	int x,y,z,i;
	x = size/2;
	mergeSort(toSort,x);
	mergeSort(toSort + x ,size -x);
	printf("\n");
	int temp[x+1];
	for(i =0; i<= x;i++){
		temp[i] = toSort[i];
	}
	i = 0;
	y = x ;
	z = 0;
	while(i < x && y < size){
		toSort[z++] = (toSort[y]<temp[i])?toSort[y++] : temp[i++];
	}
	while(i < x){
		toSort[z++] = temp[i++];
	}
	printNums(toSort,size);
	printf("-----\n");
	
}


void heapify(int* toSort,int size){
	int root,c,temp;
	for(int i = 1;i<size;i++){
		c = i;
		while(c != 0){
			root = (c -1)/2;
			if(toSort[root] < toSort[c]){
				temp = toSort[root];
				toSort[root] = toSort[c];
				toSort[c] = temp;
			}
			c = root;
		}
	}
	
	printf("\n");
}

//Goes through the numbers (that are in a heap so largest number is first) then puts the first number to the end.
void heapSort(int* toSort, int size){
	int temp;

	printNums(toSort,size);
	
	for(int j = size-1;j>=0;j--){
		heapify(toSort,j+1);
		temp = toSort[j];
		toSort[j] = toSort[0];
		toSort[0] = temp;
	}
	printNums(toSort,size);
	
}

void printNums(int* nums,int size){
	for(int j = 0; j < size;j++){
		printf("%d ",nums[j]);
	}
	printf("\n");
}
