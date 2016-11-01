void uphead(int a[], int k) {

	int v;

	v = a[k];

	a[0] = INT_MAX;

	while (a[k/2] <= v) {

		a[k] = a[k/2];

		k /= 2;

	}

	a[k] = v;

}

 

void downheap(int a[], int n, int k) {

	int i, v;

	v = a[k];

	while (k <= n/2) {

		i = k<<1;

		if (i < n && a[i] < a[i+1]) i++;

		if (v >= a[i]) break;

		a[k] = a[i];

		k = i;

	}

	a[k] = v;

}

 

void insert(int a[], int *n, int v) {

	a[++(*n)] = v;

	uphead(a, *n);

}

 

int extract(int a[], int *n) {

	int v = a[1];

	a[1] = a[(*n)--];

	downheap(a, *n, 1);

	return v;

}

 

void heap_sort(int a[], int n) {

	int i;

	int hn = 0;

	for (i = 1; i <= n; i++)

		insert(a, &hn, a[i]);

	for (i = hn; i >= 1; i--)

		a[i] = extract(a, &hn);

}
