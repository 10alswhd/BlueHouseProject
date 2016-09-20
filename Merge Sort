#include <iostream> 
 
 
 void merge(int ar[], int low, int high, int mid) 
 { 
     //int *c = new int[high]; to fit temporary storage Needs one more that index to fit temporary storage 
     int *c = new int[high + 1]; 
 
 
     // i goes from i to mid and j goes from j+1 to high 
     int i = low; 
     //int j = mid; 
     int j = mid + 1; 
     int k = low; 
     while (i <= mid && j <= high) 
     { 
         if (ar[i] < ar[j]) 
         { 
             c[k] = ar[i]; 
             ++i; 
         } 
         else 
         { 
             c[k] = ar[j]; 
             ++j; 
         } 
         ++k; 
     } 
 
 
 
 
     while (i <= mid) // need to copy mid'th element 
     { 
         c[k++] = ar[i++]; 
     } 
 
 
 
 
     while (j <= high) // need to copy high'th element 
     { 
         c[k++] = ar[j++]; 
     } 
 
 
     for (i = low; i < k; ++i) 
     { 
         ar[i] = c[i]; 
     } 
 

     delete[] c; 
 } 
 
 
 
 
 
 
 void mergesort(int ar[], int low, int high) 
 { 
     int mid; 
     if (low < high) 
     { 
 
 
         mid = (low + high) / 2; 
         mergesort(ar, low, mid); 
         mergesort(ar, mid + 1, high); 
         merge(ar, low, high, mid); 
     } 
 } 
 
 
 int _tmain(int argc, _TCHAR* argv[]) 
 { 
     int ar[] = { 3, 7, 2, 19, 5, 1, 41, 39, 27 }; 
     int sizeofar = sizeof ar / sizeof(int) - 1; // it's not size of arr. Should be range of index actually. 
 
 
     std::cout << "Unsorted"<<std::endl; 
     for (int i = 0; i < sizeofar+1; ++i) 
     { 
         std::cout << ar[i] << "\t"; 
     } 
     std::cout << std::endl; 
 
 
     mergesort(ar, 0, sizeofar); 
 
 
     std::cout << "Sorted" << std::endl; 
     for (int i = 0; i < sizeofar + 1; ++i) 
     { 
         std::cout << ar[i] << "\t"; 
     } 
     std::cout << std::endl; 
     return 0; 
 } 
