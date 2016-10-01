//shell sort 
 
 
 #include <iostream> 
 
 
 using namespace std; 
 
 
 int iCount (int *A,int size) 
 { 
     int counter = 0 ; 
 
 
     for (int i = 0  ; i < size ; i++) 
     { 
         for (int j = i+1 ; j < size -1 ; j++) 
         { 
         if(A[i] > A[j]) 
              counter++; 
         } 
     } 
     return counter ; 
 } 
 
 
 
 
 int main() 
 { 
 
 
 
 
     int array[5] = {2,3,9,5,6}; 
 
 
     int size = sizeof(array)/sizeof(int); 
 
 
     for (int gap = size/2 ; gap > 0 ; gap /=2 ) 
     { 
         for  (int i = gap ; i < size ; i++) 
         { 
             for ( int j = i-gap ; j >= 0 ; j= j-gap) 
             { 
                 if(array[j] > array[j+gap]) 
                     swap(array[j],array[j+gap]);             } 
         } 
         cout << "Remaining Inverstion : " << iCount(array,size ) << endl; 
     } 
 
 
 
 
 
 
 
 
     for (int i = 0 ; i < size ; i++) 
     { 
 
 
        cout << array[i] << " " ; 
     } 
 } 
