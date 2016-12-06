import java.util.Arrays;

public class SortArray3 {
    public static void main(String[] args) {

        int[] arr1 = {5, 6, 7, 8, 9, 10};

        sort(arr1);

        System.out.println(Arrays.toString(arr1));

    }

    static void sort(int[] data) {
        if (data == null || data.length < 2) return;

        for (int j = 0; j < data.length; j++) {
            swap(data);
        }
    }

    static void swap(int[] data) {
        if (data == null || data.length < 2) return;

        for (int i = 0; i < (data.length - 1); i++) {
            if (data[i] < data[i + 1]) {
                int temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
            }
        }
    }
}
