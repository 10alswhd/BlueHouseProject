import java.util.Scanner;
public class Reverese {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println(reverse(sc.nextLine().toCharArray()));
        sc.close();
    }
    public static String reverse(char[] strs) {
        int len = strs.length / 2;
        char temp = ' ';
        for (int loop = 0; loop < len; loop++) {
            temp = strs[loop];
            strs[loop] = strs[strs.length - 1 - loop];
            strs[strs.length - 1 - loop] = temp;
        }
        return new String(strs);
    }
}
