#ifndef PASS2_H_INCLUDED
#define PASS2_H_INCLUDED
// basic file operations
#include"search_op.h"
#include"optab.h"
#include"add_hex.h"
#include"hexfunc.h"
#include"subtract_hex.h"
#include<iostream>
#include<cstdio>
#include<fstream>
using namespace std;

void processword_2(string words[],int countWord);
void processline_2(string s); 

void processline_2(string s)
{
    bool flag_comment=false;
    string words[5];
    
    //Initialization
    int len=s.length();
    char ch;
    string w;
    w="";
    int countWord=0;//count words of line....

    for(int i=0;i<len-1;i++)
    {
        ch=s[i];
        if(ch==32 && w!="")//space
        {
            words[countWord]=w;
            countWord++;
            w="";
        }
        else if(ch!=32)
        {
             w=w+ch;
        }
        // We have already eliminate other conditions
    }
    if(w!="")
    {
        words[countWord]=w;
        w="";
        countWord++;
    }
    processword_2(words,countWord);
    if(countWord==0)
    {
        ofstream myfile;
        myfile.open ("output.txt", ios::out | ios::app);
        myfile<<endl;
        myfile.close();
    }    
}

void processword_2(string words[],int countWord)
{
    string address,code;
    ofstream myfile;
    myfile.open ("output.txt", ios::out | ios::app);

    string label="",operat="",operand="",net2="";
    int n=0,i=0,x=0,b=0,p=0,e=0,fg=0;
    bool dobase=false;
    if(countWord==2)
    {
        string trybase="";
        if(words[0]=="BASE")
        {
            trybase=words[1];
            int j;
            for(j=0;j<symtab_ctr;j++)
            {
                if(trybase == SYMTAB[j].label)
                {
                    break;
                }
            }
            base=SYMTAB[j].address;
        }
    }
    if(countWord==3)        //no label
    {
        operat=words[0];
        operand=words[1];
        address=words[2];
    }
    else
    {
        label=words[0];
        operat=words[1];
        operand=words[2];
        address=words[3];
    }
    char form;        //for format..
    if(operat=="START")
    {
       // Write nothing
    }
    string foradd="",mid="0",disp="";
    int t;
    string net;    //net operand...
    bool found=false;
    e=0;
    char qw=operat[0];
    if(qw=='+')
    {
        e=1;
        found=true;
        operat=operat.substr(1);
    }
    if(countWord==2 && words[0]=="RSUB")
    {
         myfile<<"4F0000";
         fg=1;
    }    
    if(operat=="BYTE")
    {
         if(operand[0]=='C')
         {
               for(int k=2;k<operand.length()-1;k++)
               {
                   char rr=operand[k];
                   myfile<<tohexstr((int)rr);
                   fg=1;
               }
         }
         else if(operand[0]=='X')
         {
               for(int k=2;k<operand.length()-1;k++)
               {myfile<<operand[k];
               fg=1;}
         }
    }
    if(operat=="BASE")
    {
        if(operand[0]=='#' && (operand[0]>=48 && operand[0]<=57))//number
        {
               // net=tohexstr(operand);
        }
        else
        {
            int j;
            for(j=0;j<symtab_ctr;j++)
            {
                if(operand == SYMTAB[j].label)
                break;
            }
            net=SYMTAB[j].address;
            base=net;
        }
        return;
    }
    bool find=search(operat);
    if(find==true)
    {
         form=temp.format;
         if(found==true && form=='3')
         {
             form++;
         }
         code=temp.opcode;
         //-->decide n,i-->code to code-->TWO HALF BYTES...
         qw=operand[0];
         bool printmid=true;
         if(found==true)         //FORMAT 4....
         {
                p=0;
                e=1;
                net=operand;
                if(qw=='#')//immediate...
                {
                     n=0;
                     i=1;
                     net=operand.substr(1);
                     char cha=net[0];
                     if(!(cha>='0' && cha<='9')) // label after # or + with # with variable case or modify record
                     {
                          mod_record[mod_count]=addhex(address,"1");
                          while(mod_record[mod_count].length()<6)
                               mod_record[mod_count]='0'+mod_record[mod_count];
                          mod_record[mod_count]="M"+mod_record[mod_count]+"05";
                          mod_count++;
                          int j;
                          for(j=0;j<symtab_ctr;j++)
                          {
                              if(net == SYMTAB[j].label)
                              {break;}
                          }
                          net=SYMTAB[j].address;
                     }
                     else
                     {
                         int ab,num=0;
                         char dig;
                         for(int ka=0;ka<net.length();ka++)
                         {
                             ab=net[ka]-48;
                             num=num*10+ab;
                         }
                         net=tohexstr(num);
                     }
                     t=n*2+i;
                     foradd=tohexstr(t);
                     code=addhex(code,foradd);
                     myfile<<code;
                     fg=1;
                }
                else     //if qw is NOT # can be + with variable... or modify record
                {
                    mod_record[mod_count]=addhex(address,"1");
                    while(mod_record[mod_count].length()<6)
                        mod_record[mod_count]='0'+mod_record[mod_count];
                    mod_record[mod_count]="M^"+mod_record[mod_count]+"^05";
                    mod_count++;
                    int j;
                    for(j=0;j<symtab_ctr;j++)
                    {
                        if(operand == SYMTAB[j].label)
                        {break;}
                    }
                    net=SYMTAB[j].address;
                    n=1;
                    i=1; 
                    t=n*2+i;
                    foradd=tohexstr(t);
                    code=addhex(code,foradd);
                    myfile<<code;//***set length of operand to 5 half bytes
                    fg=1;
                }
         }
         else if(qw=='#')                //immediate...
         {
                n=0;
                i=1;
                net=operand.substr(1);
                char cha=net[0];
                if(!(cha>='0' && cha<='9'))         //label after #
                {
                    int j;
                    for(j=0;j<symtab_ctr;j++)
                    {
                        if(net == SYMTAB[j].label)
                        {break;}
                    }
                    net=SYMTAB[j].address;
                    string tt="0";
                    tt=tt+form;
                    string pctr=addhex(address,tt);
                    if( compare(net,pctr) )
                    {
                        p=1;
                        net=subtract_hex(net,pctr);
                    }
                    else
                    {
                        p=1;
                        net=subtract_hex(pctr,net);
                        net=compliment(net);
                    }
                }
                //checking for variable after #
                t=n*2+i;
                foradd=tohexstr(t);
                code=addhex(code,foradd);
                myfile<<code;
                fg=1;
         }
         else if(qw=='@')//indirect addressing...
         {
                n=1;
                i=0;
                net=operand.substr(1);
                char cha=net[0];
                if(!(cha>='0' && cha<='9'))//label after #
                {
                     int j;
                     for(j=0;j<symtab_ctr;j++)
                     {
                         if(net == SYMTAB[j].label)
                         {break;}
                     }
                     net=SYMTAB[j].address;
                     string tt="0";tt=tt+form;
                     string pctr=addhex(address,tt);
                     if( compare(net,pctr))
                     {
                         p=1;
                         net=subtract_hex(net,pctr);
                     }
                     else
                     {
                         p=1;
                         net=subtract_hex(pctr,net);
                         net=compliment(net);
                     }
                }
                t=n*2+i;
                foradd=tohexstr(t);
                code=addhex(code,foradd);
                myfile<<code;
                fg=1;
         }
         else if(form=='1')
         {}
         else if(form=='2')
         {
                if(operat=="CLEAR" || operat=="TIXR")                
                {
                    //check length of operand
                    operand=operand+",A";//since A would correspond to a zero
                }
                int lp=operand.length();
                //if(lp!=3)cout<<"ERROR"<<endl;
                char ch1,ch2;
                ch1=operand[0];
                ch2=operand[2];
                string op1,op2;
                switch(ch1)
                {
                    case'A':
                        op1="0";
                        break;
                    case'X':
                        op1="1";
                        break;
                    case'L':
                        op1="2";
                        break;
                    case'B':
                        op1="3";
                        break;
                    case'S':
                        op1="4";
                        break;
                    case'T':
                        op1="5";
                        break;
                    case'F':
                        op1="6";
                        break;
                    default:
                        op1="";
                        break;
                }
                switch(ch2)
                {
                    case'A':
                        op2="0";
                        break;
                    case'X':
                        op2="1";
                        break;
                    case'L':
                        op2="2";
                        break;
                    case'B':
                        op2="3";
                        break;
                    case'S':
                        op2="4";
                        break;
                    case'T':
                        op2="5";
                        break;
                    case'F':
                        op2="6";
                        break;
                    default:
                        op2="";
                        break;
                }
                n=0;i=0;
                t=n*2+i;
                foradd=tohexstr(t);
                code=addhex(code,foradd);
                myfile<<code;
                fg=1;
                printmid=false;
                net=op1+op2;
         }
         else//direct addressing
         {

                int pos=operand.find(',');
                int lp=operand.length();
                x=0;
                if(pos>=0 && pos<lp)//index registering expected...format 3
                {
                    x=1;
                    operand=operand.substr(0,lp-2);
                }
                n=1;
                i=1;
                p=1;
                string tt="";
                tt=tt+form;
                string pctr=addhex(address,tt);
                int j;
                for(j=0;j<symtab_ctr;j++)
                {
                    if(operand == SYMTAB[j].label)
                    {break;}
                }
                net=SYMTAB[j].address;
                if( compare(net,pctr) )
                {
                    net2=net;
                    net=subtract_hex(net,pctr);
                    if(net.length()>3)
                        dobase=true;
                }
                else
                {
                    net2=net;
                    net=subtract_hex(pctr,net);
                    if(net.length()>3)
                        dobase=true;
                    else
                    {
                        net=compliment(net);
                        if(net.length()<3)
                        {
                            while(net.length()!=3)
                            net='F'+net;
                        }
                    }
                }
                if(dobase==true)
                {
                    n=1;i=1;
                    b=1;p=0;
                    net=subtract_hex(net2,base);
                }
                t=n*2+i;
                foradd=tohexstr(t);
                code=addhex(code,foradd);
                myfile<<code;
                fg=1;
         }
         mid="0";
         if(printmid==true)
         {
                t=x*8+b*4+p*2+e*1;
                foradd=tohexstr(t);
                mid=addhex(foradd,mid);
                myfile<<mid;               //ONE HALF BYTE....
                fg=1;
         }
         int j=net.length();
         if(e==0)
         {
                if(form!='2')
                {
                    if(j==4)
                    {net=net.substr(1);}
                    else
                    {
                        for(int k=1;k<=(3-j);k++)
                        net='0'+net;
                    }
                }
         }
         else
         {
                for(int k=1;k<=(5-j);k++)
                net='0'+net;
         }
         myfile<<net;
         fg=1;
         string ss="";
         ss=ss+form;
         addr=addhex(addr,ss);
    }
    if(fg==1)
    myfile<<endl;
    myfile.close();
}
#endif    
