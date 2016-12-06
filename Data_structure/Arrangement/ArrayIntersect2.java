private static int[] intersect_int_array(int[] array1, int[] array2) {
         java.util.Arrays.sort(array1);
         java.util.Arrays.sort(array2);
         
         IntList res = new IntList();
         for(int index2 = 0, index1 = 0; index2 < array2.length && index1 < array1.length; ) {
             if (array1[index1] > array2[index2]) {
                 index2 ++;
             } else if (array2[index2] > array1[index1]) {
                 index1 ++;
             } else {
                 res.add(array2[index2]);
                 index1 ++;
                 index2 ++;
             }
         }
         
         return res.toArray();
}
