#include<iostream>
using namespace std;
int index;
int *arr;
void Insert(){
	cout << "Enter the amount of element in your array:" << endl;
	cin >> index;
	arr = new int[index];
	for (int i = 0; i < index; i++){
		cin>>arr[i];
	}
}
void LinerSearch(int key){
	for (int i = 0; i < index; i++){
		if (key == arr[i]){
			cout << "Found!!!" << endl;
			exit(0);
		}
	}
	cout << "Number Not Found!!!" << endl;
}
int main(){
	Insert();
	LinerSearch(5);
}
