#include <stdio.h>

void main(){
	int num1, num2;
	char menu;

	
	printf("R , C , T 셋중 하나를 입력하세요.(대소문자 구분!)\n");
	scanf("%c", &menu);
	

	switch(menu){
	case 'R' :	printf("정사각형의 한변의 길이를 입력해주세요\n");
			    scanf("%d",&num1);
				printf("정사각형의 넓이: %d\n", num1*num1); break;
	case 'C' :  printf("원의 반지름을 입력해주세요.\n");
				scanf("%d",&num1);
				num1= num1*num1*3.14;
				printf("원의 넓이 : %d\n", num1); break;
	case 'T' :  printf("직각이등변의 밑변과 높이를 순서대로 입력해주세요.\n");
				scanf("%d %d", &num1, &num2);
				printf("삼각형의 넓이 : %d\n", num1*num2/2); break;
	}
}
