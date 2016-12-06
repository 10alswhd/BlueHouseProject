#include <stdio.h>
#include <string.h>

int main(void) {
	char str[100];
	int left, right, length, mid = 0;
	int flag = -1;
	memset(str, 0, sizeof(str));
	scanf("%s",str);
	left = 0;
	right = strlen(str) - 1;
	length = right;
	while(left < right){
		mid = (left+right)/2;
		if(mid < length && str[mid] == (char)'0'){
			if(str[mid + 1] == (char)'1'){
				flag = mid;
				break;
			}
			else{
				left = mid + 1;
			}
		}
		else if(mid > 0 && str[mid] ==(char)'1'){
			if(str[mid - 1] == (char)'0'){
				flag = mid - 1;
				break;
			}
			else{
				right = mid - 1;
			}
		}
	}
	printf("Input was = %s\n",str);
	if(flag == -1)printf("No inversion point\n");
	else printf("Inversion point = %d\n", flag + 1);
	return 0;
}
