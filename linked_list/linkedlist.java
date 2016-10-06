import java.util.Collection;

/**
 * This is a circular, singly linked list.
 */
public class LinkedList<E> implements List<E> {

  protected Node<E> head;
  protected Node<E> tail;

	protected int size;

	public LinkedList()
	{
		size = 0;
	}
	
	@Override
	public void add(E e) {
		Node<E> newNode = new Node<E>(e);
		
		if (head == null)
		{
			head = newNode;
			head.setNext(head);
			tail = head;
		}
		else
		{
			tail.setNext(newNode);
			tail = newNode;
			tail.setNext(head);
		}
		size++;
	}

	/*
	 * You will want to look at Iterator, Iterable, and 
	 * how to use a for-each loop for this method.
	 */
	@Override
	public void addAll(Collection<? extends E> c) {
		for (E element : c)
		{
			add(element);
		}
	}

	@Override
	public void clear() {
		// Set head, tail to null and allow java to garbage collect the nodes
		head = null;
		tail = null;
		size = 0;
	}

	@Override
	public boolean contains(Object o) {
		if (o == null) return false;
		
		Node<E> temp = head;
		do
		{
			if (temp.getData().equals(o))
			{
				return true;
			}
			temp = temp.getNext();
		}
		while (temp != head);
		
		return false;
	}

	@Override
	public E get(int index) throws IndexOutOfBoundsException{
		if (index >= size || index < 0) throw new IndexOutOfBoundsException();
		
		int a = 0;
		Node<E> temp = head;
		while (a != index)
		{
			temp = temp.getNext();
			a++;
		}
		return temp.getData();
	}

	@Override
	public int indexOf(Object o) {
		int index = 0;
		Node<E> temp = head;
		// do-while because it is a circular linked list (instead of while)
		do
		{
			if (temp.getData().equals(o))
			{
				return index;
			}
			index++;
			temp = temp.getNext();
		}
		while (temp != head);
		return -1;
	}

	@Override
	public boolean isEmpty() {
		return size == 0;
	}

	@Override
	public E remove(int index) throws IndexOutOfBoundsException{
		if (index >= size || index < 0) throw new IndexOutOfBoundsException();
		
		Node<E> prev = null, temp = head;
		E data;
		int a = 0;
		
		// Set temp to the node to be deleted
		while(a != index)
		{
			temp = temp.getNext();
			prev = (prev == null) ? head : prev.getNext();
		}

		data = temp.getData();
		
		// If it's the head node, update head
		if (prev == null)
		{
			head = temp.getNext();
		}
		else
		{
			prev.setNext(temp.getNext());
		}
		
		size--;
		return data;		
	}

	@Override
	public E remove(Object o) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public E set(int index, E e) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return 0;
	}

	/*
	 * The following methods are for grading. Do not modify them, and you do not
	 * need to use them.
	 */

	public void setSize(int size) {
		this.size = size;
	}

	public Node<E> getHead() {
		return head;
	}

	public void setHead(Node<E> head) {
		this.head = head;
	}
}
