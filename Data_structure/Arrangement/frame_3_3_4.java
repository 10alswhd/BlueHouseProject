package lesson_3;

import java.util.Arrays;
import java.util.Random;

public class JoinArrays {
    public static void main(String[] args) {
        int[] arr1 = createArray();
        int[] arr2 = createArray();

        System.out.println("arr1: " + Arrays.toString(arr1));
        System.out.println("arr2: " + Arrays.toString(arr2));

        System.out.println("Result Array: " + Arrays.toString(union(arr1, arr2)));
    }

    static int[] createArray() {
        int[] arr = new int[5];
        Random rand = new Random();

        for (int i = 0; i < arr.length; i++) {
            arr[i] = rand.nextInt(100);
        }
        return arr;
    }

    static int[] union(int[] data1, int[] data2) {
        int[] resArray = new int[data1.length + data2.length];

        for (int i = 0; i < data1.length; i++) {
            resArray[i] = data1[i];
        }
        for (int j = data1.length; j < (data1.length + data2.length); j++) {
            resArray[j] = data2[j - data1.length];
        }

        return resArray;
    }
}
