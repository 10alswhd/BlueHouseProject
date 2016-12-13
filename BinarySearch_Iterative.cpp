/*
http://ideone.com/RqdJ4b
*/

#include <iostream>
using namespace std;

int BinarySearch(int a[], int len, int item){
	int l = 0, r = len-1;
	while(l <= r){
		int mid = l + (r -l) / 2;
		if(item == a[mid])
			return mid;
		else if(item < a[mid]){
			r = mid -1;
		}
		else
			l = mid + 1;
	}
	return -1;
}
int main() {
	// your code goes here
	int a[] = {1, 5, 9 , 10, 45, 48, 95, 100};
	int len = sizeof(a)/sizeof(a[0]);
	int item = 100;
	int index =  BinarySearch(a, len, item);
	if(index == -1)
		cout << "Item " << item << " not found!" <<endl;
	else
		cout << "Item " << item << " found at index : " << index << endl;
	return 0;
}
Raw
 BinarySearch_Recursive.cpp
/*
http://ideone.com/FTNZKp
*/

#include <iostream>
using namespace std;

int BinarySearch(int a[], int l, int r, int item){
	int mid = l + (r - l) / 2;
	if(l <= r){
		if(item == a[mid])
			return mid;
		else if(item < a[mid])
			return BinarySearch(a, l, mid-1, item);
		else
			return BinarySearch(a, mid+1, r, item);
	}
	else
	return -1;
}
int main() {
	// your code goes here
	int a[] = {1, 5, 9 , 10, 45, 48, 95, 100};
	int len = sizeof(a)/sizeof(a[0]);
	int item = 95;
	int index =  BinarySearch(a, 0, len, item);
	if(index == -1)
		cout << "Item " << item << " not found!" <<endl;
	else
		cout << "Item " << item << " found at index : " << index << endl;
	return 0;
}
