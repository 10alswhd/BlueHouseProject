#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <dos.h>
#include <stdbool.h>
using namespace std;

void gotoxy(int h, int w);
char getSuit(int num);
char getPicture(int num);
int getValue(int num);
void printCard(int cards[52], int index);
void shuffleDeck(int cards[52], int picked[52]);
void header();
void dealFiveCards(int cards[52], int totals[5], int bets[5], int hands[5][5]);
void scoreboard(int bets[5], int& pot);
void sortHands(int hands[5][5], int index);
int checkHand(int hands[5][5], int cards[52], int ranks[5], int player);


int main(void)
{
	int playerStatus[5] = { 'a', 'a', 'a', 'a', 'a' };
	int hands[5][5];
	int ranks[5] = { 0 };
	int bets[5] = { 0 };
	int pot = 0;


	//// formatting
	//char char1 = 3;
	//char char2 = 4;
	//char char3 = 5;
	//char char4 = 6;
	////color
	//system("color 1B");
	//gotoxy(32, 12);
	//cout << char1 << " " << char2 << " " << "  POKER  " << " " << char3 << " " << char4;
	//Sleep(2500);
	//system("cls");

	boolean flag = true;
	char yesorno;

	while (flag)
	{
		//play intro sound
		Beep(1000, 100);
		Beep(2000, 100);
		Beep(3000, 100);
		Beep(2000, 100);
		Beep(1000, 100);

		//variables and arrays

		int cardNum = 16;
		int cards[52], picked[52] = { 0 }, totals[5] = { 0 }, number;

		shuffleDeck(cards, picked);
		header();
		dealFiveCards(cards, totals, bets, hands);
		gotoxy(0, 10);

		scoreboard(bets, pot);

		//sort arrays
		for (int i = 0; i < 5; i++)
			sortHands(hands, i);

		gotoxy(0, 10);
		cout << "Hand type: " << checkHand(hands, cards, ranks, 1);

		gotoxy(0, 11);
		cout << "Hand type: " << checkHand(hands, cards, ranks, 1);

		gotoxy(0, 12);
		cout << "Hand type: " << checkHand(hands, cards, ranks, 2);

		gotoxy(0, 13);
		cout << "Hand type: " << checkHand(hands, cards, ranks, 3);

		gotoxy(0, 14);
		cout << "Hand type: " << checkHand(hands, cards, ranks, 4);

		//repeat or no
		gotoxy(0, 15);
		cout << "Play again? y/n                       ";
		cin >> yesorno;

		if (yesorno == 'n')
		{
			flag = false;
			system("cls");
			cout << "Thank you for playing." << endl;
		}
		else
			system("cls");

	}

	system("pause");
	return 0;
}

void gotoxy(int h, int w)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		COORD pos = { h, w };
		SetConsoleCursorPosition(hConsole, pos);
	}
	return;
}

char getSuit(int num)
{
	char ch;
	switch (num / 13)
	{
	case 0:	ch = 3;
		break;
	case 1:	ch = 4;
		break;
	case 2:	ch = 5;
		break;
	case 3:	ch = 6;
		break;
	}
	return ch;
}

char getPicture(int num)
{
	int modvalue = num % 13;
	char pic = ' ';
	if (modvalue == 0)
		pic = 'A';
	if (modvalue == 10)
		pic = 'J';
	if (modvalue == 11)
		pic = 'Q';
	if (modvalue == 12)
		pic = 'K';
	return pic;
}

int getValue(int num)
{
	int modvalue = num % 13;
	int value = 0;

	if (modvalue == 0)
		value = 13;
	else
		value = modvalue;

	return value;
}

void printCard(int cards[52], int index)
{
	if (getValue(cards[index]) == 13)
		cout << left << setw(2) << 'A';
	else if ((getValue(cards[index]) <= 10) && ((getValue(cards[index]) > 0)))
		cout << left << setw(2) << (getValue(cards[index]) + 1);
	else
		cout << left << setw(2) << getPicture(cards[index]);

	cout << setw(2) << getSuit(cards[index]);
}

void shuffleDeck(int cards[52], int picked[52])
{
	srand(time(NULL));

	for (int i = 0; i < 52; i++)
	{
		int number = rand() % 52;

		while (picked[number])
			number = rand() % 52;

		cards[i] = number;
		picked[number] = 1;
	}
}

void header()
{
	//shows players
	gotoxy(0, 0);
	for (int i = 0; i < 5; i++)
	{
		gotoxy(i * 15, 0);
		cout << "P" << i + 1;
	}
}

void dealFiveCards(int cards[52], int totals[5], int bets[5], int hands[5][5])
{
	int rounds = 0;

	//deals initial cards, left to right
	for (int i = 0; i < 5; i++)
	{
		gotoxy(i * 15, 1);
		printCard(cards, i);
		hands[0][i] = cards[i];

	}
	for (int i = 5; i < 10; i++)
	{
		gotoxy((i - 5) * 15, 2);
		printCard(cards, i);
		hands[1][i - 5] = cards[i];

	}
	for (int i = 10; i < 15; i++)
	{
		gotoxy((i - 10) * 15, 3);
		printCard(cards, i);
		hands[2][i - 10] = cards[i];
	}
	for (int i = 15; i < 20; i++)
	{
		gotoxy((i - 15) * 15, 4);
		printCard(cards, i);
		hands[3][i - 15] = cards[i];

	}
	for (int i = 20; i < 25; i++)
	{
		gotoxy((i - 20) * 15, 5);
		printCard(cards, i);
		hands[4][i - 20] = cards[i];
	}
}

void scoreboard(int bets[5], int& pot)
{
	gotoxy(0, 17);
	cout << "      SCOREBOARD      ";
	gotoxy(0, 18);
	cout << "----------------------" << endl;
	gotoxy(0, 19);
	cout << "TOTAL BETS:" << pot;
	int num = 20;
	for (int i = 0; i < 5; i++)
	{
		gotoxy(6, num);
		cout << "P" << i + 1 << ": ";
		cout << bets[i];
		num++;
	}
}

void sortHands(int hands[5][5], int index)
{
	int i, j, first, temp;
	for (i = 4; i > 0; i--)
	{
		first = 0;                 // initialize to subscript of first element
		for (j = 1; j <= i; j++)   // locate smallest between positions 1 and i.
		{
			if (hands[index][j] < hands[index][first])
				first = j;
		}
		temp = hands[index][first];   // Swap smallest found with element in position i.
		hands[index][first] = hands[index][i];
		hands[index][i] = temp;
	}
}

int checkHand(int hands[5][5], int cards[52], int ranks[5], int player)
{

	int sameValue = 0;
	int tempHand[5];

	for (int r = 0; r < 5; r++)
		tempHand[r] = cards[(r * 5) + player];

	char c1 = getSuit(tempHand[0]);
	char c2 = getSuit(tempHand[1]);
	char c3 = getSuit(tempHand[2]);
	char c4 = getSuit(tempHand[3]);
	char c5 = getSuit(tempHand[4]);
		
	for (int startIndex = 0; startIndex < 5; ++startIndex)
	{
		int smallestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < 5; ++currentIndex)
		{
			if ((getValue(tempHand[currentIndex])) < (getValue(tempHand[smallestIndex])))
				smallestIndex = currentIndex;
		}

		std::swap(tempHand[startIndex], tempHand[smallestIndex]);
	}

	int v1 = getValue(tempHand[0]);
	int v2 = getValue(tempHand[1]);
	int v3 = getValue(tempHand[2]);
	int v4 = getValue(tempHand[3]);
	int v5 = getValue(tempHand[4]);


	// if sequence
	if ((v1) && (v1 == (v2 - 1)) && (v1 == (v3 - 2)) && (v1 == (v4 - 3)) && (v1 ==  (v5 - 4)))
		return 7;
	else if ((c1 == c2) && (c1 == c3) && (c1 == c4) && (c1 == c5))
		return 5;
	else if ((v1 == v2) || (v1 == v3) || (v1 == v4) || (v1 == v5) || (v2 == v3) || (v2 == v4) || (v2 == v5) || (v3 == v4) || (v3 == v5) || (v4 == v5))
		return 6;

		return 0;


	
	



	return 0;

}

