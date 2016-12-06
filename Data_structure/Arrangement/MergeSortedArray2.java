package leetcode.array;

/**
 * Solution: Merge from tail to head. We can't start from head because of overlap. 
 * We don't need to check if m >= 0, because we merge B to A, A's element already there.
 * 
 * @author jeffwan
 * @date Mar 8, 2014
 */
public class MergeSortedArray {
	
	// Refactor of first version(mostly on index)
	public void merge(int A[], int m, int B[], int n) {
		int index = m + n;
		while (m > 0 && n > 0) {
			if (A[m - 1] > B[n - 1]) {
				A[--index] = A[--m];
			} else {
				A[--index] = B[--n];
			}
		}
		
		while (n > 0) {
			A[--index] = B[--n];
		}
	}
	
	
	// First Version
	public static void merge2(int A[], int m, int B[], int n) {
		int i = m - 1, j = n - 1;
		
		while (i >= 0 && j >= 0) {
			int index = i + j + 1;
			
			if (A[i] >= B[j]) {
				A[index] = A[i];
				i--;
			} else {
				A[index] = B[j];
				j--;
			}
		}
		
		if (j >= 0) {
			while (j >= 0) {
				A[j] = B[j];
				j--;
			}
		}
    }
}
