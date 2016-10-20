#include<stdio.h>
#include<stdlib.h>

/*Linked List에 사용할 Node*/
typedef struct _node *nodeptr;
typedef struct _node{
	int data;
	nodeptr link;
}node;

/*Linked List의 제일 앞(Head)*/
nodeptr Head=NULL;

void InsertNode(int);
void DeleteNode();

int main(void){
	int n,i,temp;
	nodeptr search;

	printf("Input the number of data : ");
	scanf("%d",&n);

	i=0;

	while(i!=n){
		scanf("%d",&temp);
		
		InsertNode(temp);

		i++;
	}

	search=Head;
	while(search->link){
		printf("[%d] -> ",search->data);
		search=search->link;
	}
	printf("[%d] END\n", search->data);

	while(Head){
		DeleteNode();
	}	
	printf("\nDelete Complete.\n");

	return 0;
}

void InsertNode(int data){
	nodeptr tempnode,search=Head;
	
	tempnode=(nodeptr)malloc(sizeof(node));//임시 Node 생성
	tempnode->data=data;
	tempnode->link=NULL;

	if(!Head) Head=tempnode;//Head가 Null인 경우 link가 존재하지 않으므로, 바로 Insert.
	else{
		while(search->link) search=search->link;//Link가 Null인 Node를 탐색
		search->link=tempnode;
	}

	return;
}

void DeleteNode(){
	nodeptr search=Head;

	if(!Head){
		//Do Nothing
	}
	else if(!Head->link){//Head Node 하나만 존재하는 경우
		free(Head);
		Head=NULL;
	}
	else{/*일반적인 경우, Node의 다음 Node의 link가 Null인 것을 탐색.
		 (다음 Node를 free시키고, Node의 link를 Null로 하기 위함.)*/
		while(search->link->link) search=search->link;
		free(search->link);
		search->link=NULL;
	}
	return;
}
