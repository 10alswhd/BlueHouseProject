#include<stdio.h>
int main()
{
    int array[7];
    int i,j,search,max;

    for(i=0;i<7;i++)
    {
        printf("Enter ur value of [%d]:\n",i);
        scanf("%d",&array[i]);

    }
   
    max = array[0];
    for(j=0;j<7;j++)
    {
        if (max<array[j])
        {
            max = array[j];

        }
    }
    printf("Maximum value is %d\n",max);
    max = array[0];
    for(j=0;j<7;j++)
    {
        if (max>array[j])
        {
            max = array[j];

        }
    }
    printf("Mini value is %d\n",max);





    return(0);
}
