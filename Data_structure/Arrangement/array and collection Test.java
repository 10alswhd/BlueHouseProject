import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Iterator;

/**
 * java array test 
 * @author Y.Hirano 
 */
public class TestArray {

    /**
     * main function
     */
    public static void main(String[] args)
    {
        // array
        ArrayTest();

        // collection
        ListTest();
        SetTest();
        HashTest();
    }

    /**
     * Use Array
     */
    public static void ArrayTest()
    {
        print("----- test array start -----");
        String strArr[] = new String[3];
        strArr[0] = "dollar";
        strArr[1] = "cent";
        strArr[2] = "yen";

        // output value
        for(String str:strArr)
        {
            print(str);    
        }
    }

    /**
     * Use List
     */
    public static void ListTest()
    {
        print("----- test list start -----");

        // Listは重複OKな配列
        List<String> array = new ArrayList<String>();
        array.add("Mac");
        array.add("Mac");
        array.add("Windows");
        array.add("Linux");
        array.add("Linux");
        array.add("Linux");

        // output value 
        for(String str:array)
        {
            print(str);
        }

        // iteratorでの出力
        Iterator<String> iter = array.iterator();
        print("--- output it ---");
        while(iter.hasNext()) 
        {
            String str = iter.next();
            print(str);
        }
    }

    /**
     * Use Set
     */
    public static void SetTest()
    {
        print("----- test set start -----");

        // Setは重複NGな配列 重複は無視される
        Set<String> set = new HashSet<String>();
        set.add("iphone");
        set.add("android");
        set.add("iphone");
        set.add("android");
        set.add("ios");

        // output value 
        for(String str:set)
        {
            print(str);
        }
    }

    /**
     * Use Hash
     */
    public static void HashTest()
    {
        print("----- test hash start -----");

        Map<String,Integer> hash = new HashMap<String, Integer>();
        hash.put("apple", 1);
        hash.put("grape", 2);
        hash.put("orange", 3);
        
        // output value 
        for(String key:hash.keySet())
        {
            int num = hash.get(key);
            print(key +":"+ num);
        }

        // iteratorでの出力
        Iterator<?> iter = hash.entrySet().iterator();
        print("--- output it ---");
        while(iter.hasNext()) 
        {
            Map.Entry<?,?> ent = (Map.Entry<?,?>)iter.next();
            Object key = ent.getKey();
            Object value = ent.getValue();
            print(key +":"+ value);
        }
    }

    /**
     * Output string value function
     * @param str
     */
    public static void print(String str)
    {
        System.out.println(str);
    }
}
