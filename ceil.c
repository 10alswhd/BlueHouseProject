
#include <math.h>
#include <stdio.h>
int main(void)
{
    int scores[3],i, sum=0;
    printf("국어 영어 수학 성적: ");
    for(i=0;i<3;i++)
    {
        scanf_s("%d",scores+i);
        sum += scores[i];
    }   
    printf("합계: %d 평균(올림): %.lf\n",sum, ceil(sum/3.0));
    return 0;
}
