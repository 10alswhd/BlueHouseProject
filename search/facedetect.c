/** Basic OpenCV example for face detecion.
 *  Handles a still image or a video file.
 **/
#include <stdio.h>
#include <cv.h>
#include <highgui.h>

void detect_faces (IplImage*, CvHaarClassifierCascade*, CvMemStorage*);
void cleanup (char*, CvHaarClassifierCascade*, CvMemStorage*);
void print_help (char*);

#define OPENCV_DATA "/home/billy/src/opencv/opencv/data/haarcascades/"
char *classifer = OPENCV_DATA "haarcascade_frontalface_default.xml";

int main(int argc, char** argv) {
  if (argc != 2) print_help(argv[0]); //check usage
  //declare
  IplImage* image;
  CvHaarClassifierCascade* cascade = 0;
  CvMemStorage* storage = 0;
  char* window_name = "haar window";
  
  //initialize
  cascade = (CvHaarClassifierCascade*) cvLoad(classifer, 0, 0, 0 );
  storage = cvCreateMemStorage(0);
  //validate
  assert(cascade && storage);

  //create window
  cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
  
  //given an image?
  image = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);
  if (image) {
    detect_faces(image, cascade, storage); //detect and draw
    cvShowImage(window_name, image);       //display
    
    cvWaitKey(0);  //wait for key press

    //release resources and exit
    cvReleaseImage(&image);
    cleanup(window_name, cascade, storage);
    exit(0);
  }

  //or a video file?
  CvCapture* capture = cvCaptureFromFile(argv[1]);
  if (capture) {
    int key;
    //run loop, exit on ESC
    while (key != 27) {
      image = cvQueryFrame(capture);  //get frame from video
      if (!image) break;
      
      detect_faces(image, cascade, storage); //detect and draw
      cvShowImage(window_name, image);       //display

      key = cvWaitKey(10);  //check key
    }
    //free memory
    cvReleaseCapture(&capture);
  }

  //release resources and exit
  cleanup(window_name, cascade, storage);
}

void detect_faces (IplImage* image,
                   CvHaarClassifierCascade* cascade,
                   CvMemStorage* storage) {
  
  //get a sequence of faces in image
  CvSeq *faces = cvHaarDetectObjects(image, cascade, storage,
     1.1,                       //increase search scale by 10% each pass
     3,                         //drop groups of fewer than n detections
     CV_HAAR_DO_CANNY_PRUNING,  //skip regions unlikely to contain a face
     cvSize(0,0));              //smallest face to search for, use XML default

  //draw rectangle outline around each detection
  int i;
  for(i = 0; i < (faces ? faces->total : 0); i++ ) {
    CvRect *r = (CvRect*) cvGetSeqElem(faces, i);
    CvPoint top_left = { r->x, r->y };
    CvPoint bot_right = { r->x + r->width, r->y + r->height };
    cvRectangle(image, top_left, bot_right, CV_RGB(0,255,0), 3, 4, 0);
  }
}

void cleanup (char* name,
              CvHaarClassifierCascade* cascade,
              CvMemStorage* storage) {
  //cleanup and release resources
  cvDestroyWindow(name);
  if(cascade) cvReleaseHaarClassifierCascade(&cascade);
  if(storage) cvReleaseMemStorage(&storage);
}

void print_help (char* name) {
  printf("Usage: %s [image|video]\n", name);
  exit(-1);
}
