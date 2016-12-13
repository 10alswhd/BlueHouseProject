#include <stdio.h>
/*
refer to 
http://www.thecrazyprogrammer.com/2014/03/depth-first-search-dfs-traversal-of-a-graph.html
*/

#define MAX_MAPSIZE 50
#define SET_UNDIRECTIED_GRAPH 

int map[MAX_MAPSIZE][MAX_MAPSIZE]={0};	//

int visit1[MAX_MAPSIZE]={0}; 				//   visit vertex 
int visit2[MAX_MAPSIZE]={0}; 				//   visit vertex

int stack[100]={0};
int stacksize=0;

void DFS1(int currentvertex, int nvertex , int finvertex) //used function stack
{
    int i;
 
    visit1[currentvertex] = 1; 
    printf("%d->",currentvertex); 
    
    for (i = 0; i < nvertex; i++) 
    {
        if (map[currentvertex][i] == 1 && visit1[i]==0){ // visit 
        	
        //	printf("[%d][%d] ",currentvertex ,i); 
        	if(i== finvertex) { printf("%d end-1\n",i); return; }
            else DFS1   (i,nvertex,finvertex);
            
        } 
        	
    }
}

void DFS2(int currentvertex, int nvertex , int finvertex) //used function stack
{
    int i;
 
 	do{
 	
     	if(stacksize > 0)
        	currentvertex = stack[--stacksize];    
        
    	visit2[currentvertex] = 1; 
    	printf("%d->",currentvertex); 
    
    	for (i=0;i< nvertex; i++) 
    	{
        	if (map[currentvertex][i] == 1 && visit2[i]==0){ // found it
        	//	printf("[%d][%d] ",currentvertex ,i);
        		if(i== finvertex) { printf("%d end-2\n",i);}
        		stack[stacksize++]=i;
        		break;
        	}
        } 
     
        
    }while(stacksize > 0);
    
    return;
} 
 
int MAP_print(int nvertex )
{
   int i,j;
	
   printf("\nV ");
   
   for(i=0;i<nvertex;i++)		
   { 
	if(i==0){
   		for(j=0;j<nvertex;j++)
     		{	
			printf(" %d",j);  
      			if(j==(nvertex-1)) printf("\n");
      		}
   	}	   		
	printf("%d: ",i);
		
   	for(j=0;j<nvertex;j++)
		printf("%d ",map[i][j]);
      	
   	printf("\n");
    }	
    
    return 0;
} 

 
int DFS_test() 
{
   int nvertex,nedge;
   int vertex,edge;
   int start,end;
   int i;
   
   scanf("%d",&nvertex);
   scanf("%d",&nedge);
   
   for(i=0;i<nedge;i++)
   {
   		scanf("%d %d",&vertex,&edge);   
   		map[vertex][edge]=1;
   }
   	
   scanf("%d",&start);	
   scanf("%d",&end);
   	
   printf("nvertex=%d  nedge=%d\nstart=%d    end=%d \n",nvertex,nedge,start,end);
   
   MAP_print(nvertex);
   
 
 printf("\n TEST 1st\n");    
 DFS1(start,nvertex,end);
 
 printf("\n TEST 2nd\n");
 DFS2(start,nvertex,end);
    
    return 0;
}

/*
   Input: 
8
10
0 1
0 2
1 5
2 5
5 7
0 3
0 4
3 6
4 6
6 7
0
7
*/

int main(void) {
	
	DFS_test();	
	return 0;
}
