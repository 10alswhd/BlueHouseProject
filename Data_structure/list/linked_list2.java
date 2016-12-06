import java.lang.IndexOutOfBoundsException;

public class Main {
  public static void main(String args[]) {
    LinkedList<Integer> l = new LinkedList<Integer>();
    l.add(4);
    l.add(0);
    l.add(9);
    l.add(131, 1);
    l.add(12);
    l.add(151, 5);
    for (int i = 0; i < l.size(); ++i) {
      System.out.println(l.get(i));
    }
  }
}

class LinkedList<T> {
  private class Node {
    public T data;
    public Node next = null;
    public Node(T data) {
      this.data = data;
    }
  }
  Node head = new Node(null);
  int size = 0;

  public LinkedList() {

  }

  public int size() {
    return size;
  }

  public boolean add(T e) {
    Node n = head;
    for (; n.next != null; n = n.next);
    n.next = new Node(e);
    ++size;
    return true;
  }

  public boolean add(T e, int i) {
    if (i < 0 || i > size) {
      throw new IndexOutOfBoundsException();
    }
    if (i == size) {
      add(e);
      return true;
    }
    Node n = head;
    for (int j = 0; j < i; j++) {
      n = n.next;
    }
    Node next = n.next;
    n.next = new Node(e);
    n.next.next = next;
    ++size;
    return true;
  }

  public T get(int i) {
    if (i < 0 || i >= size) {
      throw new IndexOutOfBoundsException();
    }
    Node n = head;
    for (int j = 0; j < i + 1; j++) {
      n = n.next;
    }
    return n.data;
  }
}
