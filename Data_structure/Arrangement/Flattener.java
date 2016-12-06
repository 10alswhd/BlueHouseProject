package intercom.flattener;

import java.util.LinkedList;
import java.util.List;

class Flattener {
			
	/*
	* Does the actual flattening. 
	* @param  nested an object array containing an arbitrary number of elements.
	* Each element is going to be either an integer or another object array
	*/
	public void flatten(Object[] nested, List<Integer> flat) {
		
		for(Object intOrArray : nested) {

			if(intOrArray instanceof Object[]) {
				flatten((Object[]) intOrArray, flat);
			}
			else {
				flat.add((Integer) intOrArray);
			}
		}
	}
	
	/*
	* Helper method. Returns a List of integers, the flattened list .
	* @param nested an object array containing an arbitrary number of elements.
	* Each element is going to be either an integer or another object array
	* @param flat a list of integers which is the flattened version of the input array, initially empty
	* @return a list of integers which is the flattened version of the input array
	*/
	public List<Integer> doFlat(Object[] nested, List<Integer> flat) {
		if(nested == null) return null;
		flatten(nested, flat);
		
		return flat;
	}
	
	
	/*
	 * Returns an integer array containing the elements of the  
	 * input list. It is used for compatibility with the JUnit's assertArrayEquals
	 * @param  list a list of integers
	 * @return      an integer array containing the elements of this list
	 */
	public Integer[] listToArr(List<Integer> list) {
		return list.toArray(new Integer[list.size()]);
	}
	
	public static void main(String[] args) {
		Flattener f = new Flattener();
		List<Integer> flat = new LinkedList<Integer>();
		System.out.println(f.doFlat(new Object[]{ 1, 2, new Object[]{ 3, 4, 5}, 6, 7}, flat));
	}
	
}
