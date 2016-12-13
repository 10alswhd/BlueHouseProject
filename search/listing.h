#ifndef LISTING_H_INCLUDED
#define LISTING_H_INCLUDED
#include <iostream>
#include <fstream>
#include <iomanip>

void listingf()
{
    FILE* fptr;string s,s2;char buffer2[256];
    fptr=fopen("output.txt","r");
    FILE* fptr2;
    fptr2=fopen("intermediate.txt","r");
    ofstream myfile;
    myfile.open("list.txt");
    fgets(buffer2,256,fptr2);
    s2=buffer2;
    s2=s2.substr(0,s2.length()-1);
    if(s2.length()!=0)
    myfile<<s2<<endl;
    while (fgets(buffer,256,fptr) != NULL)
  {
         s=buffer;
         fgets(buffer2,256,fptr2);
         s2=buffer2;
         s=s.substr(0,s.length()-1);
         s2=s2.substr(0,s2.length()-1);
         if(s.length()==0 && s2.length()==0)continue;
         myfile<<s2<<" "<<s<<endl;
	}
#endif 
}
