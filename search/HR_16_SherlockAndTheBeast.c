#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <math.h>


using namespace std;

bool decentNumber(int x) { //only 3 or 5, number of 3s divisble by 5, number of 5s divisible by 3
    int numThree = 0;
    int numFive = 0;
    bool good = false;
    stringstream ss;//use stringstream to convert int to string
    ss << x;
    string str = ss.str();//convert x to string
    for (int i = 0; i < str.length(); i++) { //
        if (str[i] == '3') {
            good = true;
            numThree++;//counts number of 3s
        } else if (str[i] == '5') {
            good = true;
            numFive++;//counts number of 5s
        } else {
            return false;//exit
        }
    }

    if (numThree % 5 != 0){//number of 3s is divisible by 5
        return false;
    }
    if (numFive % 3 != 0){//number of 5s is divisible by 3
        return false;
    }

    return good;
}

int main() {
    int testCases, digits, largestGoodNumber, top, bottom;
    cin >> testCases;
    int answers[testCases];
    for (int i = 0 ; i < testCases ; i++) {
        largestGoodNumber = -1;
        cin >> digits;
        top = (int) pow (10, digits) - 1;//top number to search for, (2 digits would be 99)
        bottom = (int) pow (10, digits - 1);//bottom number to search for (2 digits would be 10)
        for (int k = bottom; k < top; k = k + 5){//do this for 5s
            if (decentNumber (k) == true && k > largestGoodNumber){//if good and bigger, make it the number to return
                largestGoodNumber = k;
            }


        }
        for (int k = bottom; k < top; k = k + 3){//do this for 3s
            if (decentNumber (k) == true && k > largestGoodNumber){//if good and bigger, make it the number to return
                largestGoodNumber = k;
            }


        }
        answers[i] = largestGoodNumber;
    }

    for (int i = 0 ; i < testCases ; i++) {
        cout << answers[i] << "\n";
    }

    return 0;
}
