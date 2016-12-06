public class o2i {
    private static Object getIntArray()
    {
        int[] array = new int[] { 1, 2, 3, 4, 5};
        Object obj = array;
        return obj;
    }

    public static void main(String[] args) {
        Object obj = getIntArray();
        int[] array = (int[])obj;
        for( int i=0, len=array.length; i<len; i++ )
            System.out.println( array[i] );
        System.out.println("Hello! World!");
    }
}
