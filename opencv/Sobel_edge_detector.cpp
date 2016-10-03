#include <iostream> 
 #include <stdio.h> 
 #include <stdlib.h> 
 
 #include "opencv2/highgui/highgui.hpp" 
 #include "opencv2/imgproc/imgproc.hpp" 
 #include "opencv2/core/core.hpp" 
 
 
 using namespace std; 
 using namespace cv; 
 #include "Functions.h" 
 int main() 
 { 
   Mat image; 
 	//image = imread("lena.jpg",1); 
 	image = imread("building.jpg",1); 
 	if(image.empty()) 
 	{ 
 	    cout <<  "Could not open or find the image" << std::endl ; 
         return -1; 
 	} 
 
 
 	/// Convert it to gray 
   cvtColor( image, image, CV_RGB2GRAY ); 
 	resize(image,image,Size(0,0),0.5,0.5,INTER_LINEAR); 
 	namedWindow("Image", CV_WINDOW_AUTOSIZE ); 
 	imshow("Image", image); 
 	 /// Generate grad_x and grad_y 
  	Mat grad_x, grad_y; 
 	Mat abs_grad_x, abs_grad_y; 
 	int scale = 1; 
 	int delta = 0; 
 	int ddepth = CV_16S; 
  Mat grad; 
   /// Gradient X 
   //Scharr( image, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT ); 
 	Sobel( image, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT ); 
 	convertScaleAbs( grad_x, abs_grad_x ); 
 
 
   /// Gradient Y 
   // Scharr( image, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT ); 
   Sobel( image, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT ); 
   convertScaleAbs( grad_y, abs_grad_y ); 
 	/// Total Gradient (approximate) 
 
 
 	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad ); 
 	namedWindow("ImageSobel", CV_WINDOW_AUTOSIZE ); 
 	imshow( "ImageSobel", grad ); 
 
 
 	namedWindow("ImageSobelGx", CV_WINDOW_AUTOSIZE ); 
 	imshow( "ImageSobelGx", abs_grad_x ); 
 

 	namedWindow("ImageSobelGy", CV_WINDOW_AUTOSIZE ); 
 	imshow( "ImageSobelGy", abs_grad_y ); 
 
 
 	waitKey(0); 
 	return 0; 
 } 
