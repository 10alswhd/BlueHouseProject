//랜덤 값 맞추기
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    int rand_num = 0;
    int count = 0;
    int guess = 0;
 
    srand((unsigned)time(0)); //프로그램을다시동작할 때 같은 값이 발생하지 않게 랜덤 시드 (Seed)값 설정
 
    rand_num = rand() % 100; //랜덤 값
 
    while (1)
    {
        printf("추측답: ");
        scanf_s("%d", &guess);
        if (guess == rand_num)
        {
            break;
        }
        if (guess<rand_num)
        {
            printf("더 큽니다.\n");
        }
        else
        {
            printf("더 작습니다.\n");
        }
        count++; //시도 회수
    }
    printf("%d 번 시도하여 정답을 맞추셨군요.\n", count);
    return 0;
}
