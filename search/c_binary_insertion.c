void binary_insertion_sort(long A[], size_t a_length) {
	long val;
	int low, high, mid, insert_at;
	
	/* for every element but the first */
	for (int i = 1; i < a_length; i++) {
		short found = 0;

		high = i - 1;
		low = 0;
		val = A[i];

		while (!found) {
			mid = (high + low) / 2;

			/* if we've found the proper slot */
			if ((high - low) <= 1 && A[low] <= val) {
				found = 1;
				insert_at = low + 1;
			/* if mid _is_ the value */
			} else if (val == A[mid]) {
				found = 1;
				insert_at = mid + 1;
			/* if the val is larger than any others */
			} else if (val >= A[high]) {
				found = 1;
				insert_at = i;
			/* if the value is smaller than any others */
			} else if (A[low] > val) {
				found = 1;
				insert_at = 0;
			/* if the value is between low and mid, 
			   our new search range is low - mid */
			} else if (A[low] < val && val < A[mid]) {
				high = mid;
			/* if the value is between mid and high, 
			   our new search range is mid - high */
			} else if (A[mid] < val && val < A[high]) {
				low = mid;
			}
		   
		}	

		/* we've found where it goes, now put it there */
		int j = i;
		for (; j > insert_at; j--)
			A[j] = A[j - 1];
		A[j] = val;
	}
}
