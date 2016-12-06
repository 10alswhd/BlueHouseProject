#include <iostream>
#include <cstddef>
#include "linkedlist1.h"
using namespace std;


double NumberList::listToArray(double listArray, int &count)const{
	ListNode *nodePtr;
	nodePtr = head;

	for(int i=0; i< count; i++){
		listArray[i] = nodePtr->value;
		nodePtr = nodePtr->next;
	}

	return listArray;
}


int NumberList::countList(int &count) const{
	ListNode *nodePtr;
	nodePtr = head;

	while(nodePtr){
		count++;
		nodePtr = nodePtr->next;
	}
	return count;

}




void NumberList::appendNode(double num){
	ListNode *newNode;		//to point to a new node
	ListNode *nodePtr;		//to move through the list
	newNode = new ListNode;
	newNode->value = num;
	newNode->next = NULL;

	if (!head)
		head = newNode;
	else{
		nodePtr = head;
		while(nodePtr->next)
			nodePtr = nodePtr->next;

	nodePtr->next = newNode;
	}
}

void NumberList::displayList() const{
	ListNode *nodePtr;
	nodePtr = head;

	while(nodePtr){
		cout << nodePtr->value << endl;
		nodePtr = nodePtr->next;
	}
}


		


void NumberList::insertNode(double num){
	ListNode *newNode;
	ListNode *nodePtr;
	ListNode *previousNode = NULL;

	newNode = new ListNode;
	newNode->value = num;

	if(!head){
		head = newNode;
		newNode->next = NULL;
	}

	else{
		nodePtr = head;
		previousNode = NULL;

		while (nodePtr !=NULL && nodePtr->value < num){
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		if (previousNode == NULL){
			head = newNode;
			newNode->next = nodePtr;
		}

		else{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}
