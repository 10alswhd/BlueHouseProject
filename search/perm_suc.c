//gcc -std=c99
#include<stdio.h>
#include<stdlib.h>
void swap_int(int *a,int *b){
    int t = *a;
	*a = *b;
	*b = t;
}
void reverse_int_array(int array[],int num){
	for(int i=0;i<num/2;i++){
		swap_int(&array[i],&array[num-1-i]);
	}
}
void print_int_array(int array[],int num){
	printf("[ ");
	for(int i=0;i<num;i++)printf("%d ",array[i]);
	printf("]\n");
}

int perm_search_next_item(int array[],int num,int startIndex,int keyIndex){
	int resultIndex = -1;
	for(int i=startIndex;i<num;i++){
		if(array[keyIndex] < array[i]){
			if(resultIndex==-1){
				resultIndex = i;
			}else if(array[i] <= array[resultIndex]){
				resultIndex = i;
			}
		}
	}
	return resultIndex;
}

//0:終わり
//1:arrayを次の順列にしました
int perm_suc(int array[],int num){
	int i;
	for(i=num-2;i>=0;i--){
		if(array[i]<array[i+1])break;
	}
	if(i<0)return 0;
	int nextIndex = perm_search_next_item(array,num,i+1,i);
	if(nextIndex==-1){
		fprintf(stderr,"perm_search_next_item() error\n");
		return 0;
	}
	swap_int(&array[i],&array[nextIndex]);
	reverse_int_array(&array[i+1],num-(i+1));
	return 1;
}

int main(int argc,char *argv[]){
	int *array = NULL;
	if(argc<=1){
		printf("usage : %s a[0] a[1] a[2] ...\n",argv[0]);
		exit(1);
	}
	int num = argc-1;
	array = malloc(sizeof(int)*num);
	for(int i=0;i<num;i++){
		array[i] = atoi(argv[i+1]);
	}
	while(1){
		print_int_array(array,num);
		if(!perm_suc(array,num))break;
	}
	
	free(array);
	array=NULL;
	return 0;
}
