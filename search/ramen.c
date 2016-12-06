#include <stdio.h>
#include <string.h>

#define SEAT_NUM 8

int init(int* seat) {
  memset(seat, 0x00, SEAT_NUM);
}

int search(int* seat, int num) {
  int pos = -1;
  int count = 0;
  int head_count = -1;

  for (int i = 0; i < SEAT_NUM; i++) {
    if(seat[i] == 0) {
      if (pos == -1) {
        pos = i;
      }
      count++;
    } else {
      if (head_count == -1) {
        head_count = count;
      }
      pos = -1;
      count = 0;
    }

    if (count >= num) {
      return pos;
    }
  }

  if(head_count > 0 && (count + head_count) >= num) {
    return pos;
  }

  return -1;
}

void proceed(int* seat) {
  for(int i = 0; i < SEAT_NUM; i++) {
    switch(seat[i]) {
      case 1:
        /* FALLTHROUGH */
      case 2:
        seat[i]++;
        break;
      case 3:
        seat[i] = 0;
        break;
      default:
        break;
    }
  }
}

void sitdown(int* seat, int num, int pos) {
  for (int i = 0; i < num; i++) {
    seat[pos++] = 1;

    if(pos >= SEAT_NUM) {
      pos = 0;
    }
  }
}

void output(int* seat) {
  for(int i = 0; i < SEAT_NUM; i++) {
    if(seat[i] > 0) {
      seat[i] = 1;
    }
    printf("%d", seat[i]);
  }
  printf("\n");
}

int main(void){
  int seat[SEAT_NUM];
  char input[256];

  scanf("%s", &input);

  init(seat);

  for(int i = 0; i < strlen(input); i++) {
    int num = input[i] - '0';
    int pos = -1;

    proceed(seat);

    while(1) {
      pos = search(seat, num);

      if (pos >= 0) {
        break;
      } else {
        proceed(seat);
      }
    }

    sitdown(seat, num, pos);
  }

  output(seat);

  return 0;
}
