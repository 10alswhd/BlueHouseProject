 #include <opencv2/imgproc/imgproc.hpp> 
 #include "opencv2/highgui/highgui.hpp" 
 #include <iostream> 
 
 
 using namespace cv; 
 using namespace std; 
 
 
 int main( int argc, char** argv ) 
 { 
 	 
 	// This tutorial will used the newly defined C++ interfaces which use memory managed containers instead of the  
 	// older IplImage format which was based on the older C interfaces and had issues of memory management. 
 	Mat src,result;	 
 	int size; 
 	cout<<"Enter the kernel size for the operations\n"; 
 	cin>>size; 
 
 
 	namedWindow( "source image", CV_WINDOW_AUTOSIZE ); 
 
 
 	src = imread(argv[1],-1); 
 	imshow( "source image", src ); 
 
 
 
 
 	/* 
 	Apply blur or averaging filter: 
 	Size( w,h ): Defines the size of the kernel to be used ( of width w pixels and height h pixels) 
 	Point(-1, -1): Indicates where the anchor point (the pixel evaluated) is located with respect to the neighborhood. 
 	If there is a negative value, then the center of the kernel is considered the anchor point. 
 	*/ 
 
 
 	cout<<"Normalized blurring the image\n"; 
 	namedWindow( "normalized image", CV_WINDOW_AUTOSIZE ); 
 	blur(src, result, Size(size,size),Point(-1,-1)); 
 	imshow("normalized image", result); 
 
 
 	cout<<"Gaussian blurring the image\n"; 
 	namedWindow("gaussian blurred image", CV_WINDOW_AUTOSIZE ); 
 	GaussianBlur(src,result,Size(size,size),0,0); 
 	imshow("gaussian blurred image", result); 
 	 
 	cout<<"median blurring the image\n"; 
 	namedWindow("median blurred image", CV_WINDOW_AUTOSIZE ); 
 	medianBlur ( src, result, size ); 
 	imshow("median blurred image", result); 
 
 
 	cout<<"bilateral filtering the image\n"; 
 	namedWindow("bilateral blurred image", CV_WINDOW_AUTOSIZE ); 
 	bilateralFilter ( src, result, size, size*2, size/2 ); 
 	imshow("bilateral blurred image", result); 
  waitKey(); 
 
 
 } 
