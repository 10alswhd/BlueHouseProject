#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define SIZE 30
 
typedef struct node WORD;
struct node {
char *words;
int count;
struct node *pLeft;
struct node *pRight;
};

WORD *create_node(char *);//function to create a node
WORD *add_node(char *,WORD *);//function to add a node
void list_node(WORD *,FILE *);//function to list node content

WORD *create_node(char *word){
//declare and allocate space for new node
	WORD *newNode;
	newNode=(WORD*)malloc(sizeof(WORD));


	newNode->words = (char*)malloc(SIZE*sizeof(char ));//allocate space to store word
	strcpy(newNode->words,word);//copy word into the new node's words member
	newNode->count=1;//set counter to 1 for a new word
	newNode->pLeft=newNode->pRight=NULL;

	return newNode;
}

WORD *add_node(char *word,WORD *newNode){
        //if word is same as the new word's member words counter is incremented
		 if(strcmp(newNode->words,word)==0){
			 
				 newNode->count+=1;
				 return newNode;
			 }
		 
		//else if it is less than we create a right node and store in its words member word
		 if(strcmp(newNode->words,word)<0){
		 //if right node is empty create node
			 if(!newNode->pRight){
			 
			 newNode->pRight=create_node(word);
		
			 
			 } 
		 //else reursively search for an empty right node
		 else{
			  return add_node(word,newNode->pRight);
		 }
		 
		 
		 } 
		 //else if it is less than we create a left node and store in its words member word 
		   if(strcmp(newNode->words,word)>0){
		 
		 //if left node is empty create node
			   if(!newNode->pLeft){
			 
			 newNode->pLeft=create_node(word);
			  
			 
			 } 
			  //else reursively search for an empty right node
		 else{
			  return add_node(word,newNode->pLeft);
		 }
			 }
     
     
}

void list_node(WORD *pRoot,FILE *myFile){

		if(pRoot->pLeft)//if we are on the left node we list its content
		 list_node(pRoot->pLeft,myFile);
		 printf("%15s %10d\n",pRoot->words,pRoot->count);
		 fprintf(myFile,"%10s %10d\n",pRoot->words,pRoot->count);
		if(pRoot->pRight)
		 list_node(pRoot->pRight,myFile);
		 
}

//input file to count words from is provided as first a argument and the result is provided as the second arg of command line  
int main(int argc,char *argv[]){
			FILE *myFile;//file pointer for input file
			FILE *outputFile;//file for output file
			WORD *pRoot=NULL;//root  pointer

			char word[SIZE];//buffer to store read word
			char c;//character 
			int i=0; //index

			myFile=fopen(argv[1],"r");
			outputFile=fopen(argv[2],"w");
			//check ifall files were created or opened
			if(!myFile || !outputFile ){
			
				printf("%s","one of the files could not be opened");
				exit(-1);
		
				}
			//take characters untill we reach the end of file
			  while((c=fgetc(myFile))!=EOF){
			  
			  //we check if character is alphanumeric
				  if(isalnum(c)){
					 word[i]=c;//we store each character into the array
					  i++; 
			 	 }
				
				 else{
					word[i]='\0';//append null character to end of array to form the string
					 i=0;
				   
					if(!pRoot) //check if our root node is null
					 pRoot=create_node(word);//if it is null we create root node
			  
				   else
			  {
				add_node(word,pRoot);//else we add node
		
			   }
				}
				 }
			  list_node(pRoot,outputFile);//we print  the output into our outputfile
				system("pause");
			 
			}
