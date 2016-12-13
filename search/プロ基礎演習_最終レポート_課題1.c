#include<stdio.h>
#include<stdlib.h>

int *set;
int num=0,max;

void Showset(void){
  int i;
  for(i=0;i<num;i++)
    printf("%d ",set[i]);
}

int Contains(int Val){
  int min_num=0,max_num=num-1,ave_num;
  if(max<Val||num<=0)
    return 0;
  while(min_num<=max_num){
        ave_num = (max_num + min_num) / 2;
        if (set[ave_num] == Val)
	  return 1;
        else if (set[ave_num] < Val)
            min_num = ave_num + 1;
        else
            max_num = ave_num - 1;
    }
  return 0;
}

void Add(int Val){
  int i;
  if(Contains(Val))
    return;
  if(num==0||max<Val)
    max=Val;
  for(i=num;set[i-1]>Val&&i>0;i--)
    set[i]=set[i-1];
  set[i]=Val;
  num++;
  return;
}

int Size(void){return num;}

void Delete(int Val){
  int i=0;
  if(max<Val)
    return;
  while(set[i]<Val)
    i++;
  if(set[i]==Val){
    num--;
    while(i<num){
      set[i]=set[i+1];
      i++;
    }
  }
  return;
}

int main(){
	int op, val;

	printf("**************************************************************\n");
	printf("**            How to use this program                       **\n");
	printf("** Command (op Vals)| --Explanation--                       **\n");
	printf("** 1 (No Val)       | Display the current set               **\n");
	printf("** 2 Val            | Search 'Val'                          **\n");
	printf("** 3 Val            | Add 'Val' to the current set          **\n");
	printf("** 4 (No Val)       | Count the elements of the current set **\n");
	printf("** 5 Val            | Delete 'Val'                          **\n");
	printf("** 0                | Exit                                  **\n");
	printf("**************************************************************\n");
	printf("\n");

	if((set=(int*)malloc(sizeof(int)))==NULL){
	  printf("メモリが確保できません\n");
	  return 0;
	}

	while(1) {
		printf("Input your command (0-4) -> ");
		scanf("%d", &op);
		switch (op) {
		case 1:
		  printf("----- Current Set -----\n");
		  Showset();
		  printf("\n\n");
		  break;
		case 2:
		  scanf("%d", &val);
		  if(Contains(val))
		    printf("'%d' is contained.\n\n",val);
		  else
		    printf("'%d' is not contained.\n\n",val);
		  break;
		case 3:
		  scanf("%d", &val);
		  Add(val);
		  printf("Addition Completed.\n\n");
		  break;
		case 4:
		  printf("The number of the elements : %d",Size());
		  break;
		case 5:
		  scanf("%d", &val);
		  Delete(val);
		  printf("Deletion Completed.\n\n");
		  break;
		case 0:
		  printf("Bye!\n");
		  free(set);
		  return 0;
		default:
		  printf("Invalid command! Retry!\n\n");
		}
	}

}
