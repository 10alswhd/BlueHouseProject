import java.util.Arrays;

/**
 * Created by IntelliJ IDEA.
 * User: mifang
 * Date: 12/21/11
 * Time: 2:48 PM
 * To change this template use File | Settings | File Templates.
 */
public class ArrayCopyTest {

    public static void main(String[] args) {
        byte[] source = new byte[1024 * 10];
        Arrays.fill(source, (byte) 'a');

        int count = 100000;
        test(source, true, 100);
        System.out.println("finished warmup");

        count = 10;
        int size = 2;
        while (count-- > 0) {
            test(source, false, size);
            size *= 2;
        }
    }

    private static void test(byte[] source, boolean isWarmup, int copyLength) {
        int repeat = 1000000;
        //manual copy
        byte[] destManual = new byte[copyLength];
        long startManual = System.nanoTime();
        for (int count = 0; count < repeat; count++) {
            for (int i = 0; i < copyLength; i++) {
                destManual[i] = source[i];
            }
        }
        long elapsedManual = System.nanoTime() - startManual;
        //arraycopy
        byte[] destSystem = new byte[copyLength];
        long startSystem = System.nanoTime();
        for (int count = 0; count < repeat; count++) {
            System.arraycopy(source, 0, destSystem, 0, copyLength);
        }
        long elapsedSystem = System.nanoTime() - startSystem;

        if (!isWarmup) {
            System.out.printf("length:%,d\tmanual:%,d vs system:%,d diff:%,d\n", copyLength, elapsedManual, elapsedSystem, (elapsedManual - elapsedSystem));
        }

    }


}
