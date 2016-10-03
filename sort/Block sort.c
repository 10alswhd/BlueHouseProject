 #include <stdio.h> 
 #include <stdlib.h> 
 #include <time.h> 
 
 
 void sort_array(int *tab, int size, int (^block)(int var1, int var2)) { 
    while (1) { 
       int i, count = 0; 
       for (i = 0; i < size - 1; i++) { 
          if (block(tab[i], tab[i + 1]) > 0) { 
             int tmp = tab[i]; 
             tab[i] = tab[i + 1]; 
             tab[i + 1] = tmp; 
             count++; 
          } 
       } 
 
 
       if (count == 0) 
          break; 
    } 
 } 
 
 
 int main(int argc, char **argv) { 
    int array[] = { 
       30, 60, 17, 120, 42, 25, 32, 47, 
       93, 75, 88, 230, 1270, 300, 400, 
       224, 440, 89, 330, 1, -100, 5052 
    }; 
 
 
    int tab_size = sizeof(array) / sizeof(int); 
 
 
    srand(time(NULL)); 
    int magic_index = rand() % tab_size; 
    int magic_value = array[magic_index]; 
 
 
    sort_array(array, tab_size, ^(int var1, int var2) { 
       if (var1 == magic_value) 
          return -1; 
       if (var2 == magic_value) 
          return 1; 
       return var2 - var1; 
    }); 
 
 
     for (int i = 0; i < tab_size; i++) 
       printf("%d ", array[i]); 
    printf("\n"); 
 
 
    return 0; 
 } 
