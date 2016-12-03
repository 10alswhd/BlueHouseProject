#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUF 20
#define MAX_SCOPE 10000000
#define FILE_NAME "all_nums.txt"
#define FILE_RESULT "sorted_nums.txt"

/* 将长度为n字符串str反转 */
static char* reverse_str(char *str, int n)
{
  char temp;
  int i;

  i = 0;
  while(i < n/2)
  {
    temp = str[i];
    str[i] = str[n-i-1];
    str[n-i-1] = temp;
    ++i;
  }

  return str;
}

/* 转换正整数i为对应的字符串并设置其长度为n */
static char* itostr(int i, int *n)
{
  char *i_str;
  int result, remainder, j;

  i_str = malloc(10*sizeof(char));
  result = i;
  j = 0;

  do {
    remainder = result % 10;
    result = result / 10;
    i_str[j++] = remainder + '0';
  } while(result);

  i_str = reverse_str(i_str, j);

  *n = j;

  return i_str;
}

void generate_num(int scope, int count)
{
  int i,j,n;
  FILE *fp;
  char *ch;

  i = 0;
  fp = fopen(FILE_NAME, "a");

  srand(time(NULL));

  while(i < count)
  {
    //srand(time(NULL));
    j = rand() % scope;
    ch = itostr(j, &n);
    fwrite(ch, sizeof(char), n, fp);
    fwrite("\n", sizeof(char), 1, fp);
    free(ch);
    ch = NULL;
    ++i;
  }

  fclose(fp);
}

void disk_sort()
{
  char all_nums[MAX_SCOPE]; 
  char buf[MAX_BUF];
  char *ch;
  FILE *fp;
  int n, j;

  fp = fopen(FILE_NAME, "r");

  for(n = 0; n < MAX_SCOPE-1; ++n)
  {
    all_nums[n] = '0';
  }

  all_nums[MAX_SCOPE-1] = '\0';

  while(fgets(buf, MAX_BUF, fp) != NULL)
  {
    sscanf(buf, "%d\n", &n);
    all_nums[n]++;
  }

  fclose(fp);
  fp = fopen(FILE_RESULT, "a");

  n = 0;
  while(all_nums[n] != '\0')
  {
    if(all_nums[n] != '0')
    {
      ch = itostr(n, &j);
      ch[j++] = '\n';
      ch[j] = '\0';
      /* 若有重复数据，则相应地输出all_nums[n]-'0'次对应的数据 */
      for(int i = 0; i < all_nums[n] - '0'; ++i)
      {
        fwrite(ch, sizeof(char), j, fp);
      }
      free(ch);
      ch = NULL;
    }
    ++n;
  }
  fclose(fp);
}

int main() 
{
  clock_t t = clock();

  FILE *fp = fopen(FILE_NAME, "w");
  fclose(fp);
  FILE *fp2 = fopen(FILE_RESULT, "w");
  fclose(fp2);

  generate_num(MAX_SCOPE, 1000000);
  disk_sort();

  t = clock() - t;
  printf("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

  return 0;
}
