ifndef OBJECTPROG_H_INCLUDED
#define OBJECTPROG_H_INCLUDED
#include <iostream>
#include <fstream>
#include <iomanip>
#include<string>
using namespace std;
void write()
{

    int columns=0;
    string forwriting="",s,textrec_add=start_add;
    store_count=0;

    ofstream myfile;
    myfile.open("object.txt");

    myfile<<"H^";
    myfile<<SYMTAB[0].label;
    for(int yr=SYMTAB[0].label.length();yr<6;yr++)
    myfile<<" ";
    int i=start_add.length();
    for(;i<6;i++)
    {
        start_add="0"+start_add;
    }    
    myfile<<start_add<<"^00"<<length<<endl;

    FILE* fptr;
    fptr=fopen("output.txt","r");
    int fl=0;
    while (fgets(buffer,256,fptr) != NULL)
  {
	     s=buffer;
	     store_count++;
         s=s.substr(0,s.length()-1);
         if(s.length()==0)
         {
             fl=1;                  
             continue;
         }    
         if(columns+s.length() > 60 || fl==1)
         {
              myfile<<"T";
              i=textrec_add.length();
              for(;i<6;i++)
              {
                      textrec_add="0"+textrec_add;
              } 
              myfile<<"^"<<textrec_add;
              string temp=tohexstr(columns/2);
              i=temp.length();
              for(;i<2;i++)
              {
                  temp="0"+temp;
              }    
              myfile<<"^"<<temp;
              myfile<<forwriting<<endl;
              columns=0;
              forwriting="^"+s;
              columns=s.length();
              textrec_add=store[store_count];
              fl=0;
         }
         else
         {
              forwriting+="^"+s;
              columns+=s.length();
         }
    }    
    myfile<<"T^";
    i=textrec_add.length();
    for(;i<6;i++)
    {
        textrec_add="0"+textrec_add;
    }     
    myfile<<textrec_add<<"^";
    string tem=tohexstr(columns/2);
    i=tem.length();
    for(;i<2;i++)
    {
           tem="0"+tem;
    }    
    myfile<<tem;
    myfile<<forwriting<<endl;
    for(int i=0;i<mod_count;i++)
        myfile<<mod_record[i]<<endl;
    myfile<<"E^"<<start_add<<endl;
    myfile.close();
    fclose(fptr);
}

#endif 
