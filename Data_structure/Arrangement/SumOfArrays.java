import java.util.Arrays;
public class recursiveSum {
	
	
	//independent method of 1d array sum
	public static int sumOne (int[] nums){
		return nums.length!=1?nums[nums.length-1]+sumOne(Arrays.copyOf(nums, nums.length-1)):nums[0];
	}
	
	
	//call of 1d array sum
	public static int sumTwo (int[] nums){
		return sumAll(nums, nums.length);
	}
	
	//helper method of 1d array sum;
	public static int sumAll(int[] nums, int n){
		return n!=1 ? nums[n-1] + sumAll(nums, n-1) : nums[0];
	}
	
	
	//sum of a ragged (or straight) 2d array, with reference to 1d array helper method;
	public static int sumArr(int[][] nums){
		return nums.length > 1 ? sumAll(nums[nums.length-1], nums[nums.length-1].length) + sumArr(Arrays.copyOf(nums, nums.length-1)) : sumAll(nums[0], nums[0].length);
	}
	
}
	
	
	//calls of methods
	public class tstt {

	public static void main(String[] args) {
		int[] list = {1,4,5,6,3,5,8,1};
		int[][] tlist = { {1, 2, 3},
						  {5, 6, 7},
						  {0, 8, 3} };
		
		int[][] zlist = { {0, 7, 8, 2},
						  {8, 9, 1},
						  {0, 1},
						  {9, 2, 3, 4},
						  {8, 2, 1} };
						  
						  
	    System.out.println(recursiveSum.sumArr(tlist));
	    //returns 35
		
		System.out.println(recursiveSum.sumArr(zlist));
		//returns 65
		
	}

}
