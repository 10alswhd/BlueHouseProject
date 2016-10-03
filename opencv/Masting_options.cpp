Mat src1 = Mat(512, 512, CV_8UC3, Scalar(127, 0, 0)); 
 	Mat src2 = Mat(512, 512, CV_8UC3, Scalar(0, 0, 127)); 
  	Mat dst = Mat::zeros(512, 512, CV_8UC3); 
 	Mat mask = Mat::zeros(512, 512, CV_8UC1); 
 	 
 	circle(mask, Point(mask.rows / 2, mask.cols / 2), 128, Scalar(255), -1, 8, 0); 
 	 
 	 
 	add(src1, src2, dst, mask);  
 	imshow("Normal add", dst); 
 	waitKey(); 
 	 
 	src1.copyTo(dst,mask); // Note src and dst cannot be the same 
 	imshow("copyTo", dst); 
 	waitKey(); 
 	 
 	//grey scale with bitwise_and ? 
