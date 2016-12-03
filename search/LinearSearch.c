#include <stdio.h>
main()
{
    int a[100],i,n,pos=0,item;
    printf("Enter How many elements on your Array: ");
    scanf("%d",&n);
    printf("\nEnter %d elements values : ",n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    printf("\nEnter a Item to Search: ");
    scanf("%d",&item);
    for(i=0;i<n;i++)
    {
        if(a[i]==item)
        {
            pos=i+1;
            break;
        }
    }
    if(pos==0)printf("\nNot Found !\n");
    else printf("\nItem Found at Position %d\n",pos);
}
