#include "define.h" 
 
 
 void main() 
 { 
 	//The number of connected USB camera(s) 
 	const int CAM_NUM = 2; 
 
 
 	//This will hold the VideoCapture objects 
 	VideoCapture camCaptures[CAM_NUM]; 
 
 
 	//This will hold the resulting frames from each camera 
 	Mat camFrames[CAM_NUM]; 
 
 
 	//This will be used for highgui window name 
 	string labels[CAM_NUM]; 
 

 	//Initialization of VideoCaptures 
 	for (int i = 0; i < CAM_NUM; i++) 
 	{ 
 		//Init label for highgui window name 
 		char strIndex[5] = {0, }; 
 		sprintf(strIndex, "%d", i); 
 		labels[i] = "Camera " + string(strIndex); 
 
 
 		//Opening camera capture stream 
 		camCaptures[i].open(i); 
 
 
 		 
 	} 
 

 	//continous loop until 'Esc' key is pressed 
 	while (waitKey(1) != 27){ 
 		for (int i = 0; i < CAM_NUM; i++) 
 		{ 
 			//capturing frame-by-frame from each capture 
 			camCaptures[i] >> camFrames[i]; 
 
 
 			//showing the resulting frame using highgui 
 			imshow(labels[i], camFrames[i]); 
 		} 
 	} 
 
 
 	//Releasing all VideoCapture resources 
 	for (int i = 0; i < CAM_NUM; i++) 
 	{ 
 		camCaptures[i].release(); 
 	} 
 } 
