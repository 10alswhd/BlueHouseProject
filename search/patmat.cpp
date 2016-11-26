#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100 //Max length
#define d 256 // base for Robin Karp
using namespace std;
int lps[N];
char text[N],pat[N];
int q=101;//Prime number for Robin Karp

void naivesearch()
{
	int n=strlen(text),m=strlen(pat),f=0;
	for(int i=0;i<n-m+1;i++)
	{
		f=0;
		for(int j=0;j<m;j++)
			if(text[i+j]!=pat[j])
			{
				f=1;
				break;
			}
		if(!f)
			cout<<"Found at : "<<i<<endl;
	}
	cout<<endl;
	return;
}
//Compute lps
void lpsar(int m)
{
	int len=0,i=1;
	lps[0]=0;
	while(i<m)
	{
		if(pat[i]==pat[len])
			lps[i++]=++len;
		else
		{
			if(len)
				len=lps[len-1];
			else
				lps[i++]=0;
		}
	}
	//for(int j=0;j<m;j++)cout<<lps[j]<<" ";
}

//KMP Algo
void kmpsearch()
{
	int m=strlen(pat),n=strlen(text),j=0,i=0;
	lpsar(m);
	while(i < n)
    {
      if(pat[j] == text[i])
      {
        j++;
        i++;
      }
      if (j == m)
      {
        cout<<"Found at : "<<i-j<<endl;
        j = lps[j-1];
      }
      else if(pat[j] != text[i])
      {
        if(j)
         j = lps[j-1];
        else
         i++;
      }
    }
}

//Robin Karp Algo
void robin_karp_search()
{
	int m=strlen(pat),n=strlen(text),i,j,t=0,p=0,h=1;
	for (i = 0; i < m-1; i++)
        h = (h*d)%q;
    for (i = 0; i < m; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + text[i])%q;
    }
    for (i = 0; i <= n - m; i++)
    {
        if (p==t)
        {
            for (j = 0; j < m; j++)
                if (text[i+j] != pat[j])
                    break;
            if (j==m)
	            cout<<"Found at : "<<i<<endl;
        }      
        if ( i < n-m )
        {
            t = (d*(t - text[i]*h) + text[i+m])%q;
            if(t < 0)
              t+=q;
        }
    }
}

//Driver code
int main() {
	gets(text);
	gets(pat);
	robin_karp_search();
	return 0;
}
