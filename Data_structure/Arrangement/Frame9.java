package lesson3;

import java.util.Arrays;

public class Frame9 {

	public static void main(String[] args) {
		int[] data1 = { 1, 10, 5, 7, 6 };
		int[] data2 = { 0 };
		int[] data3 = {};
		int[] data4 = { 0, 0, 15 ,25 , 16};
		int[] data5 = { -3, 25, 2};
		
		printArray(data1);
		printArray(data2);
		printArray(data3);
		printArray(data4);
		printArray(data5);
	}
	
	static void printArray(int [] data){
		 System.out.println(Arrays.toString(data));
		}
	
}
