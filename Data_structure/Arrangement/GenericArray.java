public class GenericArray {
  public static void main(String[] args) {
    Pair<String, String> arr[] = new Pair<String, String>[10]; // BOOM!
  }
}
