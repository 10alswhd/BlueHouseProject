#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


void printArray(int *);

void replaceWrongPlaceByZero(int *);

int main() {


    int *numbers = new int[1000];
    char zn;
    int i = 0;
    while (cin >> zn) {
        if (zn >= '0' && zn <= '9') {
            numbers[i] = (int) (zn - '0');
            ++i;
        }
    }

    replaceWrongPlaceByZero(numbers);
    printArray(numbers);
    int maxIndex = 0;
    uint64_t max = 0, tmp = 0;
    for (int j = 0; j <= 988; j++) {

        if ( numbers[j] == 0 ) continue;
        if (tmp == 0 && numbers[j] != 0) {
            tmp = 1;
            for (int k = j; k <= j + 12; k++) {
                tmp *= numbers[k];
            }
            if (tmp > max) {
                max = tmp;
                maxIndex = j;
            }
        } else {
            if (numbers[j + 12] == 0) {
                tmp = 0;
                j += 12;
            } else {
                if (numbers[j - 1] != 0) {
                    tmp /= numbers[j - 1];
                } else {
                  cout  << "ola la " << j;
                }
                tmp *= numbers[j + 12];
                if (tmp > max) {
                    max = tmp;
                    maxIndex = j;
                }
            }
        }
    }

    cout << "\n \n " << max << "\n";
    
    delete[] numbers;
    return 0;

}

// complexity O(n)
void replaceWrongPlaceByZero(int *array) {
    int firstZero = -1;
    for (int j = 0; j < 1000; j++) {
        if (array[j] == 0) {
            if (firstZero == -1) {
                firstZero = j;
                continue;
            }
            if (j - firstZero < 13) {
                for (int k = firstZero; k < j; k++) {
                    array[k] = 0;
                }
            }
            firstZero = j;
        }
    }
}

void printArray(int *array) {
    for (int i = 0; i < 1000; i++) {
        if (i % 100 == 0 && i != 0) {
            cout << "\n";
        }
        cout << array[i];
    }
}
