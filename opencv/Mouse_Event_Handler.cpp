#include "opencv2/opencv.hpp" 
 #include <iostream> 
 
 
 using namespace cv; 
 using namespace std;  
 
 Mat frame; 
 
 
 void mouseEventHandler(int event, int x, int y, int flags, void* param) 
 { 
 	if  ( event == EVENT_LBUTTONDOWN ) 
 	{ 
 		cout << "Left button of the mouse is clicked DOWN - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if  ( event == EVENT_LBUTTONUP ) 
 	{ 
 		cout << "Left button of the mouse is clicked UP - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if  ( event == EVENT_LBUTTONDBLCLK ) 
 	{ 
 		cout << "Left button of the mouse is double clicked - position (" << x << ", " << y << ")" << endl;		 
 	} 
 	else if  ( event == EVENT_RBUTTONDOWN ) 
 	{ 
 		cout << "Right button of the mouse is clicked DOWN - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if  ( event == EVENT_RBUTTONUP ) 
 	{ 
 		cout << "Right button of the mouse is clicked UP - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if  ( event == EVENT_RBUTTONDBLCLK ) 
 	{ 
 		cout << "Right button of the mouse is double clicked - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if  ( event == EVENT_MBUTTONDOWN ) 
 	{ 
 		cout << "Middle button of the mouse is clicked DOWN - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if  ( event == EVENT_MBUTTONUP ) 
 	{ 
 		cout << "Middle button of the mouse is clicked UP - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if  ( event == EVENT_MBUTTONDBLCLK ) 
 	{ 
 		cout << "Middle button of the mouse is double clicked - position (" << x << ", " << y << ")" << endl; 
 	} 
 	else if ( event == EVENT_MOUSEMOVE ) 
 	{ 
 		cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl; 
 	} 
 } 
 
 
 void showWindow() 
 { 
   	//Create an autoresize window 
 	namedWindow("My Window", 1); 
 
 
 	//Set the callback function for any mouse event 
 	setMouseCallback("My Window", mouseEventHandler, NULL); 
 
 
 	//Show the image 
 	frame = cv::imread("0001_.jpg"); 
 	imshow("My Window", frame); 
 
 
 	//Wait until user press some key 
 	waitKey(0); 
 } 
