//
//  svm_hog.cpp
//  OpenCVSamples
//
//  Created by jonathan on 29/07/2015.
//  Copyright (c) 2015 foundry. All rights reserved.
//
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "openCVUtils.h"
#include <opencv2/ml/ml.hpp>
#include <vector>

using namespace cv;
//using namespace cv::ml;

using namespace std;

static    HOGDescriptor _hog;
static Mat _inImage, _outImage;
static const char* _windowName = "hog detector";
static float _hitThreshold = 0;
static float _scaleFactor = 2;
static float _groupThreshold = 0.0;
static int MAX_TRACKBAR = 800;
static int _trackbar = _scaleFactor * MAX_TRACKBAR/2.0;

static int imshowWithCaption(const char* windowName, Mat inImage,  const char* caption )
{
    putText( inImage, caption,
            Point( MIN(10,inImage.cols), MIN(20,inImage.rows)),
            FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255) );
    
    imshow( windowName, inImage );
    return 0;
}
//http://stackoverflow.com/questions/15339657/training-custom-svm-to-use-with-hogdescriptor-in-opencv/17118561#17118561

class LinearSVM: public CvSVM {
public:
    
    void getSupportVector(std::vector<float>& support_vector) const;
};

void LinearSVM::getSupportVector(std::vector<float>& support_vector) const {
    
    int sv_count = this->get_support_vector_count();
    //   mexPrintf("size :   %d\n",support_vector.size());
    const CvSVMDecisionFunc* df = this->decision_func;
    const double* alphas = df[0].alpha;
    double rho = df[0].rho;
    int var_count = this->get_var_count();
    support_vector.resize(var_count, 0);
    for (unsigned int r = 0; r < (unsigned)sv_count; r++) {
        float myalpha = alphas[r];
        const float* v = this->get_support_vector(r);
        for (int j = 0; j < var_count; j++,v++) {
            support_vector[j] += (-myalpha) * (*v);
        }
    }
    support_vector.push_back(rho);
}

static std::string filename(std::string prefix, int num) {
   std::string filename = num<10? prefix+"00"+to_string(num)+".png":
    num<100? prefix+"0"+to_string(num)+".png":
    prefix+to_string(num)+".png";
    filename = assetPath(filename.c_str());
    return filename;
}

static void hogDetect () {
    _inImage.copyTo(_outImage);
    vector<Rect> found;
    vector <Rect> found_filtered;
    Size padding(Size(0, 0));
    Size winStride(Size(8, 8));
    _hog.detectMultiScale(
                          _inImage //const Mat&
                          //Matrix of the type CV_8U containing an image where objects are detected.
                          , found // vector<Rect>& objects
                          //Vector of rectangles where each rectangle contains the detected object.
                          , _hitThreshold  // hit_threshold=0
                          //hit_threshold – Threshold for the distance between features and SVM classifying plane.  Usually it is 0 and should be specfied in the detector coefficients (as the last free coefficient). But if the free coefficient is omitted (which is allowed), you can specify it manually here.
                          
                          , Size(8,8)//winSize
                          //win_stride – Window stride. It must be a multiple of block stride
                          , Size(0,0)//padding
                          //padding – Mock parameter to keep the CPU interface compatibility. It must be (0,0).
                          , _scaleFactor  // double scale = 1.05
                          //scale0 – Coefficient of the detection window increase.
                          //scaleFactor - Parameter specifying how much the image size is reduced at each image scale.
                          , _groupThreshold  //group_threshold=2
                          //group_threshold – Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles. 0 means not to perform grouping. See groupRectangles() .
                          );
    
    size_t i, j;
    
    
    cvtColor( _outImage, _outImage, CV_GRAY2BGR );

    printf("found: %lu\n",found.size());
    for( i = 0; i < found.size(); i++ )
    {
        Rect r = found[i];
    
        for( j = 0; j < found.size(); j++ ) {
            //filter out overlapping rectangles
            if ( j!=i ) {
                Rect iRect =  r;
                Rect jRect = found[j];
                Rect intersectRect = (iRect & jRect);
                if (intersectRect.area()>=iRect.area()*0.9) break;
                
            }
        }
        if( j == found.size() )
         
            found_filtered.push_back(r);
    }
    for( i = 0; i < found_filtered.size(); i++ )
    {
        Rect r = found_filtered[i];
        // the HOG detector returns slightly larger rectangles than the real objects.
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.5);
        r.width = cvRound(r.width*0.3);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(_outImage, r.tl(), r.br(), cv::Scalar(0,255,0), 1);
    }
    //eliminate overlaps
    
    //imshow(_windowName, _outImage);
    string param1string = std::string("hitThreshold ") + to_string((int)_hitThreshold);
    string param2string = std::string(" groupThreshold ") + to_string((int)_groupThreshold);
    string param3string = std::string(" scaleFactor ") + to_string(_scaleFactor);
    string combinedString = param1string + param2string + param3string;
    const char* captionString = combinedString.c_str();

    imshowWithCaption(_windowName, _outImage, captionString);
    
}

static void hogTrackbarCallback (int trackbarPos, void*) {
    _trackbar = trackbarPos;
    _scaleFactor = trackbarPos/100.0;
    hogDetect();
}

static void setupHogWindow() {
    
    namedWindow( _windowName, WINDOW_AUTOSIZE );
    
    createTrackbar( "scaleFactor" //– Name of the created trackbar.
                   , _windowName
                   , &_trackbar
                   , MAX_TRACKBAR
                   , hogTrackbarCallback
                   , nullptr
                   );
}





int svm_hog (int argc, char** argv) {
    int num_files = 359+171;  //FIXED, was 359 * 171
    Size imgSize;
    imgSize.width = 30;
    imgSize.height = 30;
    Mat training_mat(num_files,imgSize.area(),CV_32FC1);
    vector<int> training_Labels;
    Mat labels(num_files,1,CV_32FC1);
    int imagenum=0;
    
    std::string filenamePrefix = "svm_hog_";
    std::string posPrefix = filenamePrefix+"pos_";
    std::string negPrefix = filenamePrefix+"neg_";


    for (int pimageNum = 0; pimageNum < 359; pimageNum++)
    {
        // reading Positive Images from directory and resize it to 30x30
        std::string file = filename(posPrefix, pimageNum);
        Mat posImage = imread(file);
        resize(posImage, posImage, imgSize);
        int ii = 0; // Current column in training_mat
        for (int i = 0; i<posImage.rows; i++) {
            for (int j = 0; j < posImage.cols; j++) {
                training_mat.at<float>(imagenum,ii++) = posImage.at<uchar>(i,j);
            }
        }
        training_Labels.push_back(1.0);
        imagenum++;//FIXED, was inside the inner loop

    }
    for (int nimageNum = 0; nimageNum < 171; nimageNum++)
    {
        // reading Nagative Images from directory and resize it to 30x30
        
        std::string file = filename(negPrefix, nimageNum);
        Mat nagImage = imread(file);
        resize(nagImage, nagImage, imgSize);

        int ii = 0; // Current column in training_mat

        
        for (int i = 0; i<nagImage.rows; i++) {
            for (int j = 0; j < nagImage.cols; j++) {
                training_mat.at<float>(imagenum,ii++) = nagImage.at<uchar>(i,j);
            }
        }
        training_Labels.push_back(-1.0);
        imagenum++;//FIXED, was inside the inner loop

    }
    
    Mat(training_Labels).copyTo(labels);
    labels.convertTo(labels, CV_32FC1);
    
    CvSVMParams SVM_params;
    SVM_params.svm_type = CvSVM::C_SVC;
    SVM_params.kernel_type = CvSVM::LINEAR; //CvSVM::LINEAR;
    SVM_params.degree = 0;
    SVM_params.gamma = 3;
    SVM_params.coef0 = 0;
    SVM_params.C = 1;
    SVM_params.nu = 0;
    SVM_params.p = 0;
    SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 10, 0.03);
    //Train SVM
    
    
    LinearSVM svmClassifier;
    svmClassifier.train(training_mat, labels, Mat(), Mat(), SVM_params);
    std::string svmFile = "svmClassifier.yml";
    svmFile = assetPath(svmFile.c_str());

    svmClassifier.save(svmFile.c_str());
    

    FileStorage fs;
    vector<float> support_vector;

    fs.open(svmFile, FileStorage::READ);
    FileNode my_svm = fs["my_svm"];
    FileNode sv = my_svm["support_vectors"];
    
    
    FileNodeIterator current = sv.begin(), it_end = sv.end(); // Go through the node
    for (; current != it_end; ++current)
    {
        FileNode item = *current;
        item >> support_vector;
    }
   
    /*
     this is a bit suspect. "support vectors" is an array of arrays, in this case with only one array. So the iterator terminates after one cycle. support_vector is correctly populated, but this does not seem to be the correct format for the hog descriptor, which breaks with this support_vector.
     
     */

    //http://stackoverflow.com/questions/22159892/opencv-how-to-use-hogdescriptordetectmultiscale-with-custom-svm
    /*
     //for comparison, no errors with this one
     static vector<float> detector = HOGDescriptor::getDefaultPeopleDetector();
     */
    //_hog = HOGDescriptor::HOGDescriptor();
    _hog.setSVMDetector(support_vector);
    
    vector< Rect> found,found_filtered;

    std::string testfile = "svm_hog_testimage.bmp";
    testfile = assetPath(testfile.c_str());
    
    _inImage=cv::imread(testfile,CV_LOAD_IMAGE_GRAYSCALE);
    Size resized;
    resized.height = 300;
    resized.width = 400;
    //resize(_inImage, _inImage, resized);
  
    setupHogWindow();

    hogDetect();
      waitKey(0);
    return 0;
}
