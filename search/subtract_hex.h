#ifndef SUBTRACT_HEX_H_INCLUDED
#define SUBTRACT_HEX_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

string subtract_hex(string str1,string str2)
{
    char ch1,ch2,ch3;
    int d1,d2,s,c,i,j;
    string s1,s2,ans="";

    if(str1.length()>=str2.length())
    {
        s1=str1;
        s2=str2;
    }
    else
    {
        s1=str2;
        s2=str1;
    }
    c=0;
    int q=s1.length()-s2.length();
    for(int a=1;a<=q;a++)
    {
        s2='0'+s2;
    }
      
    for(i=s2.length()-1;i>=0;i--)
    {
              ch1=s1[i];
              if(ch1>=65)
                   d1=10+ch1-65;
              else
                   d1=ch1-48;
              ch2=s2[i];
              if(ch2>=65)
                   d2=10+ch2-65;
              else
                   d2=ch2-48;
              s=d1-d2-c;
              c=0;
              if(s<0)
              {
                     c=1;
                     s=s+16;
              }
              ch3=s+48;
              if(ch3>57)
                  ch3=55+s;
              ans=ch3+ans;
    }
    string ans2=ans;
    for(i=0;i<ans.length();i++)
    {
        if(ans[i]=='0')
            continue;
        break;
    }
    ans=ans.substr(i);
    if(ans=="")
        ans="0";
    return ans;
}

#endif // SUBTRACT_HEX_H_INCLUDED
