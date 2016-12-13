// basic file operations
#include <iostream>
#include <fstream>
#include "optab.h"
#include "search_op.h"
#include "hexfunc.h"
#include "subtract_hex.h"
#include "add_hex.h"
#include "Pass2.h"
#include "Pass1.h"
#include "objectprog.h"
#include "input_prog.h"
using namespace std;
int main ()
{
    printf("*******************************************************************************\n");
    printf("**************************WELCOME TO ASSEMBLER*********************************\n");
    printf("*******************************************************************************\n");
    printf("\n");
    printf("CREATED BY:\n");
    printf("Shubham Kansal            11114043\n");
    printf("Siddhant Sonkar           11114044\n");
    printf("Surendra Kumar Gadewal    11114045\n");
    printf("Vishu Goyal               11114049\n");
    int swp;
    printf("\nPRESS\n1.To generate assembly program for finding nth Fibonacci\n");
    printf("2.To generate assembly program for checking whether a number is a Palindrome\n");
    scanf("%d",&swp);
    if(swp==1)
    fib();
    else if(swp==2)
    palindrome();   
    ofstream myfile;
    myfile.open("intermediate.txt");
    myfile.close();
    myfile.open("output.txt");
    myfile.close();
    start=false;
    base="";
    string line;
    locctr=0;
    symtab_ctr=0;
    addr="0";
    int lcount=0;//counts the no. of lines
    FILE* fptr;
    fptr=fopen("input.txt","r");

    while (fgets(buffer,256,fptr) != NULL)
  {
         lcount++;
         processline(buffer);
    }
    fclose(fptr);
    length=subtract_hex(addr,start_add);
    start=false;

    fptr=fopen("intermediate.txt","r");
    while (fgets(buffer,256,fptr) != NULL)
	{
        lcount++;
        processline_2(buffer);
    }
    fclose(fptr);
    return 0;
}
