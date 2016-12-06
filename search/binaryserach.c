#include <stdio.h>
#include <stdlib.h>

int compare_int(const void * a,  const void * b)
{
  return (*(int*)a - *(int*)b);
}

int var_list[] = { 50, 20, 60, 40, 10, 30 };

int main()
{
  int * pItem;

  qsort (var_list, (sizeof(var_list) / sizeof(int)), sizeof (int), compare_int);
  pItem = (int*) bsearch (40, values, (sizeof(var_list) / sizeof(int)), sizeof (int), compare_int);
  
  if (pItem!=NULL)
    printf ("%d is in the array.\n",*pItem);
  else
    printf ("%d is not in the array.\n",key);
  
  return 0;
}
