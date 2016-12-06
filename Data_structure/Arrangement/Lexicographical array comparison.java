public final class ArrayUtils {
    private ArrayUtils() {

    }

    public static <T extends Comparable<T>> int compare(T[] arr1, T[] arr2) {
        int length = Math.min(arr1.length, arr2.length);
        for (int i = 0; i < length; i++) {
            int compare = arr1[i].compareTo(arr2[i]);
            if (compare != 0)
                return compare;
        }
        return arr1.length - arr2.length;
    }
}
