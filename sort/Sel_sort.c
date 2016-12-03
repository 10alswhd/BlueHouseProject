void SelectionSort(int a[], int array_size)
{
     int i;
     for (i = 0; i < array_size - 1; ++i)
     {
          int j, min, gecici;
          min = i;
          for (j = i+1; j < array_size; ++j)
          {
               if (a[j] < a[min])
                    min = j;
          }

          gecici = a[i];
          a[i] = a[min];
          a[min] = gecici;
     }
}
