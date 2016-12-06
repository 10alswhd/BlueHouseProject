import java.io.PrintWriter;
import java.util.Random;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Chanaka
 */
public class DynamicArray {

    static int temp[];
    static long max = 0;
    static long min = Long.MAX_VALUE;
    static long sum = 0;

    static void read_array(int arr[]) {
        for (int j = 0; j < arr.length; j++) {
            System.out.println(j + " " + arr[j]);
        }
    }

    static int[] push_value(int arr[], int index, int val) {
        arr[index] = val;
        return arr;
    }

    static void copy_array(int newArr[], int oldArr[]) {
        for (int k = 0; k < temp.length; k++) {
            newArr[k] = temp[k];
        }
    }

    static void set_time(long time) {
        if (time > max) {
            max = time;
        }
        if (time < min) {
            min = time;
        }
        sum += time;
    }

    static PrintWriter create_file() {
        try {
            PrintWriter writer = new PrintWriter("output.txt", "UTF-8");
            return writer;
        } catch (Exception e) {
            System.out.println(e);
            return null;
        }
    }

    public static void main(String[] args) {
        Random rand = new Random();
        int input[] = {1000, 1001, 2000, 2001, 4000, 4001, 8000, 8001, 16000, 16001};

        int arr[] = new int[1000];
        PrintWriter writer = create_file();

        for (int i = 0; i < input.length; i++) {
            for (int t = 0; t < 5; t++) {
                int val = rand.nextInt(1000);
                for (int j = 0; j < input[i]; j++) {
                    long start = System.nanoTime();
                    try {
                        temp = push_value(arr, j, val);
                    } catch (ArrayIndexOutOfBoundsException e) {
                        arr = new int[arr.length * 2];
                        copy_array(arr, temp);
                        push_value(arr, temp.length, val);
                    }
                    long end = System.nanoTime();
                    long duration = end - start;
                    set_time(duration);
//                    System.out.println("Time in (ns) for " + input[i] + " : " + duration);
                }
            }
            System.out.print("Time in (ns) for " + input[i] + " : ");
            System.out.print("Max " + max);
            System.out.print("\tMin " + min);
            System.out.print("\tAvg " + sum / 5000 + "\n");

            writer.print("Time in (ns) for " + input[i] + " : ");
            writer.print("Max " + max + "\t");
            writer.print("Min " + min + "\t");
            writer.println("Avg " + sum / 5000);

            max = 0;
            min = Long.MAX_VALUE;
            sum = 0;
        }
        writer.close();
    }
}
