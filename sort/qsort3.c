//void qsort (void* base,size_t n, size_t size,  int (*compare)(const void*,const void*)); 정렬 함수
//회원 배열을 번호 순으로 정렬, 이름 순으로 정렬
 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
typedef struct{//회원 구조체 정의
   int num;
   char name[20];
}Member;
 
typedef int (*compare)(const void*,const void*);//비교 알고리즘 함수 포인터를 compare 이름으로 타입명 정의
 
int CompareByNum(const void *v1, const void *v2)//회원 번호로 비교 함수
{
   const Member *m1 = (const Member *)v1;
   const Member *m2 = (const Member *)v2;
   return m1->num - m2->num;
}
 
int CompareByName(const void *v1, const void *v2)//회원 이름으로 비교 함수
{
   const Member *m1 = (const Member *)v1;
   const Member *m2 = (const Member *)v2;
   return strcmp(m1->name,m2->name);
}
 
void ListMember(Member *base,int n)//회원 전체 목록 출력 함수
{
   int i = 0;
   for(i=0;i<n;i++)
   {
       printf("번호:%3d   이름:%s\n",base[i].num,base[i].name);
   }
}
 
int main (void)
{
   Member members[4]=
   {
       {20,"홍길동"},{12,"강감찬"},{3,"을지문덕"},{40,"유관순"}
   };
 
 
   printf("========== 정렬 전============\n");
   ListMember(members,4);
 
   qsort(members,4,sizeof(Member),CompareByNum);//번호 순으로 정렬
   printf("========== 번호 순============\n");
   ListMember(members,4);
 
   qsort(members,4,sizeof(Member),CompareByName);//이름 순으로 정렬
   printf("========== 이름 순============\n");
   ListMember(members,4);
 
   return 0;
}
