#include <stdio.h>
#include <string.h>

int main()
{
  char str1[100], str2[100];
  size_t location;
  
  puts("문자열을 입력해주세요");
  gets_s(str1);
  puts("찾을 단어를 입력해주세요");
  gets_s(str2);
  
  location = strcspn(str1, str2);
  
  if(location == strlen(str1))
    printf("찾을 수 없습니다\n");
  else
    printf("위치 %d에서 처음으로 발견되었습니다\n",location);
    
    return 0;
}
