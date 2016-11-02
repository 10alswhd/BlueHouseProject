#include <stdio.h>

void main(){
		int i, n;

		printf("0을 입력하면 종료합니다\n\n");
		while(1){
			printf("약수를 구할 정수를 입력 하시오 :");
			scanf("%d", &n);
			printf("%d의 약수는 : ", n);
			
			for(i=1; i<=n; i++){
				if(n%i==0){
					printf("%d ",i);
				}
			}
			printf("\n");
				if(n==0) break;
		}

}
