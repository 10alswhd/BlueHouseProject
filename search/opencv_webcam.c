#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// from http://d.hatena.ne.jp/ryousanngata/20101209/1291903743
#include <windows.h>
#define dlopen(P,G) (void*)LoadLibraryEx(P,NULL,LOAD_WITH_ALTERED_SEARCH_PATH)
#define dlsym(D,F) (void*)GetProcAddress((HMODULE)D,F)
#define dlclose(D) FreeLibrary((HMODULE)D)

int main(int argc, char **argv)
{
  void *handle;
  const char* text = "test";
  void *cap, *frame;

  handle = dlopen("opengl32.dll", RTLD_LAZY);
  if (handle == NULL) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }//

  handle = dlopen("D:/opencv3/opencv/build/x64/vc12/bin/opencv_world300.dll", RTLD_LAZY);
  if (handle == NULL) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }

  int (*cvNamedWindow)(const char*,int) = dlsym(handle, "cvNamedWindow");
  void (*cvDestroyAllWindows)() = dlsym(handle, "cvDestroyAllWindows");
  void (*cvShowImage)(const char*, void*) = dlsym(handle, "cvShowImage");
  int (*cvWaitKey)(int) = dlsym(handle, "cvWaitKey");
  void* (*cvCreateCameraCapture)(int) = dlsym(handle, "cvCreateCameraCapture");
  void* (*cvQueryFrame)(void*) = dlsym(handle, "cvQueryFrame");
  int (*cvSaveImage)(const char*, void*, int*) = dlsym(handle, "cvSaveImage");
  void (*cvReleaseCapture)(void**) = dlsym(handle, "cvReleaseCapture");

  cap = cvCreateCameraCapture(-1);
  cvNamedWindow(text,0);
  while (1) {
    frame = cvQueryFrame(cap);
    cvShowImage(text, frame);
    int c = cvWaitKey(2);
    if (c == 0x1b)
      break;
    if (c == 0x20) {
      cvSaveImage("snap.jpg", frame, NULL);
      break;
    }
  }
  cvReleaseCapture(&cap);
  cvDestroyAllWindows();
  dlclose(handle);
  // int (*func)(char*,FUNCPTR) = dlsym(handle, "boot");
}
