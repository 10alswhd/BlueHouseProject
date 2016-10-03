void match(Mat &a, Mat &b) 
 { 
 
 
 	Mat r; 
 	matchTemplate(a, b, r, CV_TM_SQDIFF_NORMED); 
 	double minVal; double maxVal; Point minLoc; Point maxLoc; 
 	Point matchLoc; 
 
 
 	minMaxLoc(r, &minVal, &maxVal, &minLoc, &maxLoc, Mat()); 
 	 
 	rectangle(a, maxLoc, Point(maxLoc.x + b.cols, maxLoc.y + b.rows), Scalar(255)); 
 	imshow("1", r); 
 	imshow("2", a); 
 } 
