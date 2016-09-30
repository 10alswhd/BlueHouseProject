#include <iostream> 
 #include <opencv2/core/core.hpp> 
 #include <opencv2/highgui/highgui.hpp> 
 
 
 using namespace std; 
 using namespace cv; 
 
 
 int main() 
 { 
 Mat image; 
  string fname; 
 cout << "Enter name of file:"; 
 cin >> fname; 
 image = imread(fname,CV_LOAD_IMAGE_COLOR); 
 namedWindow("Image",WINDOW_AUTOSIZE); 
 imshow("Image",image); 
 waitKey(0); 
 return 0; 
} 
