#ifndef HEXFUNC_H_INCLUDED
#define HEXFUNC_H_INCLUDED
#include "subtract_hex.h"
#include "add_hex.h"

string tohexstr(int n)
{
    char ch='0';
    if(n<16)
    {
        int x=n;
        if(x<10)
            ch=x+48;
        else
        {
            int p=x-9;
            ch=p+48;
            ch=ch+16;
        }
        string temp="";
        temp=temp+ch;
        return temp;
    }
    int x=n%16;
    if(x<10)
        ch=x+48;
    else
    {
        int p=x-9;
        ch=p+48;
        ch=ch+16;
    }
    return (tohexstr(n/16)+ch);
}

string compliment(string a)    //2s compliment on the input hex 'a'
{
    int len=a.length();string ans="";
    for(int i=0;i<len;i++)
     ans='F'+ans;
    ans=subtract_hex(ans,a);
    ans=addhex(ans,"1");
    return ans;

}

bool compare(string s1,string s2)
{
    int i=0;char ch=s1[i];
    while(i<s1.length() && ch=='0')
    {
        ch=s1[i];
        i++;
    }
    s1=s1.substr(max(0,i-1));

    i=0;ch=s2[i];
    while(i<s2.length() && ch=='0')
    {
        ch=s2[i];
        i++;
    }
    s2=s2.substr(max(0,i-1));
    if(s1.length()>s2.length())return true;
    if(s2.length()>s1.length())return false;
    i=0;ch=s1[i];char ch2;ch2=s2[i];
    while(i<s1.length())
    {
        ch=s1[i];ch2=s2[i];
        if(ch2>ch)return false;
        else if(ch2<ch)return true;
        i++;
    }
    return true;

}

#endif // HEXFUNC_H_INCLUDED
