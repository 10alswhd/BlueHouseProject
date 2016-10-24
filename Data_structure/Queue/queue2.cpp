#include <iostream>
#include <queue>

using namespace std;


int main()
{
	int auxiliar = 0;
	
	queue<int> fila;

	fila.push(10);
	fila.push(20);

	cout << fila.size() << '\n';
	cout << "Queue back is: " << fila.back() << '\n';


	while(!fila.empty())
	{
		auxiliar += fila.front();
		fila.pop();
	}


	cout << "Soma de todos elementos da fila foi de " << auxiliar << '\n';

}
