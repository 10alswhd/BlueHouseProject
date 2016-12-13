#ifndef PASS1_H_INCLUDED
#define PASS1_H_INCLUDED
// basic file operations
#include"search_op.h"
#include"optab.h"
#include"add_hex.h"
#include"hexfunc.h"
#include"subtract_hex.h"
#include<iostream>
#include<cstdio>
#include<fstream>
#include<algorithm>
using namespace std;

void processword(string words[],int countWord);
void insert_symtab(string lab);

void processline(string s)
{
    bool flag_comment=false;
    string words[3];

    int len=s.length();
    char ch;
    string w="";
    int cword=0;        //count words of line....

    for(int i=0;i<=len-1;i++)
    {
        ch=s[i];
        if(ch=='\n')
             continue;
        if(ch=='.')             //flag_comment=true
        {
            if(w!="")
            {
                words[cword++]=w;
                w="";
                break;
            }
            else
            break;
        }                     //rest is comment portion
        if(cword==3)
                break;        //rest is considered to be comment...
        if(ch==32 && w!="")   //space
        {
            words[cword++]=w;
            w="";
        }
        else if(ch!=32)
        {
             w=w+ch;
        }
    }
    if(w!="")
    {
        words[cword++]=w;
        w="";
    }
    if(cword==1||cword==2 || cword==3)
        processword(words,cword);
}

void processword(string words[],int cword)
{

    store_count++;
    ofstream myfile;
    myfile.open ("intermediate.txt", ios::out | ios::app);

    string label="",operat="",operand="";

    if(cword==1 && words[0]=="RSUB")
    {
        myfile<<words[0]<<"  "<<addr<<endl;
        addr=addhex(addr,"3");
        store[store_count]=addr;
        return;
    }
    if(cword==2)        //no label
    {
        operat=words[0];
        operand=words[1];
    }
    else
    {
        label=words[0];
        operat=words[1];
        operand=words[2];
        insert_symtab(label);
        myfile<<label<<" ";
    }
    
    short code=0;
    char form;            //for format..
    int f;
    if(operat=="START")
    {
        start=true;
        addr=operand;
        start_add=operand;
        myfile<<operat<<" "<<operand<<" "<<addr;
        store[store_count]=addr;
    }
    else        //if not start
    {
        int aa,bb;
        string cc="";
        bool found=false;
        char qw=operat[0];    // qw is addressing type
        if(qw=='+')
        {
            found=true;     // FOR FORMAT 4
            operat=operat.substr(1);
        }
        bool find=false;
        find=search(operat);
        if(find==true)
        {
            form=temp.format; //OBJECT OF OPTABLE
            f=form-48;
            if(found==true && f==3)
            {
                form++;
                operat=qw+operat;
            }
            myfile<<operat<<" "<<operand<<" "<<addr;
            store[store_count]=addr;
            string ss="";
            ss=ss+form;
            addr=addhex(addr,ss);
        }
        else if(operat=="END")
            myfile<<operat<<" "<<operand;
        else if(operat=="RESW")
        {
            bb=0;
            //operand to integer...integer to hex...
            for(int dd=0;dd<operand.length();dd++)
            {
                qw=operand[dd];
                aa=qw-48;
                bb=bb*10+aa;
            }
            cc=tohexstr(3*bb);     // 3*bb because size of each word is 3 bytes...
            myfile<<operat<<" "<<operand<<" "<<addr;
            store[store_count]=addr;
            addr=addhex(addr,cc);
        }
        else if(operat=="RESB")
        {
            bb=0;
            //operand to integer...integer to hex...
            for(int dd=0;dd<operand.length();dd++)
            {
                qw=operand[dd];
                aa=qw-48;
                bb=bb*10+aa;
            }
            cc=tohexstr(bb);
            myfile<<operat<<" "<<operand<<" "<<addr;
            if(bb>4)
            myfile<<endl;
            store[store_count]=addr;addr=addhex(addr,cc);
        }
        else if(operat=="WORD")
        {
            bb=0;
            //operand to integer...integer to hex...
            cc="3";
            myfile<<operat<<" "<<operand<<" "<<addr;
            store[store_count]=addr;
            addr=addhex(addr,cc);
        }
        else if(operat=="BASE")
        {
           //assuming that after BASE there is a label as operand...
           myfile<<operat<<" "<<operand;
        }
        else if(operat=="BYTE")
        {
            char q=operand[0];
            if(q=='C')
            {
                 int qwerty=operand.length();
                 cc=tohexstr(qwerty-3);
                 myfile<<operat<<" "<<operand<<" "<<addr;
                 store[store_count]=addr;
                 addr=addhex(addr,cc);
            }
            else if(q=='X')
            {
                 int qwerty=operand.length();
                 cc=tohexstr((qwerty-3+1)/2);
                 myfile<<operat<<" "<<operand<<" "<<addr;store[store_count]=addr;
                 addr=addhex(addr,cc);
            }
        }
    }
    myfile<<endl;
    myfile.close();
}

void insert_symtab(string lab)
{
    SYMTAB[symtab_ctr].label=lab;            //symtab_ctr=SYMBOL COUNTER
    SYMTAB[symtab_ctr].address=addr;
    symtab_ctr++;
}

#endif
