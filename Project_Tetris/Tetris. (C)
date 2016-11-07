#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STEPS 6

int coloane[5] = {0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100};
int a[8][8];
int i = 7, j = 4;
int centru_i = 7, centru_j = 4;
long k;
int piesa, poz;



/*
=============PIESA============
0 - linie (3 puncte) 	...
1 - colt  (3 puncte) 	.:
2 - patrat (2x2)  		::
3 - punct				.
==============================
============POZITIE===========
0 - .: 		...		::		.
1 - :.		:		::		.
2 - :'		...		::		.
3 - ':		:		::		.
==============================
*/

//functie de initializare a matricei
void completMatrix(){
	int k, l;
	for (k = 0; k < 8; k++)
		for (l = 0; l < 8; l++)
			a[k][l]=0;
}

//functie de afisare a pieselor pe matrice
void printMatrix() {
	int k, l;

	for (k = 0; k < 8; k++) {
		PORTA = ~(1 << k);
		PORTC = 0x00;
		for (l = 0; l < 8; l++) {
			PORTC |= a[k][l] << l;
		}
		_delay_ms(2);
	}
}

//functie pentru a depista cand s-au umplut o linie si trebuie stearsa, iar piesele de deasupra sa coboare
int isLine(){
	int ii,c=0;;
	for (i=0;i<8;i++){
		c=0;
		for(j=0;j<8;j++)
			if (a[i][j]==1)
				c++;
		if (c==8){
			for(j=0;j<8;j++)
				a[i][j]=0;
			break;
		}
	}

	if (i<7 && c==8){
		for(ii=i+1;ii<7;ii++)
			for (j=0;j<8;j++)
				a[ii-1][j]=a[ii][j];
		for (j=0;j<8;j++)
			a[7][j]=0;
		isLine();
		return 1;
	}
	return 0;
}


// functie de stingere a ledurilor (folosita la deplasare si rotatie) in functie de centrul piesei
int ledOFF(int centru_i,int centru_j){
	a[centru_i][centru_j]=0;
	if (piesa==0){		//linie
		if(poz==0 || poz==2){
			a[centru_i][centru_j+1]=0;
			a[centru_i][centru_j-1]=0;
		}
		else{
			a[centru_i-1][centru_j]=0;
			a[centru_i+1][centru_j]=0;
		}
	}
	if (piesa==1){		//tip L
		if(poz==0){
			a[centru_i][centru_j-1]=0;
			a[centru_i+1][centru_j]=0;
		}
		else if(poz==1){
			a[centru_i][centru_j+1]=0;
			a[centru_i+1][centru_j]=0;
		}
		else if (poz==2){
			a[centru_i][centru_j+1]=0;
			a[centru_i-1][centru_j]=0;
		}
		else if (poz==3) {
			a[centru_i][centru_j-1]=0;
			a[centru_i-1][centru_j]=0;
		}
	}

	if (piesa==2){ //patrat
		a[centru_i][centru_j-1]=0;
		a[centru_i+1][centru_j-1]=0;
		a[centru_i+1][centru_j]=0;
	}

	if (piesa==3){ //punct
			a[centru_i][centru_j]=0;
	}
	return 0;
}


//functie de aprindere a ledurilor (folosita la deplasare si rotatie) in functie de centrul piesei
int ledON(int centru_i,int centru_j){
	a[centru_i][centru_j]=1;
	if (piesa==0){		//figura de tip linie
		if(poz==0 || poz==2){
			a[centru_i][centru_j+1]=1;
			a[centru_i][centru_j-1]=1;
		}
		else{
			a[centru_i-1][centru_j]=1;
			a[centru_i+1][centru_j]=1;
		}
	}
	if (piesa==1){		//figura de tip L
		if(poz==0){
			a[centru_i][centru_j-1]=1;
			a[centru_i+1][centru_j]=1;
		}
		else if(poz==1){
			a[centru_i][centru_j+1]=1;
			a[centru_i+1][centru_j]=1;
		}
		else if (poz==2){
			a[centru_i][centru_j+1]=1;
			a[centru_i-1][centru_j]=1;
		}
		else if (poz==3){
			a[centru_i][centru_j-1]=1;
			a[centru_i-1][centru_j]=1;
		}
	}
	if (piesa==2){  //patrat
		a[centru_i][centru_j-1]=1;
		a[centru_i+1][centru_j-1]=1;
		a[centru_i+1][centru_j]=1;
	}
	if (piesa==3){  //punct
		a[centru_i][centru_j]=1;
	}
	return 0;
}


//functie care deseneaza piesa in noua pozitie daca aceasta este una valabila. In cazul in care pozitia nu este permisa, functia returneaza 1
int drawImage(int i,int j,int centru_i,int centru_j){
	if (piesa==0) {		//linie
		if(poz==0 || poz==2){
			a[centru_i][centru_j+1]=0;
			a[centru_i][centru_j-1]=0;
			if (a[centru_i+i][centru_j+j]==1 || a[centru_i+i][centru_j+1+j]==1 || a[centru_i+i][centru_j-1+j]==1 ||
				centru_i+i <0 || centru_j+j>6 || centru_j+j<1)
				return 1;

			a[centru_i][centru_j]=0;
			a[centru_i][centru_j+1]=0;
			a[centru_i][centru_j-1]=0;

			centru_i+=i;
			centru_j+=j;

			a[centru_i][centru_j]=1;
			a[centru_i][centru_j+1]=1;
			a[centru_i][centru_j-1]=1;
		}
		else{
			if (a[centru_i+i][centru_j+j]==1 || a[centru_i-1+i][centru_j+j]==1 || a[centru_i+1+i][centru_j+j]==1  ||
				centru_i+i<1 || centru_j+j >7 || centru_j+j<0)
				return 1;

			a[centru_i][centru_j]=0;
			a[centru_i-1][centru_j]=0;
			a[centru_i+1][centru_j]=0;

			centru_i+=i;
			centru_j+=j;

			a[centru_i][centru_j]=1;
			a[centru_i-1][centru_j]=1;
			a[centru_i+1][centru_j]=1;
		}
	}
	if (piesa==1){		//tip L
		if(poz==0){
			if (a[centru_i+i][centru_j+j]==1 || a[centru_i+i][centru_j-1+j]==1 || a[centru_i+1+i][centru_j+j]==1 ||
				centru_i+i<0 || centru_j+j>7 || centru_j+j<1)
				return 1;

			a[centru_i][centru_j]=0;
			a[centru_i][centru_j-1]=0;
			a[centru_i+1][centru_j]=0;

			centru_i+=i;
			centru_j+=j;

			a[centru_i][centru_j]=1;
			a[centru_i][centru_j-1]=1;
			a[centru_i+1][centru_j]=1;
		}
		else if(poz==1){
			if (a[centru_i+i][centru_j+j]==1 ||
				a[centru_i+i][centru_j+1+j]==1 || a[centru_i+1+i][centru_j+j]==1 ||
				centru_i+i<0 || centru_j+j>6 || centru_j+j<0)
				return 1;

			a[centru_i][centru_j]=0;
			a[centru_i][centru_j+1]=0;
			a[centru_i+1][centru_j]=0;

			centru_i+=i;
			centru_j+=j;

			a[centru_i][centru_j]=1;
			a[centru_i][centru_j+1]=1;
			a[centru_i+1][centru_j]=1;
		}
		else if (poz==2){
			if (a[centru_i+i][centru_j+j]==1 || a[centru_i+i][centru_j+1+j]==1 || a[centru_i-1+i][centru_j+j]==1 ||
				centru_i+i<1 || centru_j+j>6 || centru_j+j<0)
				return 1;

			a[centru_i][centru_j]=0;
			a[centru_i][centru_j+1]=0;
			a[centru_i-1][centru_j]=0;

			centru_i+=i;
			centru_j+=j;

			a[centru_i][centru_j]=1;
			a[centru_i][centru_j+1]=1;
			a[centru_i-1][centru_j]=1;
		}
		else if (poz==3){
			if (a[centru_i+i][centru_j+j]==1 || a[centru_i+i][centru_j-1+j]==1 || a[centru_i-1+i][centru_j+j]==1 ||
				centru_i+i<1 || centru_j+j>7 || centru_j+j<1)
				return 1;

			a[centru_i][centru_j]=0;
			a[centru_i][centru_j-1]=0;
			a[centru_i-1][centru_j]=0;

			centru_i+=i;
			centru_j+=j;

			a[centru_i][centru_j]=1;
			a[centru_i][centru_j-1]=1;
			a[centru_i-1][centru_j]=1;
		}
	}
	if (piesa==2) {//patrat

		if (a[centru_i+i][centru_j+j]==1 || a[centru_i+i][centru_j-1+j]==1 || a[centru_i+1+i][centru_j+j]==1 || a[centru_i+1+i][centru_j-1+j]==1 ||
			centru_i+i<0 || centru_j+j>7 || centru_j+j<1)
			return 1;

		a[centru_i][centru_j]=0;
		a[centru_i][centru_j-1]=0;
		a[centru_i+1][centru_j-1]=0;
		a[centru_i+1][centru_j]=0;

		centru_i+=i;
		centru_j+=j;

		a[centru_i][centru_j]=1;
		a[centru_i][centru_j-1]=1;
		a[centru_i+1][centru_j]=1;
		a[centru_i+1][centru_j-1]=1;
	}
	if (piesa==3) {		//punct
		if (a[centru_i+i][centru_j+j] == 1 ||
			centru_i+i<0 || centru_j+j>7 || centru_j+j<0)
			return 1;

			a[centru_i][centru_j]=0;

			centru_i+=i;
			centru_j+=j;

			a[centru_i][centru_j]=1;
	}
	return 0;
}


//functie de start a jocului
void start(){
	// daca se apasa unul din butoane se incepe jocul
	while (1){
		if (!(PIND & (1 << PD4)) || !(PIND & (1 << PD5)) || !(PIND & (1 << PD6))){
			_delay_ms(15);
			completMatrix();
			break;
		}
	}
}

// buton deplasare dreapta - PD5
// buton deplasare stanga - PD6
// buton rotire figura - PD4

int main(){
	// setam toti pinii portului C ca pini de iesire
	DDRA = 0xFF;
	DDRC = 0xFF;

	PORTA = 0x00;
	PORTC = 0xFF;

	//totii pinii pentru intrare
	DDRD = 0x00;
	PORTD = 0XFF;

	completMatrix();

	start();
	srand(k);
	piesa = rand() % 4; // se alege random prima piesa
	srand(k / 2);
	poz = rand() % 4;  // se alege random o pozitie pentru piesa
	long timp = 0;


	while(1){
		if (!(PIND & (1 << PD6))) {
			_delay_ms(100);
			ledOFF(centru_i,centru_j);
			if (drawImage(0, 1, centru_i, centru_j) == 1)
				ledON(centru_i,centru_j);
			else
				centru_j++;
		} if (!(PIND & (1 << PD5))) {
			_delay_ms(100);
			ledOFF(centru_i,centru_j);
			if (drawImage(0, -1, centru_i, centru_j) == 1)
				ledON(centru_i, centru_j);
			else
				centru_j--;
		} else if (!(PIND & (1 << PD4))) {
			_delay_ms(100);
			ledOFF(centru_i,centru_j);
			poz=(poz+1)%4;
			if (drawImage(0,0,centru_i,centru_j) == 1) {
				poz=(poz+3)%4;
				ledON(centru_i,centru_j);
			}
		}

		printMatrix();

		if (timp >= 30) {
			ledOFF(centru_i,centru_j);
			if (drawImage(-1,0,centru_i,centru_j)==1) {
				ledON(centru_i,centru_j);
				isLine();
				if (a[7][4]==1 || a[7][3]==1 || a[7][5]==1) {
					timp = 0;

					while (1) {
						timp++;
						if (timp >= 50)
							if (!(PIND & (1 << PD6)) || !(PIND & (1 << PD4)) || !(PIND & (1 << PD5))){
								_delay_ms(15);
								start();
								break;
							}
					}

				}
				srand((centru_i + centru_j + piesa + poz));
				piesa=rand() % 4;
				srand((piesa + poz));
				poz=rand() % 4;
				centru_i = 7;
				centru_j = 4;
			}
			else
				centru_i--;
			timp = 0;
		}
		printMatrix();
		timp++;
	}

	return 0;
}
