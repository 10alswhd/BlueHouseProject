#include <stdio.h>
#include <pthread.h>
#include "conio.h"
#include <stdlib.h>

//Function prototypes
int rand_range(int min, int max);
void drawField(void);
void drawLblock();
void drawLineBlock(void);
void spawnShape(int x);
void checkWin(void);

int a = 5, i, k = 0, j = 0, turn = 3, lock = 0, rotate = 0;
int field[21][10];
pthread_t pth0;
pthread_t pth1;
pthread_t pth2;
pthread_t pth3;
int speed = 400000000;

void *lineBlock(void *arg)
{
    while(1)
    {   
        if(rotate % 2 == 0)
        {   
            field[k][a] = 1;
            field[1 + k][a] = 1;
            field[2 + k][a] = 1;
            field[3 + k][a] = 1;
            k++;
            nanosleep((const struct timespec[]){{0, speed}}, NULL);     
            if(field[3 + k][a] != 0)
            {
                field[k - 1][a] = 2;
                field[k][a] = 2;
                field[k + 1][a] = 2;
                field[k + 2][a] = 2;
                break;
            }
            if(turn == 1 && a != 0 && field[3 + k][a - 1] == 0 &&         field[2 + k][a - 1] == 0 && field[1 + k][a - 1] == 0 && field[0 + k][a - 1] == 0)
        {
                a--;
                if(field[k - 1][a + 1] != 2)
                    field[k - 1][a + 1] = 0;
                if(field[k][a + 1] != 2)
                    field[k][a + 1] = 0;
                if(field[k + 1][a + 1] != 2)
                    field[k + 1][a + 1] = 0;
                if(field[k + 2][a + 1] != 2)
                    field[k + 2][a + 1] = 0;
                turn = 0;
        }
        else if(turn == 2  && a !=9 && field[3 + k][a + 1] == 0 && field[2 + k][a + 1] == 0 && field[1 + k][a + 1] == 0 && field[0 + k][a + 1] == 0)        
        {
                a++;
                if(field[0 + k - 1][a - 1] != 2)
                    field[0 + k - 1][a - 1] = 0;
                if(field[1 + k - 1][a - 1] != 2)
                    field[1 + k - 1][a - 1] = 0;
                if(field[2 + k - 1][a - 1] != 2)
                    field[2 + k - 1][a - 1] = 0;
                if(field[3 + k - 1][a - 1] != 2)
                    field[3 + k - 1][a - 1] = 0;
                turn = 0;
        }
        if(field[0 + k - 1][a] != 2)
            field[0 + k - 1][a] = 0;
        if(field[1 + k - 1][a] != 2)
            field[1 + k - 1][a] = 0;
        if(field[2 + k - 1][a] != 2)
            field[2 + k - 1][a] = 0;
        if(field[3 + k - 1][a] != 2)
            field[3 + k - 1][a] = 0;
        }
        else
        {
            field[k][a - 1] = 1;
            field[k][a] = 1;
            field[k][a + 1] = 1;
            field[k][a + 2] = 1;
            k++;
        nanosleep((const struct timespec[]){{0, speed}}, NULL);     
        if(field[k][a] != 0 || field[k][a - 1] != 0 || field[k][a + 1] != 0 || field[k][a + 2] != 0)
        {
            field[k - 1][a - 1] = 2;
            field[k - 1][a] = 2;
            field[k - 1][a + 1] = 2;
            field[k - 1][a + 2] = 2;
            break;
        }
        if(turn == 1 && a - 1 != 0 && field[3 + k][a - 1] == 0 && field[2 + k][a - 1] == 0 && field[1 + k][a - 1] == 0 && field[0 + k][a - 1] == 0)
        {
                a--;
                if(field[0 + k - 1][a + 1] != 2)
                    field[0 + k - 1][a + 1] = 0;
                if(field[0 + k - 1][a + 2] != 2)
                    field[0 + k - 1][a + 2] = 0;
                if(field[0 + k - 1][a  + 3] != 2)
                    field[0 + k - 1][a + 3] = 0;
                if(field[0 + k - 1][a  + 4] != 2)
                    field[0 + k - 1][a + 4] = 0;
                turn = 0;
        }
        else if(turn == 2  && a + 2 !=9 && field[3 + k][a + 1] == 0 && field[2 + k][a + 1] == 0 && field[1 + k][a + 1] == 0 && field[0 + k][a + 1] == 0)        
        {
                a++;
                if(field[0 + k - 1][a - 1] != 2)
                    field[0 + k - 1][a - 1] = 0;
                if(field[0 + k - 1][a - 2] != 2)
                    field[0 + k - 1][a - 2] = 0;
                if(field[0 + k - 1][a - 3] != 2)
                    field[0 + k - 1][a - 3] = 0;
                if(field[0 + k - 1][a - 4] != 2)
                    field[0 + k - 1][a - 4] = 0;
                turn = 0;
        }
        if(field[0 + k - 1][a - 1] != 2)
            field[0 + k - 1][a - 1] = 0;
        if(field[0 + k - 1][a] != 2)
            field[0 + k - 1][a] = 0;
        if(field[0 + k - 1][a + 1] != 2)
            field[0 + k - 1][a + 1] = 0;
        if(field[0 + k - 1][a + 2] != 2)
            field[0 + k - 1][a + 2] = 0;

    }
}
k = 0;
a = 5;
speed = 400000000;
checkWin();
rotate = 0; 
spawnShape(rand_range(1, 3));
}

void *squareBlock(void *arg)
{
    while(1)
    {
        field[0 + k][a] = 1;
        field[1 + k][a] = 1;
        field[0 + k][a + 1] = 1;
        field[1 + k][a + 1] = 1;
        k++;
        nanosleep((const struct timespec[]){{0, speed}}, NULL);     
        if(field[1 + k][a] != 0 || field[1 + k][a + 1] != 0)
    {
        field[0 + k - 1][a] = 2;
        field[1 + k - 1][a] = 2;
        field[0 + k - 1][a + 1] = 2;
        field[1 + k - 1][a + 1] = 2;
        break;
    }
    if(turn == 1 && a != 0 && field[1 + k][a - 1] == 0 && field[0 + k][a - 1] == 0)
    {
        a--;
        if(field[0 + k - 1][a + 1] != 2)
            field[0 + k - 1][a + 1] = 0;
        if(field[1 + k - 1][a + 1] != 2)
            field[1 + k - 1][a + 1] = 0;
        if(field[0 + k - 1][a + 2] != 2)
            field[0 + k - 1][a + 2] = 0;
        if(field[1 + k - 1][a + 2] != 2)
            field[1 + k - 1][a + 2] = 0;
        turn = 0;
    }
    else if(turn == 2 && a + 1 != 9 && field[1 + k][a + 2] == 0 && field[0 + k][a + 2] == 0)        
    {
        a++;
        if(field[0 + k - 1][a - 1] != 2)
            field[0 + k - 1][a - 1] = 0;
        if(field[1 + k - 1][a - 1] != 2)
            field[1 + k - 1][a - 1] = 0;
        if(field[0 + k - 1][a - 2] != 2)
            field[0 + k - 1][a - 2] = 0;
        if(field[1 + k - 1][a - 2] != 2)
            field[1 + k - 1][a - 2] = 0;
            turn = 0;           
    }
    if(field[0 + k - 1][a] != 2)
    field[0 + k - 1][a] = 0;
    if(field[1 + k - 1][a ] != 2)
    field[1 + k - 1][a] = 0;
    if(field[0 + k - 1][a + 1] != 2)
    field[0 + k - 1][a + 1] = 0;
    if(field[1 + k - 1][a + 1] != 2)
    field[1 + k - 1][a + 1] = 0;        
}
k = 0;
a = 5;
speed = 400000000;
checkWin();
spawnShape(rand_range(1, 3));
}
void *LBlock(void *arg)
{
    while(1)
    {       
    field[0 + k][a] = 1;
    field[1 + k][a] = 1;
    field[2 + k][a] = 1;
    field[2 + k][a + 1] = 1;
    k++;
    nanosleep((const struct timespec[]){{0, speed}}, NULL);     
    if(field[2 + k][a] != 0 || field[2 + k][a + 1] != 0)
    {
        field[0 + k - 1][a] = 2;
        field[1 + k - 1][a] = 2;
        field[2 + k - 1][a] = 2;
        field[2 + k - 1][a + 1] = 2;
        break;
    }
    if(turn == 1 && a != 0)
    {
        if(field[2 + k][a - 1] == 0 && field[1 + k][a - 1] == 0 && field[0 + k][a - 1] == 0)
        {
            a--;
            if(field[0 + k - 1][a + 1] != 2)
                field[0 + k - 1][a + 1] = 0;
            if(field[1 + k - 1][a + 1] != 2)
                field[1 + k - 1][a + 1] = 0;
            if(field[2 + k - 1][a + 1] != 2)
                field[2 + k - 1][a + 1] = 0;
            if(field[2 + k - 1][a + 2] != 2)
                field[2 + k - 1][a + 2] = 0;
            turn = 0;
        }
    }
    else if(turn == 2 && a + 1 != 9)        
    {
        if(field[0 + k][a + 1] == 0 /*&& field[1 + k][a + 1] == 0*/ && field[2 + k][a + 2] == 0)
        {
            a++;
            if(field[0 + k - 1][a - 1] != 2)
                field[0 + k - 1][a - 1] = 0;
            if(field[1 + k - 1][a - 1] != 2)
                field[1 + k - 1][a - 1] = 0;
            if(field[2 + k - 1][a - 1] != 2)
                field[2 + k - 1][a - 1] = 0;
            if(field[2 + k - 1][a - 2] != 2)
                field[2 + k - 1][a - 2] = 0;
            turn = 0;
        }
    }
    if(field[0 + k - 1][a] != 2)
    field[0 + k - 1][a] = 0;
    if(field[1 + k - 1][a] != 2)
    field[1 + k - 1][a] = 0;
    if(field[2 + k - 1][a] != 2)
    field[2 + k - 1][a] = 0;
    if(field[2 + k - 1][a + 1] != 2)
    field[2 + k - 1][a + 1] = 0;        
}
k = 0;
a = 5;
speed = 400000000;
checkWin();
spawnShape(rand_range(1, 3));
}




void *inputThread(void *arg) //Thread to handle input
{
char input;
while(1)
{   
    fflush(stdin);
    input = getch();
    fflush(stdin);
    if(input == 'a')
        turn = 1;
    else if(input == 'd')
        turn = 2;
    else if(input == 's')
        speed = 150000000;
    else if(input == 'w')
    rotate++;
}    
}

int main(void)
{   
int gameOver = 0; //Variable to keep track of game state

srand(time(NULL)); //seed randomizer with time

for(i = 0; i < 10; i++) //Set last (invisible) row of matrix to 1's.
field[19][i] = 1;

pthread_create(&pth0,NULL, inputThread,"foo"); //Start input thread

spawnShape(rand_range(1,3)); // Spawn first tetromino

while(gameOver == 0) // Main loop that draws the grid at around 60 fps
{       
    system("clear");        
    drawField();
    nanosleep((const struct timespec[]){{0, 160000000L}}, NULL);
}   
return 0;
}

void drawField(void)
{
int i, a;
printf("________________\n");
for(i = 0; i < 19; i++)
{
    printf("|*|");
    for(a = 0; a < 10; a++)
    {
        if(field[i][a] == 1 || field[i][a] == 2)
            printf("O");
        else
            printf(" ");
    }
    printf("|*|\n");
}           
printf("----------------\n");
}


int rand_range(int min, int max)//Returns a random integer in the specified range
{
return rand() % (max - min + 1) + min;
}

void spawnShape(int x) //Function that starts threads to draw tetrominos
{
if(x == 1)
    pthread_create(&pth1,NULL,lineBlock,"foo");
else if(x == 2)
    pthread_create(&pth2,NULL,squareBlock,"foo");
else if(x == 3)
    pthread_create(&pth3,NULL,LBlock,"foo");
}

void checkWin(void)
{
int fieldtemp[20][10];
int i, a, count = 0, count2 = 0;

for(i = 0; i < 19; i++)
{
    count = 0;
    for(a = 0; a < 10; a++)
        if(field[i][a] == 2)
            count++;            
    if(count == 10)
    {
        count2++;
        for(a = 0; a < 10; a++)
                field[i][a] = 0;
    }                   
}
if(count2 > 0)
    for(i = 0; i < 20; i++)
    {
        for(a = 0 ;a < 10; a++)
        {
            fieldtemp[i][a] = field[i][a];
            field[i][a] = 0;
            field[i][a] = fieldtemp[i][a];
        }
    }           
}
