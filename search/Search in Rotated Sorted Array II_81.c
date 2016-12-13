class Solution {
public:
    bool search_linear(int A[], int lower, int upper, int target){
        for(; lower <= upper; ++lower){
            if(A[lower] == target)
                return true;
        }
        return false;
    }
    bool search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int lower = 0;
        int upper = n - 1;
        while (lower <= upper) {
            int middle = (lower + upper) / 2;
            if(A[middle] == A[lower] && A[middle] == A[upper])
                return search_linear(A, lower, upper, target);
            if (A[middle] == target) {
                return true;
            } else if (A[middle] >= A[lower]) {
                if (A[lower] <= target && target < A[middle])
                    upper = middle - 1;
                else
                    lower = middle + 1;
            } else {
                if (A[middle] < target && target <= A[upper])
                    lower = middle + 1;
                else
                    upper = middle - 1;
            }
        }
        return false;
    }
};
