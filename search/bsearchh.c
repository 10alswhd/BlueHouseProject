int 
binary_search_first_position(int *A, int n, int target) {
	int end[2] = { -1, n };
	while (end[0] + 1 < end[1]) {
		int mid = (end[0] + end[1]) / 2;
		int sign = (unsigned)(A[mid] - target) >> 31;
		end[1-sign] = mid;
	}
	int high = end[1];
	if (high >= n || A[high] != target)
		return -high - 1;
	else
		return high;
}

int 
binary_search_last_position(int *A, int n, int target) { 
	int end[2] = { -1, n };
	while (end[0] + 1 < end[1]) {
		int mid = (end[0] + end[1]) / 2;
		int sign = (unsigned)(target - A[mid]) >> 31;
		end[sign] = mid;
	}
	int low = end[0];
	if (low < 0 || A[low] != target)
		return -low - 2;
	else
		return low;
}
