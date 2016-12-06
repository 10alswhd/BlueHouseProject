package com.funj.collections;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.function.Function;

/**
 * An immutable list which contains head and tail.
 * 
 * @author machine
 *
 * @param <T>
 */
public interface List<T> extends Iterable<T> {

	boolean isEmpty();

	T head();
	
	int length();

	List<T> tail();
	
	/**
	 * Default Iterator implementation
	 */
	default Iterator<T> iterator(){
		//TODO
		return null;
	}
	
	default List<T> prepend(final T element){
		return new Cons<>(element, this);
	}
	
	@SafeVarargs
	static <T> List<T> of(final T... elements) {
		Objects.requireNonNull(elements, "Invalid Parameter");
		List<T> list = Nil.instance();
		for(int i = elements.length - 1; i >= 0; i--){
			list = list.prepend(elements[i]);
		}
		return list;
	}
	
	static <T> List<T> empty(){
		return Nil.instance();
	}

	/**
	 * Cons class which contains head and tail. Cons will not be empty
	 * 
	 * @author machine
	 *
	 * @param <T>
	 */
	final class Cons<T> implements List<T> {
		private final T head;
		private final List<T> tail;
		private final int length;

		private Cons(final T head, final List<T> tail) {
			this.head = head;
			this.tail = tail;
			this.length = 1 + tail.length();
		}

		@Override
		public boolean isEmpty() {
			return false;
		}

		@Override
		public T head() {
			return head;
		}

		@Override
		public List<T> tail() {
			return tail;
		}
		
		@Override
		public int length() {
			return length;
		}
		
	}

	/**
	 * An Nil instance which defines nothing type. i.e. No values are available
	 * 
	 * @author machine
	 *
	 * @param <T>
	 */
	final class Nil<T> implements List<T> {

		private static final Nil<?> NIL_INSTANE = new Nil<>();

		private Nil() {

		}

		@SuppressWarnings("unchecked")
		public static <T> Nil<T> instance() {
			return (Nil<T>) NIL_INSTANE;
		}

		@Override
		public boolean isEmpty() {
			return true;
		}

		@Override
		public T head() {
			throw new NoSuchElementException("Head is Empty");
		}

		@Override
		public List<T> tail() {
			throw new NoSuchElementException("Tail is Empty");
		}

		@Override
		public int length() {
			return 0;
		}

	}

}
