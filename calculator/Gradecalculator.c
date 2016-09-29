#include "stdafx.h"
#include "stdlib.h"

int i,num,sum=0;
char subject[10][100]={0,};
double score[100];
int credit[10];
int getcredit;
double result=0;

void input(int num);
void output();

int _tmain(int argc, _TCHAR* argv[])
{
	int take = 0;
	printf("수강 과목 수 : ");
	scanf("%d",&num);
	printf("\n");

	input(num);
	printf("====================================\n");
	output();

	system("pause");
	return 0;
}
void input(int num)
{
	for(i=0; i<num; i++)
	{
		printf("과목 : ");
		scanf("%s",&subject[i]);
		printf("성적 :(숫자로 기입) ");
		scanf("%lf",&score[i]);
		printf("학점 : ");
		scanf("%d",&credit[i]);
		printf("\n");
	}
}
void output()
{
	for(i=0; i<num; i++)
	{
		printf("과목 : %s\n",subject[i]);
		printf("성적 : %.1lf\n",score[i]);
		printf("학점 : %d\n",credit[i]);
		printf("\n");
		
		result=result+(score[i]*credit[i]);
		sum=sum+credit[i];
		getcredit=getcredit+credit[i];
	}
	result=result/sum;
	printf("총 취득학점은 %d입니다.\n",getcredit);
	printf("평점은 %.2lf입니다.\n",result);	
}
