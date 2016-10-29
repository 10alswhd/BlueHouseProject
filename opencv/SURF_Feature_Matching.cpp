#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "opencv2\opencv.hpp"
#include <opencv2\nonfree\features2d.hpp>

using namespace std;
using namespace cv;

int main()
{
        Mat img_1, img_2;
  //image = imread("lena.jpg",1);
	img_1= imread("Matrix1_small.jpg", CV_LOAD_IMAGE_GRAYSCALE );
	img_2= imread("RoboticsMatrix.jpg", CV_LOAD_IMAGE_GRAYSCALE );
	if(img_1.empty()||img_2.empty())
	{
	    cout <<  "Could not open or find the image" << std::endl ;
        return -1;
	}

 	/// Resize
        resize(img_1,img_1,Size(0,0),0.15,0.15,INTER_LINEAR);
	resize(img_2,img_2,Size(0,0),0.2,0.2,INTER_LINEAR);
	
	imshow("Image 1", img_1);
	imshow("Image 2", img_2);

	// Step -1, Detect keypoints using SURF detector
	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);

	vector<KeyPoint> keypoints_1, keypoints_2;
	detector.detect(img_1, keypoints_1);
	detector.detect(img_2, keypoints_2);
	
	Mat img_keypoints_1; 

        drawKeypoints( img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	imshow("Image1 KeyPoints", img_keypoints_1);
	//imwrite("Lena Keypoints.jpg",img_keypoints_1);
	// Step -2, Calculate descriptors (feature vector)
	SurfDescriptorExtractor extractor;

	Mat descriptor_1, descriptor_2;

	extractor.compute(img_1,keypoints_1,descriptor_1);
	extractor.compute(img_2,keypoints_2,descriptor_2);

	//step - 3, Matching descriptor vectors with a brute force mathcher

	double t = (double)getTickCount();

	BFMatcher matcher(NORM_L2);

	vector<DMatch> matches;
	matcher.match(descriptor_1, descriptor_2,matches);

	t = ((double)getTickCount() - t)/getTickFrequency();
	cout << " Brute Force Matching Time (senconds):  " << t<<endl;

	// maches  with Flann Based Matching.
	t = (double)getTickCount();
	FlannBasedMatcher matcher2;
	vector<DMatch> matches2;
	matcher2.match(descriptor_1,descriptor_2,matches2);

	t = ((double)getTickCount() - t)/getTickFrequency();
	cout << " Flann Based Matching Time (senconds):  " << t<<endl;

	//--Draw Matches
	Mat img_matches;
	drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,img_matches);

	//-- Show Detected Matches
	imshow("Matches Brute",img_matches);
	//--Draw Matches
	Mat img_matches2;
	drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches2,img_matches2);

	//-- Show Detected Matches
	imshow("Matches Flann",img_matches2);
	// quick calcualation of max and min distances between keypoints
	double max_dist=0; double min_dist = 100;
	for (int i =0; i < descriptor_1.rows;i++)
	{
		double dist = matches2[i].distance;
		if(max_dist<dist) max_dist = dist;
		if(min_dist>dist) min_dist = dist;
	}

	vector< DMatch> good_matches;
	for (int i=0;i<descriptor_1.rows;i++)
	{
		if( matches2[i].distance<3*min_dist)
			good_matches.push_back(matches2[i]);
	}
	// Draw Good Matches
	Mat img_goodmatches;
	drawMatches(img_1,keypoints_1,img_2,keypoints_2,good_matches,img_goodmatches,Scalar::all(-1),Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow( "Good Matches", img_goodmatches );
	for( int i = 0; i < good_matches.size(); i++ )
	{ 
		printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx ); 
	}

	// Localize the object
	vector<Point2f> obj;
	vector<Point2f> scene;
	for( int i = 0; i < good_matches.size(); i++ )
	{
		obj.push_back(keypoints_1[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_2[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography( obj,scene,CV_RANSAC);
	vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0,0);
	obj_corners[1] = cvPoint(img_1.cols,0);
	obj_corners[2] = cvPoint(img_1.cols,img_1.rows);
	obj_corners[3] = cvPoint(0,img_1.rows);

	
	std::vector<Point2f> scene_corners(4);

	Mat img_object = img_1.clone();

    	perspectiveTransform( obj_corners, scene_corners, H);
 	 img_matches = img_goodmatches;
  //-- Draw lines between the corners (the mapped object in the scene - image_2 )
 	line( img_matches, scene_corners[0] + Point2f( img_object.cols, 0), scene_corners[1] + Point2f( img_object.cols, 0), Scalar(0, 255, 0), 4 );
 	line( img_matches, scene_corners[1] + Point2f( img_object.cols, 0), scene_corners[2] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
 	line( img_matches, scene_corners[2] + Point2f( img_object.cols, 0), scene_corners[3] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );
  	line( img_matches, scene_corners[3] + Point2f( img_object.cols, 0), scene_corners[0] + Point2f( img_object.cols, 0), Scalar( 0, 255, 0), 4 );

  //-- Show detected matches
  	imshow( "Good Matches & Object detection", img_matches );

// imwrite("Lena SURF Matches.jpg",img_matches);
	waitKey(0);
	return 0;
}
