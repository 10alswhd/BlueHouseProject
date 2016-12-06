import java.util.Arrays;
import java.util.List;

/**
 * Nested Arrays Flattener runnable program.
 *
 * @author Paolo Maresca {@email plo.maresca@gmail.com }
 */
public class NestedArraysFlattener
{

    private static final boolean DEBUG = false;

    /**
     * Flattener. Takes in input an Array of Objects, tries to flatten it into an Array of Integers.
     *
     * E.g. [[1,2,[3]],4] -> [1,2,3,4]
     *
     * @param nested    Array of nested Arrays
     * @return          A List of Integers
     */
    public static Integer[] flattener(Object[] nested)
    {
        List<Integer> flattened = flatten(nested);
        Integer[] canonical = new Integer[flattened.size()];

        return flattened.toArray(canonical);
    }

    /**
     * Recursive Helper.
     *
     * @param nested    Array of nested Arrays
     * @return          A List of Integers
     */
    public static List<Integer> flatten(Object[] nested)
    {
        if(nested == null)
            throw new IllegalArgumentException("Nestings cannot be NULL");

        List<Integer> flattened = new LinkedList<>();
        for(int i = 0; i < nested.length; i++) {
            if(nested[i] instanceof Integer)
                flattened.add((Integer) nested[i]);
            else if(nested[i] instanceof Object[])
                flattened.addAll(flatten((Object[]) nested[i]));
            else
                throw new IllegalArgumentException("Only Integers and Nested Arrays are allowed");
        }

        return flattened;
    }


    /**
     * Main
     *
     * @param args   Command Line arguments
     */
    public static void main(String[] args)
    {
        if(!test1()) {  // base case
            System.err.println("Test 1: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 1: Succeded: Continue Testing");

        if(!test2()) {  // null
            System.err.println("Test 2: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 2: Succeded: Continue Testing");

        if(!test3()) {  // nested null
            System.err.println("Test 3: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 3: Succeded: Continue Testing");

        if(!test4()) {  // null input
            System.err.println("Test 4: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 4: Succeded: Continue Testing");

        if(!test5()) {  // nested String
            System.err.println("Test 5: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 5: Succeded: Continue Testing");

        if(!test6()) {  // all valid nestings
            System.err.println("Test 6: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 6: Succeded: Continue Testing");

        if(!test7()) {  // all valid nestings in a strange order
            System.err.println("Test 7: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 7: Succeded: Continue Testing");

        if(!test8()) {  // all valid nestings, nested repetitions
            System.err.println("Test 8: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 8: Succeded: Continue Testing");

        if(!test9()) {  // yet another error case
            System.err.println("Test 9: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 9: Succeded: Continue Testing");

        if(!test10()) {  // yet another nesting combination
            System.err.println("Test 10: Failed: Unable to Continue");
            System.exit(1);
        } else
            System.out.println("Test 10: Succeded: Continue Testing");
    }

    public static boolean test1()
    {
        Object[] mainOne = new Object[2];
        Object[] firstNest = new Object[3];
        Object[] secondNest = new Object[1];
        secondNest[0] =  3;
        firstNest[0] =  1;
        firstNest[1] =  2;
        firstNest[2] = secondNest;
        mainOne[0] = firstNest;
        mainOne[1] = 4;

        Integer[] expected = { 1, 2, 3, 4 };
        Integer[] outcome = flattener(mainOne);

        return Arrays.equals(outcome, expected);
    }

    public static boolean test2()
    {
        Object[] mainOne = new Object[2];
        Object[] firstNest = new Object[3];
        Object[] secondNest = new Object[1];
        secondNest[0] =  3;
        firstNest[0] =  1;
        firstNest[1] =  2;
        firstNest[2] = secondNest;
        mainOne[0] = firstNest;
        mainOne[1] = null;

        try {
            flattener(mainOne);
            return false;
        } catch(Exception e) { if(DEBUG) e.printStackTrace(); return true; }
    }

    public static boolean test3()
    {
        Object[] mainOne = new Object[2];
        Object[] firstNest = new Object[3];
        Object[] secondNest = new Object[1];
        secondNest[0] = null;
        firstNest[0] =  1;
        firstNest[1] =  2;
        firstNest[2] = secondNest;
        mainOne[0] = firstNest;
        mainOne[1] =  4;

        try {

            flattener(mainOne);
            return false;
        } catch(Exception e) { if(DEBUG) e.printStackTrace(); return true; }
    }

    public static boolean test4()
    {
        try {
            flattener(null);
            return false;
        } catch(Exception e) { if(DEBUG) e.printStackTrace(); return true; }
    }

    public static boolean test5()
    {
        Object[] mainOne = new Object[2];
        Object[] firstNest = new Object[3];
        Object[] secondNest = new Object[1];
        secondNest[0] = null;
        firstNest[0] =  1;
        firstNest[1] = "";
        firstNest[2] = secondNest;
        mainOne[0] = firstNest;
        mainOne[1] =  4;

        try {
            flattener(mainOne);
            return false;
        } catch(Exception e) { if(DEBUG) e.printStackTrace(); return true; }
    }

    public static boolean test6()
    {
        Object[] mainOne = new Object[10];
        Object[] firstNest = new Object[1];
        Object[] secondNest = new Object[1];
        Object[] thirdNest = new Object[1];
        Object[] fourthNest = new Object[1];
        Object[] fifthNest = new Object[1];
        Object[] sixthNest = new Object[1];
        Object[] seventhNest = new Object[1];
        Object[] eightNest = new Object[1];
        Object[] ninthNest = new Object[1];
        Object[] tenthNest = new Object[1];
        firstNest[0] = 1;
        secondNest[0] = 2;
        thirdNest[0] = 3;
        fourthNest[0] = 4;
        fifthNest[0] = 5;
        sixthNest[0] = 6;
        seventhNest[0] = 7;
        eightNest[0] = 8;
        ninthNest[0] = 9;
        tenthNest[0] = 10;
        mainOne[0] = firstNest;
        mainOne[1] = secondNest;
        mainOne[2] = thirdNest;
        mainOne[3] = fourthNest;
        mainOne[4] = fifthNest;
        mainOne[5] = sixthNest;
        mainOne[6] = seventhNest;
        mainOne[7] = eightNest;
        mainOne[8] = ninthNest;
        mainOne[9] = tenthNest;

        Integer[] expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        Integer[] outcome = flattener(mainOne);

        return Arrays.equals(outcome, expected);
    }

    public static boolean test7()
    {
        Object[] mainOne = new Object[10];
        Object[] firstNest = new Object[1];
        Object[] secondNest = new Object[1];
        Object[] thirdNest = new Object[1];
        Object[] fourthNest = new Object[1];
        Object[] fifthNest = new Object[1];
        Object[] sixthNest = new Object[1];
        Object[] seventhNest = new Object[1];
        Object[] eightNest = new Object[1];
        Object[] ninthNest = new Object[1];
        Object[] tenthNest = new Object[1];
        firstNest[0] = 2;
        secondNest[0] = 1;
        thirdNest[0] = 4;
        fourthNest[0] = 3;
        fifthNest[0] = 6;
        sixthNest[0] = 5;
        seventhNest[0] = 8;
        eightNest[0] = 7;
        ninthNest[0] = 10;
        tenthNest[0] = 9;
        mainOne[0] = firstNest;
        mainOne[1] = secondNest;
        mainOne[2] = thirdNest;
        mainOne[3] = fourthNest;
        mainOne[4] = fifthNest;
        mainOne[5] = sixthNest;
        mainOne[6] = seventhNest;
        mainOne[7] = eightNest;
        mainOne[8] = ninthNest;
        mainOne[9] = tenthNest;

        Integer[] expected = {2, 1, 4, 3, 6, 5, 8, 7, 10, 9};
        Integer[] outcome = flattener(mainOne);

        return Arrays.equals(outcome, expected);
    }

    public static boolean test8()
    {
        Object[] mainOne = new Object[10];
        Object[] firstNest = new Object[1];
        Object[] secondNest = new Object[1];
        Object[] thirdNest = new Object[3];
        Object[] fourthNest = new Object[1];
        Object[] fifthNest = new Object[1];
        Object[] sixthNest = new Object[3];
        Object[] seventhNest = new Object[1];
        Object[] eightNest = new Object[1];
        Object[] ninthNest = new Object[1];
        Object[] tenthNest = new Object[3];
        firstNest[0] = 2;
        secondNest[0] = 1;
        thirdNest[0] = 4;
        thirdNest[1] = 4;
        thirdNest[2] = 4;
        fourthNest[0] = 3;
        fifthNest[0] = 6;
        sixthNest[0] = 5;
        sixthNest[1] = 5;
        sixthNest[2] = 5;
        seventhNest[0] = 8;
        eightNest[0] = 7;
        ninthNest[0] = 10;
        tenthNest[0] = 9;
        tenthNest[1] = 9;
        tenthNest[2] = 9;
        mainOne[0] = firstNest;
        mainOne[1] = secondNest;
        mainOne[2] = thirdNest;
        mainOne[3] = fourthNest;
        mainOne[4] = fifthNest;
        mainOne[5] = sixthNest;
        mainOne[6] = seventhNest;
        mainOne[7] = eightNest;
        mainOne[8] = ninthNest;
        mainOne[9] = tenthNest;

        Integer[] expected = {2, 1, 4, 4, 4, 3, 6, 5, 5, 5, 8, 7, 10, 9, 9, 9};
        Integer[] outcome = flattener(mainOne);

        return Arrays.equals(outcome, expected);
    }

    public static boolean test9()
    {
        Object[] mainOne = new Object[10];
        Object[] firstNest = new Object[1];
        Object[] secondNest = new Object[1];
        Object[] thirdNest = new Object[3];
        Object[] fourthNest = new Object[1];
        Object[] fifthNest = new Object[1];
        Object[] sixthNest = new Object[3];
        Object[] seventhNest = new Object[1];
        Object[] eightNest = new Object[1];
        Object[] ninthNest = new Object[1];
        Object[] tenthNest = new Object[3];
        firstNest[0] = 2;
        secondNest[0] = 1;
        thirdNest[0] = 4;
        thirdNest[1] = 4;
        thirdNest[2] = 4;
        fourthNest[0] = 3;
        fifthNest[0] = 6;
        sixthNest[0] = 5;
        sixthNest[1] = 5;
        sixthNest[2] = 5;
        seventhNest[0] = 8;
        eightNest[0] = 7;
        ninthNest[0] = 10;
        tenthNest[0] = 9;
        tenthNest[1] = "";
        tenthNest[2] = 9;
        mainOne[0] = firstNest;
        mainOne[1] = secondNest;
        mainOne[2] = thirdNest;
        mainOne[3] = fourthNest;
        mainOne[4] = fifthNest;
        mainOne[5] = sixthNest;
        mainOne[6] = seventhNest;
        mainOne[7] = eightNest;
        mainOne[8] = ninthNest;
        mainOne[9] = tenthNest;

        try {
            flattener(mainOne);
            return false;
        } catch(Exception e) { if(DEBUG) e.printStackTrace(); return true; }
    }

    public static boolean test10()
    {
        Object[] mainOne = new Object[10];
        Object[] firstNest = new Object[1];
        Object[] secondNest = new Object[1];
        Object[] thirdNest = new Object[3];
        Object[] fourthNest = new Object[1];
        Object[] fifthNest = new Object[1];
        Object[] sixthNest = new Object[3];
        Object[] seventhNest = new Object[1];
        Object[] eightNest = new Object[1];
        Object[] ninthNest = new Object[1];
        Object[] tenthNest = new Object[3];
        Object[] nest = new Object[1];
        Object[] nestNest = new Object[1];
        Object[] nestNestNest = new Object[1];
        Object[] nestNestNestNest = new Object[1];
        nestNestNestNest[0] = 100;
        nestNestNest[0] = nestNestNestNest;
        nestNest[0] = nestNestNest;
        nest[0] = nestNest;
        firstNest[0] = 2;
        secondNest[0] = 1;
        thirdNest[0] = 4;
        thirdNest[1] = nest;
        thirdNest[2] = 4;
        fourthNest[0] = 3;
        fifthNest[0] = 6;
        sixthNest[0] = 5;
        sixthNest[1] = 5;
        sixthNest[2] = 5;
        seventhNest[0] = 8;
        eightNest[0] = 7;
        ninthNest[0] = 10;
        tenthNest[0] = 9;
        tenthNest[1] = 9;
        tenthNest[2] = 9;
        mainOne[0] = firstNest;
        mainOne[1] = secondNest;
        mainOne[2] = thirdNest;
        mainOne[3] = fourthNest;
        mainOne[4] = fifthNest;
        mainOne[5] = sixthNest;
        mainOne[6] = seventhNest;
        mainOne[7] = eightNest;
        mainOne[8] = ninthNest;
        mainOne[9] = tenthNest;

        Integer[] expected = {2, 1, 4, 100, 4, 3, 6, 5, 5, 5, 8, 7, 10, 9, 9, 9};
        Integer[] outcome = flattener(mainOne);

        return Arrays.equals(outcome, expected);
    }

}
