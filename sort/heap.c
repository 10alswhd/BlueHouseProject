#include<stdio.h>
void max_heapify(int *,int);
void build_heap(int arr[]);
void display(int *);
void heap_sort(int *);
void te(int *);
int heap_length,arr_length;
int main(int argc, char* argv[]){
	int n,i;
	scanf("%d",&n);
	arr_length=n;
	int arr[n+1];
	for(i=1;i<=n;i++){
		scanf("%d",&arr[i]);
		}
	display(arr);
	heap_sort(arr);
	display(arr);
	}
void build_heap(int arr[]){
	heap_length=arr_length;
	int i;
	for(i=(heap_length/2);i>=1;i--){
		max_heapify(arr,i);
		}
	return;
	}
void max_heapify(int *arr,int index){
	int l=2*index,r=(2*index)+1,max,tmp;
	if(l<=heap_length && *(arr+l)>*(arr+index))max=l;
	else max=index;
	if(r<=heap_length && *(arr+r)>*(arr+max))max=r;
	if(max!=index){
		tmp=*(arr+index);
		*(arr+index)=*(arr+max);
		*(arr+max)=tmp;
		max_heapify(arr,max);
		}
	return;
	}
void display(int *arr){
	int i;
	int l=arr_length;
	for(i=1;i<=l;i++){
		printf("%d ",arr[i]);
		}
	printf("\n");
	return;
	}
void heap_sort(int *arr){
	build_heap(arr);
	int i,tmp;
	for(i=arr_length;i>=1;i--){
		tmp=*(arr+i);
		*(arr+i)=*(arr+1);
		*(arr+1)=tmp;
		heap_length--;
		max_heapify(arr,1);
		}
	return ;
	}
