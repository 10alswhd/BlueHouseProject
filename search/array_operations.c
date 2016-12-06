#include<stdio.h>
#include <conio.h>

#define ARR_LENGTH 20

int search(int arr[],int len, int n);
int insert(int arr[],int len, int n, int p);
int delete(int arr[],int len, int p);
void print_arr(int arr[],int len);

int main() {
    int arr[ARR_LENGTH];
    int no; // no of elements
    int i, n, pos;
    
    printf("Enter no of elements: ");
    scanf("%d", &no);
    printf("enter elements:\n");
    /* get the array */
    for (i = 0; i < no; i++)
    {
        scanf("%d",&arr[i]);    
    }
    
    /* Inserting 
    printf("Enter element to insert: ");
    scanf("%d", &n);
    printf("Enter posistion: ");
    scanf("%d", &pos);
    
    no = insert(arr, no, n, pos);
    print_arr(arr, no);*/
    
    /* Deleting */
    
    
    printf("Enter posistion to delete: ");
    scanf("%d", &pos);
    no = delete(arr,no,pos);
    print_arr(arr, no);
    
    
    getch();
    return 0;
} 

void print_arr(int arr[],int len)
{
     int i;
     printf("array is:\n");
     for(i=0;i<len;i++)
            printf("%d\n",arr[i]);
             
}

int search(int arr[],int len, int n)
{
    int flag = -1, i;
    
    for(i=0;i<len;i++)       
     if(arr[i]==n) {
      flag = i;
      break;
      }
      
      return flag;
}
      
int insert(int arr[],int len, int n, int p)
{
     int i;
     if (len+1 < ARR_LENGTH) { 
        for(i=len-1;i>=p;i--) 
            arr[i+1]=arr[i];
        arr[p] = n;
        return len+1;
        }
     else {
          printf("Error inserting element");
          return len;
          }
}     

int delete(int arr[],int len, int p)
{
     int i;
     arr[p] = 0;
     for (i = p+1; i<len; i++) 
         arr[i-1] = arr[i];
     return len-1;
}   
   
