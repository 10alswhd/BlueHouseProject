// ----------------------------------------------------------
/*
			Queue : Ryan 12/12/2013
				• Singly linked implementation
				• Lack of notes (ran out of time =(
*/
// ----------------------------------------------------------

// ----------------------------------------------------------
#include "queue.h"
#include <iostream>
#include <string>
#include <limits>
// ----------------------------------------------------------
using std::cout;	using std::string;
using std::endl;	using std::numeric_limits;
using std::cin;		using std::streamsize;
// ----------------------------------------------------------
void welcome();
// ----------------------------------------------------------
void process_queue(Queue<int>* q);
// ----------------------------------------------------------
int main()
{	
	welcome();	
	Queue<int>* que { new Queue<int>() };
	process_queue(que);
}
// --------------------------------------------------
void process_queue(Queue<int>* q)
{
	int choice{ 0 };
	char go_again{ 'y' };
	
	cout << "\nWhat would you like to do with this queue?\n\n";	
	
	while (tolower(go_again) == 'y')
	{
		cout << 
			"1. Enqueue           2. Dequeue\n"
			"3. Is it empty?      4. Size of queue\n"
			"5. Print queue       6. Quit\n\n"
			"choice >> ";

		cin >> choice;
		cout << '\n';

		int value{ 0 };
		bool b{ false };
		
		switch (choice)
		{
		case 1:
			cout << "Enter values you would like to store.\n"
				"value >> ";
			
			while (cin >> value)			
				q->enqueue(value);
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << '\n';
			break;
		case 2:
			b = q->dequeue(value);
			if (b)
				cout << "Dequeued value : " << value << "\n\n";
			else
				cout << "Failure.\n\n";
			break;
		case 3:
			cout << "Queue is empty : " << std::boolalpha << q->is_empty() << "\n\n";
			break;
		case 4:
			cout << "Current size of queue : " << q->queue_count() << "\n\n";
			break;
		case 5:
			q->print();
			break;
		case 6:
			go_again = 'n';
			break;			
		default:
			cout << "Try again.\n";
		};
	}

	cout << "Program terminating. Goodbye.\n\n";
}

// --------------------------------------------------
void welcome()
{
	const int s = 6;
	const string hello = '*' + string(s, ' ') + "Welcome to the Queue Program" + string(s, ' ') + '*';

	for (int columns = 0; columns < s * 2 + 3; ++columns) {

		if (columns == 0 || columns == s * 2 + 2)
			cout << string(hello.length(), '*') << endl;

		else if (columns == s + 1)
			cout << hello << endl;

		else
			cout << '*' << string(hello.length() - 2, ' ') << '*' << endl;

	}

}
// ----------------------------------------------------------
// end main.cpp
// ----------------------------------------------------------





 queue.h
// ----------------------------------------------------------
// queue.h
// ----------------------------------------------------------
#pragma once
// ----------------------------------------------------------
#include <iostream>

template <typename T>
class Queue
{
private:	
	struct Node								// sll
	{
		T item;								// stored data
		Node *next;							// pointer to next in list
		Node(const T& t, Node *const v)	
			: item{ t }, next{ v }
		{}
		Node()
			: item{}, next{ nullptr }
		{}

	};	
	int length;
	Node *front, *rear;
	
public:
	Queue()
		: length{ 0 }, front{ nullptr }, rear{ nullptr }
	{ }
	
	~Queue()
	{
		Node *temp{ nullptr };
		while (front)
		{
			temp = front;
			front = front->next;
			delete temp;
		}
	}	
	
	Queue(const Queue& q) 
		: length{ 0 } 
	{ }						// copy constructor
							// will stop gcc complaints

	Queue& operator=(const Queue& q) 
	{
		return *this;
	}						// copy assignment
							// will stop gcc complaints
	bool is_empty() const;
	int queue_count() const;
	bool enqueue(const T&);
	bool dequeue(T&);
	void print() const;
};
// ----------------------------------------------------------
template<typename T>
bool Queue<T>::is_empty() const
{
	return length == 0;
}
// ----------------------------------------------------------
template<typename T>
int Queue<T>::queue_count() const
{
	return length;
}
// ----------------------------------------------------------
template<typename T>
bool Queue<T>::enqueue(const T& val)
{	
	Node *n { new Node(val, nullptr) }; // making use of constructor with parameters

	if (!front)
		front = n;
	else
		rear->next = n;

	rear = n;

	++length;

	return true;
}
// ----------------------------------------------------------
template <typename T>
bool Queue<T>::dequeue(T& item)
{
	if (!front)
		return false;

	item = front->item;

	Node *temp{ front };

	front = front->next;	

	delete temp;			// delete previous first 

	if (length == 0)
		rear = nullptr;

	--length;

	return true;
}
// ----------------------------------------------------------
template <typename T>
void Queue<T>::print() const
{
	if (is_empty())
		std::cout << "List is empty\n\n";

	else
	{
		Node *t{ front };

		std::cout << "  |First Out|" << t->item << "| <-- ";

		t = t->next;

		while (t)
		{
			std::cout << "|" << t->item << "|" << "|";

			if (t->next)
				std::cout << " <-- ";

			t = t->next;
		}
		std::cout << "\n\n";
	}

}
// ----------------------------------------------------------
// end queue.h
// ----------------------------------------------------------
