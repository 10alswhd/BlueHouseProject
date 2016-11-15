#include <string.h>
#include <stdio.h>
 
#define MAX_MEMBER     5
#define MAX_NAMELEN    20
typedef struct
{
    char name[MAX_NAMELEN];
    int age;
}Member;
 
void Swap(Member *m1, Member *m2)
{
    Member temp;
    memcpy(&temp,m1,sizeof(Member));//m1의 데이터를  temp 주소로 복사
    memcpy(m1,m2,sizeof(Member)); //m2의 데이터를 m1으로 복사
    memcpy(m2,&temp,sizeof(Member));//temp 주소의 데이터를 m2에 복사
}
int main(void)
{
    Member m1={"홍길동",20};
    Member m2={"강감찬",27};
 
    printf("바꾸기 전\n");
    printf("이름:%s 나이:%d\n",m1.name,m1.age);
    printf("이름:%s 나이:%d\n",m2.name,m2.age);
    Swap(&m1,&m2);//m1 주소와 m2 주소의 데이터를 교환
    printf("바꾸기 후\n");
    printf("이름:%s 나이:%d\n",m1.name,m1.age);
    printf("이름:%s 나이:%d\n",m2.name,m2.age);
 
    return 0;
}
