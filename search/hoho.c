#include<stdio.h>
		
	struct student{
		int roll,marks[3];
		char name[20];
		float percent;
	};

	struct student ourarray[100];


	void search(int roll, int n){
		int temp=0,i;
		for(i=0;i<n;i++){
			if(roll == ourarray[i].roll){
				printf("Search Found.\nDetails:\n");
				printf("Roll:%d \n",ourarray[i].roll);
				printf("Name:%s \n",ourarray[i].name);
				printf("Percentage:%f \n",ourarray[i].percent);
				printf("Marks:%d , %d , %d",ourarray[i].marks[0] ,ourarray[i].marks[1] ,ourarray[i].marks[2]);
				break;
			}
			else{
				temp=-1;
				}
		}
		if(temp==-1){printf("Search not found!");}
	}


	void modify(int roll, int n){
		int i;	
		for(i=0;i<n;i++){
			if(roll == ourarray[i].roll){
		printf("---MODIFICATION FOR CURRENT ROLL %d----",ourarray[i].roll);
		printf("Roll:");scanf("%d",&ourarray[i].roll);
		printf("Name:");scanf("%s",&ourarray[i].name);
		printf("Marks(1):");scanf("%d",&ourarray[i].marks[0]);
		printf("Marks(2):");scanf("%d",&ourarray[i].marks[1]);
		printf("Marks(3):");scanf("%d",&ourarray[i].marks[2]);
		printf("Percentage:");scanf("%f",&ourarray[i].percent);
			}
		}
	}

	void maxpercent(int n){
		float perarr[100],swap;int i,d;
		for(i=0;i<n;i++){
			perarr[i]=ourarray[i].percent;
		}
		
		for(i=0;i<n-1;i++){
			
			 
			    for (d = 0 ; d < n - i - 1; d++)
			    {
			      if (perarr[d] < perarr[d+1]) /* For decreasing order use < */
			      {
				swap       = perarr[d];
				perarr[d]   = perarr[d+1];
				perarr[d+1] = swap;
			      }
			    }
			 


		}	for(i=0;i<n;i++){
				if(ourarray[i].percent == perarr[0]){	
				printf("Roll:%d \n",ourarray[i].roll);
				printf("Name:%s \n",ourarray[i].name);
				printf("Percentage:%f \n",ourarray[i].percent);
				printf("Marks:%d , %d , %d",ourarray[i].marks[0] ,ourarray[i].marks[1] ,ourarray[i].marks[2]);
			   }
			}
		}
//START OF MAIN PROGRAM
main()	
{
	int n,i=0;
	printf("Number Of Students:");scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("-------");
		printf("Roll:");scanf("%d",&ourarray[i].roll);
		printf("Name:");scanf("%s",&ourarray[i].name);
		printf("Marks(1):");scanf("%d",&ourarray[i].marks[0]);
		printf("Marks(2):");scanf("%d",&ourarray[i].marks[1]);
		printf("Marks(3):");scanf("%d",&ourarray[i].marks[2]);
		printf("Percentage:");scanf("%f",&ourarray[i].percent);
			
	}

	//SEARCH STUFF
	int xs;
	printf("Search: ");scanf("%d",&xs);
	search(xs,n);
	//SEARCH ENDS
	maxpercent(n);
	
}
