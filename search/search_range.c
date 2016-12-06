bool binsearch(int *nums, int numsSize, int target, int *range) {
    int start = 0, end = numsSize - 1;
    int mid;
    
    while (start <= end) {
        mid = (start + end) / 2;
        if (nums[mid] == target) {
            range[0] = start;
            range[1] = mid;
            range[2] = end;
            return true;
        } else if (nums[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    range[0] = -1;
    range[1] = -1;
    range[2] = -1;
    return false;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int *nums, int numsSize, int target, int *returnSize) {
    int *res = malloc(2 * sizeof(int));
    
    *returnSize = 2;
    res[0] = -1;
    res[1] = -1;
    
    if (nums[0] == target && nums[numsSize - 1] == target) {
        res[0] = 0;
        res[1] = numsSize - 1;
        return res;
    }
    
    int range[3];
    bool ch = binsearch(nums, numsSize, target, range);
    if (!ch) {
        return res;
    }
    
    int start, mid, end;
    
    start = range[0];
    end = range[1];
    if (nums[start] == target && nums[end] == target) {
        res[0] = start;
    } else {
        while (start < end) {
            mid = (start + end) / 2;
            if (nums[mid] == target) {
                end = mid;
            } else {
                start = mid + 1;
            }
            // printf("First half mid: %d\n", mid);
        }
        res[0] = start;
    }
    
    start = range[1];
    end = range[2];
    if (nums[start] == target && nums[end] == target) {
        res[1] = end;
    } else {
        while (start < end) {
            mid = (start + end) / 2;
            if (nums[mid] == target) {
                start = mid + 1;
            } else {
                end = mid;
            }
            // printf("Second half mid: %d\n", mid);
        }
        res[1] = nums[end] == target ? end : end - 1;
    }

    return res;
}
