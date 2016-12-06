#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

bool search(int value, int values[], int n){
    for (int i = 0; i < n; i++){
    if (values[i] == value){
        return true;
    }
    else{ 
        return false;
    }
}
    return false;
}
