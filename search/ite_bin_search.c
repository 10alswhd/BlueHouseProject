int binarySearchIte(int *a, int start, int end, int value) {

	while ((end - start) > 1) {
		int cursor = start + (end - start) / 2;
		if (a[cursor] == value) {
			return cursor;
		}

		if (a[cursor]<value) {
			start = cursor;
		}
		else if (a[cursor]>value) {
			end = cursor;
		}
	}

	return -1;

}
