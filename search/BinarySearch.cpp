#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int bsearch(vector<int> a, int left, int right, int what) {
 	if (right < left) return -1;	
	int middle = left + (right - left)/2;

	if (a[middle] < what) {
		return bsearch(a, left, middle-1, what);
	}
	else if (a[middle] > what) {
		return bsearch(a, middle + 1, right, what);
	}
	return middle;
}

int main(int, char**) {
	vector<int> a(10);
	for (int i = 0; i < a.size(); i++) {
		a[i] = 10 - i;
		cout << a[i] << " ";
	}
	cout << endl;
	for (int i = 16; i >= 0; i--)
		cout << i << " at " << bsearch(a, 0, a.size()-1, i) << endl;

	return 0;
}
