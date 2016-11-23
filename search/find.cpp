#include "stdafx.h"
#include <iostream>

using namespace std;

int main(void) {

	int index = -1, key, i;

	cout << "Enter key:";
	cin >> key;

	const int N = 10;
	int a[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (i = 0; i < N; i++) {
		if (key == a[i]) { index = i; break; }
	}

	if (index >= 0) {
		cout << "Found index: " << index << "\n";
	}
	else {
		cout << "Not found index\n";
	}
	system("pause");
	return 0;
}
