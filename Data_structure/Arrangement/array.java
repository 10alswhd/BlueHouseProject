public class 배열{
  public static void main(String args[]){
    int a [] = new int[4];
    System.out.println("Array a length : " + a.length);
    for(int i = 0 ; i < a.length ; i++){
      a[i] = (i + 10);
    }
    
    for(int i = 0 ; i < a.length ; i++){
      System.out.println("a[" + i + "] : " + a[i]);
    }
    
  }
}
