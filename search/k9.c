#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int i=0,j=0,k=0;
  int tmp=0;
  int map[5][5]={0},buf[5][15]={0};
  
  srand((unsigned int) time(NULL));

  // 配列に1-75の値を格納
  for(i=0; i<5; i++) {
    for(j=0; j<15; j++) {
      buf[i][j] = k + 1;
      k++;
    }   
  }

  // 2次配列をシャッフル
  for(i=0; i<5; i++) {
    for(j=14; j; j--) {
      tmp = buf[i][j];
      k = rand() % (j + 1); 
    
      buf[i][j] = buf[i][k];
      buf[i][k] = tmp;
    }   
  }

  puts("  B  I  N  G  O ");

  // ビンゴカードを描画
  for(i=0; i<5; i++) {
    for(j=0; j<5; j++) {
      if(i == 2 && j == 2) {
        printf("   ");
      } else {
        printf("%3d", map[i][j]=buf[j][i]);
      }   
    }   
    printf("\n");
  }
  
  return 0;
}
