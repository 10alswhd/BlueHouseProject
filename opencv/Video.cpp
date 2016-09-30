 #include <stdio.h> 
 #include <opencv\cv.h> 
 #include <opencv\cxcore.h> 
 #include <opencv\highgui.h> 
 
 
 int main() 
 { 
   IplImage* pFrame = NULL;   
   IplImage* pFrameNew = NULL; 
 
 
   CvCapture* pCapture = NULL;  
   CvVideoWriter* pWriter = NULL;  
 
 
   int nFrmNum = 0; 
 
 
   cvNamedWindow("Video", 1); 
   cvNamedWindow("Process", 1); 
   
   cvMoveWindow("Video", 30, 0); 
   cvMoveWindow("Process", 360, 0); 
 
 
   if( !(pCapture = cvCaptureFromFile("video.avi")) ) 
 	   printf("Video Capture Wrong!\n"); 
 
 
    int fps=cvGetCaptureProperty(pCapture,CV_CAP_PROP_FPS); 
    int width=cvGetCaptureProperty(pCapture,CV_CAP_PROP_FRAME_WIDTH); 
    int height=cvGetCaptureProperty(pCapture,CV_CAP_PROP_FRAME_HEIGHT); 
    int count=cvGetCaptureProperty(pCapture,CV_CAP_PROP_FRAME_COUNT); 
    printf("%d X %d, %d FPS, %d frames!\n",width,height,fps,count); 
 
 
    if(!(pWriter = cvCreateVideoWriter("Save.avi", -1, 40, cvSize(width,height), 1)) ) 
      printf("Video Writer Wrong!\n"); 
 
 
    pFrameNew=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,3); 
     
    
   while(pFrame = cvQueryFrame( pCapture )) 
   { 
 	  nFrmNum++; 
 	  cvShowImage("Video", pFrame); 
        
 	  cvSmooth(pFrame, pFrameNew, CV_GAUSSIAN, 9, 0, 0); 
 
 
 	  cvShowImage("Process", pFrameNew); 
 	   
 	  cvWriteFrame(pWriter, pFrameNew); 

 
 	  cvWaitKey(10); 
   } 
 
 
   cvWaitKey(); 
 
 
   cvDestroyWindow("Video"); 
   cvDestroyWindow("Process"); 
 
 
   cvReleaseImage(&pFrameNew); 
   cvReleaseVideoWriter(&pWriter); 
   cvReleaseImage(&pFrame);   
   cvReleaseCapture(&pCapture); 
   return 0; 
 } 
