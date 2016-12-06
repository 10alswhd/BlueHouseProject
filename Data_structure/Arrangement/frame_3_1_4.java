public class Array3 {
    public static void main(String[] args) {
        int[] arr1 = {1, 10, 5, 7, 6};
        int[] arr2 = {0};
        int[] arr3 = {};
        int[] arr4 = {0, 0, 15, 25, 16};
        int[] arr5 = {-3, 25, 2};

        printArray(arr1);
        printArray(arr2);
        printArray(arr3);
        printArray(arr4);
        printArray(arr5);
    }

    static void printArray(int[] data) {
        String result = "[";
        int i = 0;
        String separate = ", ";

        while (i < data.length) {
            if (i == data.length - 1) {
                separate = "";
            }
            result += (data[i] + separate);
            i++;
        }

        result += "]";

        System.out.println(result);
    }
}
