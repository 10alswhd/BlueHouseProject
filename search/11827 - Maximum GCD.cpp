#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define BUFFER 10000 
using namespace std;

int GCD(int a,int b){
	while((a=a%b) && (b = b %a));
	return a+b;
}

int main(){ 
	int N;
	char lineSeries[BUFFER];
	char *tempNum; 
	cin >> N;
	cin.ignore(100,'\n');
	while( N-- ){
		int numSerise[BUFFER],size = 0,maxGcd = 0;
		gets(lineSeries);
		tempNum = strtok(lineSeries," "); 
		while(tempNum != NULL){
			numSerise[size++] = atoi(tempNum);
			tempNum = strtok(NULL," "); 
		}   
		for(int j = 0; j < size - 1; j++)
			for(int k = j+1; k < size; k++)
			 	maxGcd = max(maxGcd,GCD(numSerise[j],numSerise[k])); 
	
		cout<<maxGcd<<endl;
	}
}
