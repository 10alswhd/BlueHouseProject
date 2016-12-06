import java.io.PrintWriter;
import java.util.Scanner;

//import java.text.DecimalFormat;
//import java.text.DecimalFormatSymbols;
//import java.util.Locale;



public class Main {
    public static class Tree{
        public Tree left = null;
        public Tree right = null;
        public int data;
        Tree(int data){
            this(null, null, data);
        }
        Tree(Tree l, Tree r, int data){
            left = l;
            right = r;
            this.data = data;
        }
    }    
    
    static Tree[] persArray;
    static int[] arr;
    
    static Tree formTree(int l, int r){
        if(l > r) return null;
        if(l == r) return new Tree(arr[l]);
        return new Tree(formTree(l, (l+r)/ 2), formTree((l+r)/2+1, r),-1);
    }
    
    static int getElem(Tree tree, int l, int r, int elem){
        if(l == r) return tree.data;
        int mid = (l + r) / 2;
        if(elem > mid){
            return getElem(tree.right, mid + 1, r, elem);
        }
        else{
            return getElem(tree.left, l, mid, elem);
        }
    }
    
    static Tree cloneTree(Tree tree, int l, int r, int change, int val){
        if(l > r) return null;
        if(l == r) return new Tree(val);
        int mid = (l + r)/ 2;
        if(change > mid){
            return new Tree(tree.left,
                    cloneTree(tree.right,mid + 1, r, change, val), tree.data);
        }
        else{
           return new Tree(cloneTree(tree.left, l, mid, change, val),
                    tree.right, tree.data); 
        }
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
//        DecimalFormatSymbols dotSplit = new DecimalFormatSymbols(Locale.ENGLISH);
//        DecimalFormat mantFormat = new DecimalFormat("0.0000",dotSplit);
        int n;
        n = in.nextInt();
        arr = new int[n];
        for(int i = 0; i < n; i++) arr[i] = in.nextInt();
        int m;
        m = in.nextInt();
        persArray = new Tree[m + 1];
        persArray[0] = formTree(0, n - 1);
        int top = 0;
        for(int i = 0; i < m; i++){
            String input = in.next();
            if(input.charAt(0) == 'c'){
               top++;
               persArray[top] = cloneTree(persArray[in.nextInt() - 1], 0, n - 1,
                       in.nextInt() - 1, in.nextInt()); 
            }           
            else{
                out.println(getElem(persArray[in.nextInt() - 1], 0, n - 1, 
                        in.nextInt() - 1));
            }
        }
        out.flush();
    }

}
