#ifndef SEARCH_OP_H_INCLUDED
#define SEARCH_OP_H_INCLUDED
#include <iostream>
# include "optab.h"
using namespace std;
bool search(string operat)
{
    
    //SEARCHING!!
    bool found=false;
    for(int i=0;i<optab_length;i++)
    {
        if(OPTAB[i].mnemonic==operat)
        {
               temp=OPTAB[i];
               return true;
        }
    }
    return false;
}

#endif 
