#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "linkedlist1.h"
using namespace std;

int main(){

	const int MAX_SIZE = 1000000;

	double insert;
	double append;

	int count =0;
	double listValue;

	double listArray[MAX_SIZE];

	int listSize =0;

	srand(time(NULL)+getpid());

	NumberList list;

	cout << "How many numbers would you like to add to your list?" << endl;
	cout << "No more than 1,000,000 please!" << endl;
	cin >> listSize;

	for(int i=0; i<listSize; i++){
		listValue=(rand() % 1000000);
		list.appendNode(listValue);
	}

	list.countList(count);

	list.displayList();

	cout << "The list has " << count << " nodes." << endl;

	return 0;
}
