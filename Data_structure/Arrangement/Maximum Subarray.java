public int maxSubArray(int[] nums) {
        if (nums == null || nums.length == 0) {
            return Integer.MIN_VALUE;
        }

        int curSum = nums[0];
        int maxSum = nums[0];

        for (int i = 1; i < nums.length; i++) {
            curSum = Math.max(nums[i], nums[i] + curSum);
            maxSum = Math.max(maxSum, curSum);
        }
        return maxSum;
}
