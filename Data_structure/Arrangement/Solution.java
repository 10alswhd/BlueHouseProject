//        sort(array);

    public static void sort(int[] array)
    {
        for (int i = 0; i < array.length; i++){
            int max = array[i];
            int imax = i;
            for (int j = i + 1; j < array.length; j++){
                if (array[j] > max){
                    max = array[j];
                    imax = j;
                }
            }
            if (i != imax){
                int temp = array[i];
                array[i] = array[imax];
                array[imax] = temp;
            }
        }
    }
