/*
 * MyArrayListTester.java
 *
 */

/**
 * Tester for the <code>MyArrayList</code> class. <br>
 * <code><b> [Omi-GP2-EA2-Aufgabenteil2] </b></code>
 *
 * @author Annika Harms (annika.fischli@web.de)
 *
 */
public class MyArrayListTester {

    /**
     * Test the functionalities of the MyArrayList class.
     *
     * @param args
     *            not used
     */
    public static void main(String[] args) {
        // Hier hast du die Generic argumente vergessen
        MyArrayList<String> myList = new MyArrayList<>(15, 5);

        System.out.println("Test capacity and size.");
        System.out.println(myList.getCapacity() == 15);
        System.out.println(myList.getSize() == 0);
        myList.add("auto");
        myList.add("flugzeug");
        myList.add("boot");
        System.out.println(myList.getSize() == 3);

        System.out.println("Test get()");
        System.out.println(myList.toString().equals("auto, flugzeug, boot"));
        System.out.println(myList.get(0).equals("auto"));
        System.out.println(myList.get(1).equals("flugzeug"));
        System.out.println(myList.get(2).equals("boot"));

        System.out.println("Test remove()");
        myList.remove(0);
        System.out.println(myList.get(0).equals("flugzeug"));
        System.out.println(myList.get(1).equals("boot"));

        boolean caught = false;
        try {
          myList.get(2);
        } catch (IndexOutOfBoundsException e) {
          caught = true;
          System.out.println("Success: Caught exception " + e);
        } finally {
          if (!caught) {
            System.out.println("ERROR: No exception caught");
          }
        }

    }

}
