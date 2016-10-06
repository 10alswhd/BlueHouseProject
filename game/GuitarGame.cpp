/*	Paul Booth
Guitar Hero clone in ascii. (mary had a little lamb)
*/

#include <iostream>
#include <windows.h>
#define G 392
#define A 440
#define B 494
#define D 587
#define E 659

#define quarternote 200
#define stepsleep 50
#define gameheight 23
#define slowness 2
using namespace std;


struct note {
	int x;
	int freq;
	int length;
	int y;
};
void gotoxy(int x, int y);
void clrscr();
void setTextColor(int fg, int bg);
struct note greenNote(int posy);
struct note redNote(int posy);
struct note yellowNote(int posy);
struct note blueNote(int posy);
struct note orangeNote(int posy);

struct note greenNote(int posy, int l);
struct note redNote(int posy, int l);
struct note yellowNote(int posy, int l);
struct note blueNote(int posy, int l);
struct note orangeNote(int posy, int l);


struct note notes[] = {
	yellowNote(1),
	redNote(2),
	greenNote(3),
	redNote(4),
	yellowNote(5),
	yellowNote(6),
	yellowNote(7,2 * quarternote),
	redNote(9),
	redNote(10),
	redNote(11,2 * quarternote),//10
	greenNote(13),
	blueNote(14),
	blueNote(15,2 * quarternote),
	yellowNote(17),
	redNote(18),
	greenNote(19),
	redNote(20),
	yellowNote(21),
	yellowNote(22),
	yellowNote(23),//20
	yellowNote(24),
	redNote(25),
	redNote(26),
	yellowNote(27),
	redNote(28),
	greenNote(30,4 * quarternote),
	//end mary had a little lamb
	orangeNote(35),
	blueNote(36),
	yellowNote(37),
	redNote(38),//30
	greenNote(39),
	{ 3,800,4 * quarternote,41 }


};
int numofnotes = 32;
int main(void)
{
	for (int i = 0; i<numofnotes; i++) {
		notes[i].y *= slowness;
		//slow down song- make it more playable

	}
	int currenty = -gameheight, deadnum = -1, score = 0;

	int keys[] = { 49,50,51,52,53 };//controls for frets
	int colors[] = { FOREGROUND_GREEN | FOREGROUND_INTENSITY,//green
		FOREGROUND_RED | FOREGROUND_INTENSITY,//red
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, //yellow
		FOREGROUND_BLUE | FOREGROUND_INTENSITY, //blue
		FOREGROUND_RED | FOREGROUND_BLUE };//purple
	while (currenty<notes[numofnotes - 1].y + gameheight) {
		currenty++;
		Sleep(100);
		clrscr();

		int i = 0;
		boolean beeped = false;//note at strum point
		for (i = deadnum + 1; i<numofnotes&&notes[i].y - currenty<gameheight; i++) {
			setTextColor(0, 0);
			gotoxy(2 * notes[i].x, currenty - notes[i].y + gameheight - 1);//write over old note spot
			cout << ' ' << '\n';
			setTextColor(colors[notes[i].x - 1], 0);//set correct color
			gotoxy(2 * notes[i].x, currenty - notes[i].y + gameheight);
			cout << char(15) << '\n';//draw note

			if (notes[i].y == currenty) {	//note at strum point	
				if (GetAsyncKeyState(VK_BACK)<0) {//strumming
					if (GetAsyncKeyState(keys[notes[i].x - 1])<0) {//correct note pressed
						Beep(notes[i].freq, notes[i].length);
						score += int(notes[i].length / quarternote);
					}
					else
						score--;//deducted for missed fret

				}
				else score--;//missed the note
				deadnum = i;//most recent passed note
				beeped = true;
			}
		}
		if (!beeped) {
			if (GetAsyncKeyState(VK_BACK)>0) score--;//no note and strummed
		}

		gotoxy(0, gameheight);
		setTextColor(15, 17);
		cout << "|-XOXOXOXOX-|\n";

		setTextColor(17, 15);//draw P if button is pressed
		for (int j = 0; j<5; j++) {
			gotoxy(j * 2 + 2, gameheight - 1);
			if (GetAsyncKeyState(keys[j]))
			{
				cout << "P\n";
			}
			else {
				cout << " \n";
			}
		}
		//show score
		gotoxy(15, gameheight);
		setTextColor(10, 9);
		cout << "Score:" << score << "\n";

		//song over
		if (deadnum + 1 >= numofnotes) {
			setTextColor(colors[1], 0);
			gotoxy(0, notes[deadnum].y - currenty + gameheight);
			cout << ' ' << char(176) << char(219) << char(177) << char(219) << char(178) << char(219) << char(178) << char(219) << char(177) << char(219) << char(176) << ' ' << "\n";
		}


	}
	setTextColor(15, 0);
	cout << "YOU ROCK!!!";

	return 0;
}
struct note greenNote(int posy) {
	struct note beep = { 1,G,quarternote,posy };

	return beep;
}
struct note redNote(int posy) {
	struct note beep = { 2,A,quarternote,posy };

	return beep;
}
struct note yellowNote(int posy) {
	struct note beep = { 3,B,quarternote,posy };

	return beep;
}
struct note blueNote(int posy) {
	struct note beep = { 4,D,quarternote,posy };

	return beep;
}
struct note orangeNote(int posy) {
	struct note beep = { 5,E,quarternote,posy };

	return beep;
}
struct note greenNote(int posy, int l) {
	struct note beep = { 1,G,l,posy };

	return beep;
}
struct note redNote(int posy, int l) {
	struct note beep = { 2,A,l,posy };

	return beep;
}
struct note yellowNote(int posy, int l) {
	struct note beep = { 3,B,l,posy };

	return beep;
}
struct note blueNote(int posy, int l) {
	struct note beep = { 4,D,l,posy };

	return beep;
}
struct note orangeNote(int posy, int l) {
	struct note beep = { 5,E,l,posy };

	return beep;
}
void gotoxy(int x, int y)//moves cursor to position on screen
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clrscr()
{
	system("cls");
}
void setTextColor(int fg, int bg) {//sets foreground and background text colors
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, fg | bg << 4);

}
