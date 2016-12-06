 int binary_search(int *a,int x,int n)
  {  int low,mid,high;
      low=0;
      high=n-1;
     while(1)
     {
          mid=(low+high)/2;     
          if(low==mid && a[low]!=x)
             break;
         if(a[mid] < x)
            low=mid;
         else if(a[mid] > x)
           high=mid;
         else return mid;  
      }
      return -1;
   }
