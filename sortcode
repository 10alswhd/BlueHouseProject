#include <stdio.h> 

 
#define N 3 

int main() 
{ 
  int num[N]; 
 	int i, j, tmp; 
 
 
 	for( i = 0 ; i < N ; i++ ){ 
 
 
 		scanf("%d", &num[i]); 
 
 
 	} 
 
 
 	for( i = 0 ; i < N-1 ; i++ ){ 
 		for( j = i ; j < N ; j ++ ){ 
 
 
 			if( num[i] > num[j] ){ 
 
 
 				tmp = num[j]; 
 				num[j] = num[i]; 
 				num[i] = tmp; 
 
 
 			}	 
 
 
 		} 
 	} 
 
 
 	for( i = 0 ; i < N ; i++ ){ 
 
 
 		printf("%d ", num[i]); 
 
 
 	} 
 
 
 	printf("\n"); 
 
 
 	return 0; 
 } 
