#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
void find(int *, int , int , int&, int&, int);
int binary_search(int *, int , int , int );
void find(int * a, int ptr, int year, int& length, int& start, int arr_size) {
  int t = binary_search(a, a[ptr]+year-1, ptr, arr_size-1);
  if (t-ptr+1>length ) {
     length = t-ptr+1;
     start = ptr;
  }
}
int binary_search (int * a,  int value, int low, int high ) {
   int ans = 0;
   if(low == high) {return low;}
   int mid = (low + high) / 2 +1 ;
   if (a[mid]<=value) {
     ans = binary_search(a,value,mid,high);
   } else {
     ans = binary_search(a,value,low, mid-1);
   }
}
int main  () {
 int Y=0;
 while(cin>>Y ) {
   int M=0, length=0, start=0;
    cin >> M;
   int *a = new int[M];
   for(int i=0;i<M;i++) cin >> a[i];
   for(int i=0;i<M;i++) {

     find(a,i,Y,length,start,M);

   }
   cout << length << " " << a[start] << " " << a[start + length -1] <<endl;
   delete [] a;
 }
 return 0;
}
