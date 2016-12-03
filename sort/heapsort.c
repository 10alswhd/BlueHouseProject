#define type int 
2 #define less(a, b) a < b 
3 #define swap(a, b) type t = a; a = b; b = t; 
4 
 
5 void sift(type *array, int start, int end) { 
6     while(start * 2 + 1 < end) { 
7         int child = 2 * start + 1; 
8         if (child + 1 < end && less(array[child], array[child + 1])) { 
9             child += 1; 
10         } 
11         if (less(array[start], array[child])) { 
12             swap(array[child], array[start]); 
13             start = child; 
14         } 
15         else return; 
16     } 
17 } 
18 
 
19 void heapsort(type* array, int n) { 
20     int start, end; 
21     for (start = (n - 2)/2; start >= 0; start--) { 
22         sift(array, start, n); 
23     } 
24     for (end = n - 1; end > 0; end--) { 
25         swap(array[end], array[0]); 
26         sift(array, 0, end); 
27     } 
28 } 
