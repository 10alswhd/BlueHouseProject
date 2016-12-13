#include<iostream>
using namespace std;
int *arr;
int index;
int *temp;
int i = 0;
int num;
bool count1 = true;
bool count2 = true;
void LinearSearch(){
	if (count2){
		temp = arr;
		cout << "Enter the number you want to search:" << endl;
		cin >> num;
		count2 = false;
	}
	if (*temp != num){
		temp++;
		LinearSearch();
	}
	else{
		cout << "Found!!!" << endl;
		exit(0);
	}
}

int Insert(){
	if (count1){
		cout << "Enter the size of your array:" << endl;
		cin >> index;
		arr = new int[index];
		count1 = false;
	}
	if (i < index){
		cin >> arr[i];
		i++;
		Insert();
	}
	else{
		 LinearSearch();
	}
	return 0;
}
int j = 0;
void Print(){
	if (j < index){
		cout << arr[j] << endl;
		j++;
		Print();
	}
	else{
		exit(0);
	}
}
int main(){
	Insert();
	Print();
	LinearSearch();
}
