#include<stdio.h>

int Partition(int A[],int left,int right){
  int x = A[left];
  int i = left;
  int j;
  for(j=left+1;j<=right;j++){
    if(A[j] < x ){
      i++;
      int buf = A[i];
      A[i] = A[j];
      A[j] = buf;
    }
  }
  int buf = A[i];
  A[i] = A[left];
  A[left] = buf;
  return i;
}


void qsort(int A[],int left,int right){
  if(left >= right){
    return;
  }else{
    int middle = Partition(A,left,right);
    qsort(A,left,middle-1);
    qsort(A,middle+1,right);
  }
}

int main(void){
  int n;
  int array[100];
  scanf("%d",&n);
  int i;
  for(i=0;i<n;i++){
    scanf("%d",&array[i]);
  }
  qsort(array,0,n-1);
  for(i=0;i<n;i++){
    printf("%d ",array[i]);
  }
  puts("");
  return 0;
}
