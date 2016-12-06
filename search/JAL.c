#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <pthread.h>

int result = -1;

void decode(unsigned char* out, const char* in){
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    sscanf(&in[i*2], "%02x", &out[i]);
}

void md5(unsigned char* buf, const char* in, int len){
  MD5_CTX ctx;
  MD5_Init(&ctx);
  MD5_Update(&ctx, in, len);
  MD5_Final(buf, &ctx);
}

int search(const unsigned char* ans_buf, const char* salt, int size, int start, int step){
  for (int i = start; i < size; i+=step){
    char in[256];
    unsigned char buf[MD5_DIGEST_LENGTH];

    sprintf(in, "%s$%06d", salt, i);//todo

    md5(buf, in, strlen(in));
    if (strncmp(buf, ans_buf, MD5_DIGEST_LENGTH) == 0) return i;
    if (result > 0) break;
  }

  return -1;
}

int single_main(){
  unsigned char ans_buf[MD5_DIGEST_LENGTH];

  decode(ans_buf, "4b364677946ccf79f841114e73ccaf4f");
  printf("result=%d\n", search(ans_buf, "hoge", 1000000, 0, 1));
  return 0;
}

typedef struct {
  const unsigned char* ans_buf;
  const char* salt;
  int size;
  int start;
  int step;
} SearchParam;

void* invoke(void *arg){
  SearchParam *a = arg;
  int r = search(a->ans_buf, a->salt, a->size, a->start, a->step);
  if (r >= 0) result = r;
}

int main(){
  const int ThreadSize = 1;
  const char answer[] = "4b364677946ccf79f841114e73ccaf4f";
  const char salt[] = "hoge";

  pthread_t threads[ThreadSize];
  SearchParam prams[ThreadSize];
  unsigned char ans_buf[MD5_DIGEST_LENGTH];

  decode(ans_buf, answer);

  for (int i = 0; i < ThreadSize; i++){
    prams[i].ans_buf = ans_buf;
    prams[i].salt = salt;
    prams[i].size = 1000000;
    prams[i].start = i;
    prams[i].step = ThreadSize;
    pthread_create(&threads[i], NULL, invoke, &prams[i]);
  }

  for (int i = 0; i < ThreadSize; i++)
    pthread_join(threads[i], NULL);

  return 0;
}
