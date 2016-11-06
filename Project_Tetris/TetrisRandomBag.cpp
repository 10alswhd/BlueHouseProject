#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 7

using namespace std;

class RandomBag
{
    int bloxPicked,ranNum;
    char bag[7];

public:
    RandomBag();
    char* emptyBag(char*);
    void fillBag();
    void isValid(char*);
};

RandomBag::RandomBag()
{
    bag[0] = 'o';
    bag[1] = 'i';
    bag[2] = 's';
    bag[3] = 'z';
    bag[4] = 'l';
    bag[5] = 'j';
    bag[6] = 't';
    srand(time(NULL));
}

char* RandomBag::emptyBag(char* returnedBag)
{
    
    bloxPicked = 0;
    while(bloxPicked < MAX)
    {
        ranNum = rand()% 7;
        if(bag[ranNum] != 'x')
        {
            cout << bag[ranNum];
            returnedBag[bloxPicked] = bag[ranNum];
            bag[ranNum] = 'x';
            bloxPicked++;
        }
    }
    cout << " ";
    return returnedBag;

}

void RandomBag::fillBag()
{
    bag[0] = 'o';
    bag[1] = 'i';
    bag[2] = 's';
    bag[3] = 'z';
    bag[4] = 'l';
    bag[5] = 'j';
    bag[6] = 't';
}

void RandomBag::isValid(char* bag)
{
    int counter = 0;
    bool o = false,i = false,s = false,z = false,l = false,j = false,t = false;
    for(counter = 0; counter < MAX; counter++)
    {
        switch(bag[counter])
        {
            case('o'):
            {
                o = true;
                break;
            }
            case('i'):
            {
                i = true;
                break;
            }
            case('s'):
            {
                s = true;
                break;
            }
            case('z'):
            {
                z = true;
                break;
            }
            case('l'):
            {
                l = true;
                break;
            }
            case('j'):
            {
                j = true;
                break;
            }
            case('t'):
            {
                t = true;
                break;
            }
            default:
                break;
        }
    }
    if(o && i && s && z && j && l && t)
        cout << " Valid ";
    else
        cout << " NOT Valid";
}

int main()
{
    char checkBag[7];
    int numBags,i;
    RandomBag rb;

    cout << "How many Tetris bags do you want to empty?";
    cin  >> numBags;
    for(i = 0; i < numBags; i++)
    {
        rb.emptyBag(checkBag);
        rb.fillBag();
        rb.isValid(checkBag);
    }
    cout << "\nPrinted " << numBags << " Tetris bag(s) out..";
    return 0;
}
