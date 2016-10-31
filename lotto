#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int i,j,r,yescnt;
	int answer[6], usernum[6];
	for(i=1;i<7;i++){
			answer[i]=0;
			usernum[i]=0;
	}
	yescnt=0;
	srand(time(NULL));

	for(i=1;i<7;i++){
		answer[i]=(rand()%44)+1;
	}

	printf("숫자 6개를 입력하십시오 [1~45]--->");
	fflush(stdin);
	scanf("%d %d %d %d %d %d", &usernum[1], &usernum[2], &usernum[3], &usernum[4], &usernum[5], &usernum[6]);
	fflush(stdin);
	printf("복권을 뽑았습니다.\n");
	printf("당신이 입력한 숫자는 %d, %d, %d, %d, %d, %d입니다.\n",usernum[1],usernum[2],
		usernum[3],usernum[4],usernum[5],usernum[6]);
	printf("당첨번호는 %d, %d, %d, %d, %d, %d입니다.\n", answer[1], answer[2], answer[3],
		answer[4], answer[5], answer[6]);

	for(i=1;i<7;i++){
		if(usernum[i]==answer[i]){
			yescnt++;
		}
	}
	printf("당신이 맞춘 숫자는 %d개입니다.\n", yescnt);
	switch(yescnt){
	case 6: 
		printf("1등입니다. 빨리 진짜 로또사세요.");break;
	case 5: 
		printf("2등입니다.");break;
	case 4: 
		printf("3등입니다.");break;
	case 3: 
		printf("4등입니다.");break;
	case 2: 
		printf("5등입니다.");break;
	case 1: 
		printf("6등입니다.");break;
	default:
		printf("완전 꽝입니다");
	}
	printf("\n");
	system("pause");
	return 0;
		
}

