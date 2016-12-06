#include<stdio.h>
#include<stdlib.h>

/*Stack에 사용할 Node*/
typedef struct _node *nodeptr;
typedef struct _node{
	int data;
	nodeptr link;
}node;

/*Stack의 제일 위*/
nodeptr Top=NULL;

void Push(int);
void Pop();

int main(void){
	int n,i,temp;
	nodeptr search;

	printf("Input the number of data : ");
	scanf("%d",&n);

	i=0;

	while(i!=n){
		scanf("%d",&temp);
		
		Push(temp);

		i++;
	}
	i++;
	while(i){
		Pop();
		i--;
	}

	return 0;
}

/*Stack에 새로운 데이터를 Top에 추가*/
void Push(int data){
	nodeptr tempnode;

	tempnode=(nodeptr)malloc(sizeof(node));
	tempnode->data=data;
	tempnode->link=Top;
	Top=tempnode;

	return;
}

/*Stack의 Top이 비어있지 않다면, Top의 node를 삭제*/
void Pop(){
	nodeptr temp;

	if(Top){
		temp=Top->link;
		free(Top);
		Top=temp;
	}
	else{
		printf("Stack is Empty!\n");
	}
	return;
}
