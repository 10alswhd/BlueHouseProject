#include <stdio.h>

void scanArray2D(int arr2D[][5],int ROW,int COL);
void printArray2D(int arr2D[][5],int ROW,int COL);
int searchItem2D(int arr2D[][5],int ROW,int COL,int item);

int main(void)
{
    int x,y,a[5][5],item;
    printf("Enter Row and Column: \n");
    scanf("%d%d",&x,&y);
    scanArray2D(a,x,y);
    printArray2D(a,x,y);
    printf("Numbers1 :\n");
    scanf("%d",&item);
    searchItem2D(a,x,y,item);

}
void scanArray2D(int arr2D[][5],int ROW,int COL)
{
int i,j;
   for(i=0;i<ROW;i++){
    for(j=0;j<COL;j++)
    {
        printf("Numbers :\n");
        scanf("%d",&arr2D[i][j]);

    }

   }
        }
void printArray2D(int arr2D[][5],int ROW,int COL)
{
   int i,j;
   for(i=0;i<ROW;i++)
{
         for(j=0;j<COL;j++)
         {
           printf("%d",arr2D[i][j]);
         }
printf("\n");

}   }
int searchItem2D(int arr2D[][5],int ROW,int COL,int item)
{
   int i,j;
    for(i=0;i<ROW;i++)
   {
       for(j=0;j<COL;j++)
        if(arr2D[i][j]==item)
        printf("Found\n");
   }

}
