package intercom.flattener;

import java.util.LinkedList;

import org.junit.Assert;
import org.junit.Test;

public class FlattenerTest {

	@Test
	public void test() {
		Flattener f = new Flattener();
				
		Assert.assertArrayEquals(
				"1d", 
				f.listToArr(f.doFlat(new Object[]{1, 2, 3}, 
						new LinkedList<Integer>())), 
				new Integer[] {1, 2, 3});
		
		Assert.assertArrayEquals(
				"1d with String", 
				f.listToArr(f.doFlat(new Object[]{1, 2, 3}, 
						new LinkedList<Integer>())), 
				new Integer[] {1, 2, 3});
	
		Assert.assertArrayEquals(
				"2d", 
				f.listToArr(f.doFlat(new Object[]{ 1, 2, new Object[]{ 3, 4, 5}, 6, 7}, 
						new LinkedList<Integer>())), 
				new Integer[] {1, 2, 3, 4, 5, 6, 7});
		
		Assert.assertArrayEquals(
				"2d more complex", 
				f.listToArr(f.doFlat(new Object[]{ new Object[] {1, 2}, 2, new Object[]{ 3, 4, 5}, 6, 7}, 
						new LinkedList<Integer>())), 
				new Integer[] {1, 2, 2, 3, 4, 5, 6, 7});
		
		Assert.assertArrayEquals(
				"3d", 
				f.listToArr(f.doFlat(new Object[]{ 1, 2, new Object[] { 3, new Object[] {4, 5, 6}} }, 
						new LinkedList<Integer>())), 
				new Integer[] {1, 2, 3 ,4 ,5, 6});
		
		Assert.assertNull(
				"null", 
				f.doFlat(null, 
						new LinkedList<Integer>()));
		
		Assert.assertArrayEquals(
				"empty", 
				f.listToArr(f.doFlat(new Object [] {}, 
						new LinkedList<Integer>())), 
				new Integer[] {});
		
		}
}
