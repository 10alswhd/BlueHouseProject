 #include <opencv2\core\core.hpp> 
 #include<opencv2\highgui\highgui.hpp> 
 #define TEST_IMAGE "D:\\opencv.png" 
 
 
 int main(){ 
 	// Open the file. 
 	cv::Mat img = cv::imread(TEST_IMAGE); 
 
 
 	// Display the image. 
 	cv::namedWindow("Image:", CV_WINDOW_AUTOSIZE); 
 	cv::imshow("Image:", img); 
 
 
 	// Wait for the user to press a key in the GUI window. 
 	cv::waitKey(0); 
 
 
 	// Free the resources. 
 	cv::destroyWindow("Image:"); 
 
 
 	return 0; 
 } 
