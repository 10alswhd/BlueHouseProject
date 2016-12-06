int linear_search(int *list,int size, int key)
{
  int i;
  for(i=0;i<=size;++i)
  {
    if(key==list[i])
    return i;
  }
  return 0;
}
