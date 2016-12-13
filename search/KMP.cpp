#include<stdio.h>

void createPrefixTable(int F[], char P[], int n)
{
	int i=1,j=0;
	F[0] = 0;
	
	while(i<n){
		if(P[i]==P[j])
		{
			F[i] = j+1;
			i++;
			j++;
		}
		else if(j>0)
		j=F[j-1];
		
		else{
				F[i] = 0;
				i++;
		}
	}
}

int matchText(char P[], char T[], int F[], int sizeP, int sizeT)
{
	int i=0, j=0;
	
	while(i<sizeT)
	{
		if(T[i]==P[j])
		{
			if(j==sizeP-1)
				return i-j;
			else
			{
			
				i++;
				j++;
			}
		}
		else if(j>0)
			j=F[j-1];
		
		else
		i++;
	}
	return -1;
}

int main()
{
	
	char P[] = {'a','b','a','b','a','c','a'};
	char T[] = {'b','a','c','b','b','a','a','b','a','b','a','c','a','b','a'};
	
	int sizeP = sizeof(P)/sizeof(P[0]);
	int sizeT = sizeof(T)/sizeof(T[0]);
	
	int F[sizeP];
	int res = 0;
	
	createPrefixTable(F, P, sizeP);
	
	res = matchText(P,T,F, sizeP, sizeT);
	
	if(res==-1)
	{
		printf("No match found");
		
	}
	else
	{
		printf("Match found at %d", res);
	}
}
