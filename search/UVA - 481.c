/*TPC2015 HW5 Solution by yukiring*/
/*Problem: NTHUOJ 10534 (UVA 481) - What goes up*/
/*C version*/

#include<stdio.h>

typedef struct{
	int val;
	int id;
}Block;

int sequence[100000],seqNum=0;
int lisLength[100000],prevId[100000];

Block data[100000];int size=0;

Block makeBlock(int newVal,int newId){
	Block ret;
	ret.val = newVal;
	ret.id = newId;
	return ret;
}
void insert(Block newBlock,int position){
	data[position] = newBlock;
}
int binarySearch(int targetVal,int lf,int rt){
	int mid,ret;
	while(lf<=rt){
		mid = (lf+rt)>>1;
		if(targetVal<=data[mid].val){
			ret = mid;
			rt = mid-1;
		}
		else lf = mid+1;
	}
	return ret;
}

void trace(int c){
	if(prevId[c]!=-1)
		trace(prevId[c]);
		
	printf("%d\n",sequence[c]);
}

int main()
{
	int i,max=0,maxId,insertPosition;
	
	while(EOF!=scanf("%d",sequence+seqNum))seqNum++;
	
	for(i=0;i<seqNum;i++)
		prevId[i] = -1;
	
	insert( makeBlock(sequence[0],0), size++ );
	lisLength[0] = 1;
	for(i=1;i<seqNum;i++){
		if( sequence[i]>data[size-1].val ){
			insert( makeBlock(sequence[i],i), size );
			lisLength[i] = size + 1;
			prevId[i] = data[size-1].id;
			size++;
		}
		else{
			insertPosition = binarySearch( sequence[i] , 0, size-1);
			insert( makeBlock(sequence[i],i), insertPosition );
			lisLength[i] = insertPosition + 1;
			prevId[i] = (insertPosition>0) ? data[insertPosition-1].id : -1;
		}
	}
	
	for(i=0;i<seqNum;i++){
		if(lisLength[i]>=max){
			max = lisLength[i];
			maxId = i;
		}
	}
	
	printf("%d\n-\n",max);
	trace(maxId);
	return 0;
}
