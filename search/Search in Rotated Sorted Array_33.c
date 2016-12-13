/*北京-安子(86307667)的代码*/
int search(int A[], int n, int target) {
    int lower = 0;
    int upper = n - 1;
    while (lower <= upper) {
        int middle = (lower + upper) / 2;
        if (A[middle] == target) {
            return middle;
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
    return -1;
}

/*先找分界点再处理的丑陋代码*/
class Solution {
public:
    int search_rotated(int A[], int n) {
        int low = 0;
        int high = n-1;
        int mid;
        /*找到翻转点下标,345612找到4，如果是123则找到0*/
        while(low < high){
            if(A[low] < A[high]){
                return low;
            }
            mid = low + (high - low)/2;
            if(A[mid] < A[high])
                high = mid;
            else if(A[mid] >= A[low])
                low = mid + 1;
        }
        return low;
    }
    int search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int mid;
        int low = search_rotated(A, n);
        int high = (low + n - 1)%n;
        while(low != high){
            if(low < high)
                mid = (low + high)/2;
            else
                mid = ((low + high + n)/2)%n;
            if(A[mid] == target)
                return mid;
            else if(A[mid] < target)
                low = (mid + 1)%n;
            else
                high = mid;
        }
        if(A[low] == target)
            return low;
        else
            return -1;
    }
};
