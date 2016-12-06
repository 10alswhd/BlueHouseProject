package lesson3;

import java.util.Arrays;

public class Frame8 {

	public static void main(String[] args) {

		int[] data = { 10, 3, 25, 4 };

		System.out.println("before: " + data[1] + ", " + data[3]);

		swap(data, 1, 3);

		System.out.println("after: " + data[1] + ", " + data[3]);

		System.out.println(Arrays.toString(data));

	}

	static void swap(int[] data, int i, int k) {
		if (data == null || (data.length - 1 < i) || (data.length - 1 < k)) {
			return;
		}

		int cell = data[i];
		data[i] = data[k];
		data[k] = cell;
	}
}
