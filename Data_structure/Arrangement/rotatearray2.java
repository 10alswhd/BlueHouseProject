/*
1. create a k length temp int array to hold the last k int and copy over the values
2. switch the rest values in the original array
3. copy the values back to the array from temp
*/
public class Solution {
    public void rotate(int[] nums, int k) {
        int len = nums.length;
        k = k%len;
        int[] temp = new int[k];
        for(int i=0; i<k;i++) {
            temp[k-i-1] = nums[len-i-1]; 
        }
        for(int i=len-1-k; i>=0; i--) {
            nums[--len] = nums[i];
        }
        for(int i=0;i<temp.length; i++) {
            nums[i] = temp[i];
        }
    }
}
