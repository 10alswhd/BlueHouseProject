
#include <Windows.h>
#include <Ole2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <WinBase.h>

// Kinect 
#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>

// Opencv
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <core.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

#define pictureMode false // true: take pictures for training 
#define cropMode false // true: crop the faces in the images
#define pictureOwner "Lady_Big2" // name the picture owner
/* Image setting */
#define imgWidth 640
#define imgHeight 480
#define imgWidthBig 1280
#define imgHeightBig 960

#define useExistingModel true // train new face rec. model or load existing. 
#define recognizerThreshold 125.0
#define writeToVideo false // true: record the operation
bool useBigPic = true; // true: use 1280x960 images for better accuracy. false: 640x480 

string modelName = "fisher"; // name the face rec. model 

// Kinect variables 
HANDLE rgbStream;
HANDLE skeletonStream;
INuiSensor* sensor; 
NUI_SKELETON_FRAME* nextSkeletonFrame;
bool *m_bArrSkeletonsTracked;



// Program variables 
IplImage* kinectColorImage = cvCreateImage(cvSize(imgWidth, imgHeight), IPL_DEPTH_8U, 4); 
IplImage* kinectColorImageBig = cvCreateImage(cvSize(1280, 960), IPL_DEPTH_8U, 4);
IplImage* kinectColorImageTiny = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 4);

string output_folder = "Images";//"C:/attFaces/frec"; //for face recog only
string fn_csv = "croppedImagesBig/frecAll.txt"; //path to the csv file. 
//string fn_csv = "Images/BigImages.txt"; //path to the csv file. 
string fn_haar = "C:\\opencv243\\data\\haarcascades\\haarcascade_frontalface_alt.xml"; //.._default.xml";
string fn_lbp = "C:\\opencv243\\data\\lbpcascades\\lbpcascade_frontalface.xml"; //.._profileface.xml, lbpcascade_frontalface.xml
string eye_cascade_name = "C:/opencv243/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";//haarcascade_mcs_eyepair_small";//haarcascade_eye_tree_eyeglasses.xml";


vector<Mat> images;//These vectors hold the images and corresponding labels.
vector<int> labels;

int training_im_width; // for video face recog.
int training_im_height;
bool showResult = false; // true: show the eigenvalues, eigenvectors, etc, false: save resuts in files 

Ptr<FaceRecognizer> model; // Face recognizer model for eigenfaces. 
CascadeClassifier haar_cascade; // cascade classifier (to detect faces, or what in needed)
CascadeClassifier eye_cascade; // Eye detector 

int *sklBelongsToFaceId;
bool *skeletonHasFaceId;


/*
  Initialize the kinect.  
*/
bool initKinect() {
	//get a working kinect sensor 
	int numSensors;
	if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1) return false;
	if (NuiCreateSensorByIndex(0, &sensor) < 0) return false;

	nextSkeletonFrame = new NUI_SKELETON_FRAME;
	m_bArrSkeletonsTracked = new bool[NUI_SKELETON_COUNT];
	
	// init face data holder  
	skeletonHasFaceId = new bool [NUI_SKELETON_COUNT]; 
	sklBelongsToFaceId = new int [NUI_SKELETON_COUNT]; // for each skeleton, a face label will be assigned, if mathched. 
	
	for (int i = 0; i < NUI_SKELETON_COUNT; ++i )
	{
		m_bArrSkeletonsTracked[i] = false;
		skeletonHasFaceId[i] = false;
		sklBelongsToFaceId[i] = -1;
	}


	// Initialize sensor 
	DWORD nuiFlags = NUI_INITIALIZE_FLAG_USES_DEPTH | NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_SKELETON;
		sensor->NuiInitialize(nuiFlags);
	NUI_IMAGE_RESOLUTION kinect_resolution;
	useBigPic? kinect_resolution = NUI_IMAGE_RESOLUTION_1280x960 : kinect_resolution = NUI_IMAGE_RESOLUTION_640x480;
	// Get Color Data 
		sensor->NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, // Depth camera or rgb camera ?
		kinect_resolution	,//NUI_IMAGE_RESOLUTION_640x480, // Image resolution 
		0,		// Image stream flags, e.g. near mode
		2,		// Number of frames to buffer
		NULL,	// Event Handle 
		&rgbStream);
	// Get Skeleton Data
	sensor->NuiImageStreamOpen(
		HasSkeletalEngine(sensor) ? NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX : NUI_IMAGE_TYPE_DEPTH,
		NUI_IMAGE_RESOLUTION_640x480, // Change? to 640x480 later.
		0,
		2,
		NULL,
		&skeletonStream);
	cout <<"Kinect initialized!\n";
	return sensor;
}

/*
  Retrieves the RGB image of the kinect. 
*/
void getKinectColorData(IplImage* dest) {
	NUI_IMAGE_FRAME imageFrame;
	NUI_LOCKED_RECT lockedRect;
	if (sensor->NuiImageStreamGetNextFrame(rgbStream,0, &imageFrame) < 0) return; 
	INuiFrameTexture* texture = imageFrame.pFrameTexture;
	texture->LockRect(0, &lockedRect, NULL, 0);
	if (lockedRect.Pitch != 0)
	{
		cvSetData(dest, static_cast<BYTE *>(lockedRect.pBits), 
			dest->widthStep);
	}
	texture->UnlockRect(0);
	sensor->NuiImageStreamReleaseFrame(rgbStream, &imageFrame);
}

/*
  Retrieves the kinect's skeleton data 
*/
void getKinectSkeletalData() {

	bool bFoundSkeleton = false;
	float fClosestDistance = 0; 

	if (SUCCEEDED(sensor->NuiSkeletonGetNextFrame(0, nextSkeletonFrame))) {
		for (int i = 0; i  < NUI_SKELETON_COUNT; i++) {
			if (nextSkeletonFrame->SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED) // might need revision : && m_bAppTracking is ommited 
			{
				if ( !m_bArrSkeletonsTracked[i] )
				{
					cout << " * Skeleton " << i << " found at " << nextSkeletonFrame->SkeletonData[i].Position.z
						<< " meters from camera, " << (int) (clock() / CLOCKS_PER_SEC) << " seconds after startup.\n\n";
					if (fClosestDistance == 0 || fClosestDistance > nextSkeletonFrame->SkeletonData[i].Position.z )
					{
						fClosestDistance = nextSkeletonFrame->SkeletonData[i].Position.z;
					}
					m_bArrSkeletonsTracked[i] = true;

				}
				bFoundSkeleton = true;
			}
			else if (m_bArrSkeletonsTracked[i])  {
				cout << " * Skeleton " << i << " lost.\n\n";
				m_bArrSkeletonsTracked[i] = false;
				skeletonHasFaceId[i] = false; 
			}
		}
	
	}

	// no skeletons!
	if ( !bFoundSkeleton) {
		return;
	}

	// smooth out the skeleton 
	sensor->NuiTransformSmooth(nextSkeletonFrame, NULL);

}

/*
  Scales the skeleton's 20 joints to the corresponding actual points in the RGB image.   
*/
void scaleTo(Vector4 aPoint, int *x, int *y) {

	float fx = 0, fy = 0;
	NuiTransformSkeletonToDepthImage(aPoint, &fx, &fy);
	long l_x =0, l_y = 0;
	NuiImageGetColorPixelCoordinatesFromDepthPixel(NUI_IMAGE_RESOLUTION_640x480,
													NULL, 
													(long) fx, 
													(long) fy,
													NULL,
													&l_x,
													&l_y);
	*x = (int) l_x;
	*y = (int) l_y;
													
}

/*
	Capture and save the images in a folder with th same name as the picture owner. 
	These pictures will be used to crop faces to train the face recog. model. 
*/
void saveImages(string person){
	//create a folder named person 
	//
	cout << 
		"*************************************************\n" << 
		"* Saving images for training purpose.\n"<< 
		"* Face to the camera and ";

	system("pause");
	string image_folder = "Images/";
	image_folder.append(person.c_str());
	// create destination dir for images
	CreateDirectory(image_folder.c_str(), NULL);
	
	//IplImage* kinectImg = cvCreateImage(cvSize(imgWidth,imgHeight), IPL_DEPTH_8U, 4);
	IplImage* kinectImgBig = cvCreateImage(cvSize(imgWidthBig,imgHeightBig), IPL_DEPTH_8U, 4);
	
	for (int i = 0; i < 150 ; i++) {
		getKinectColorData(kinectImgBig);
		Mat image(kinectImgBig);
		if (image.empty()) continue;
		
		string fname = format("%s/%s/%s_%d.jpg", output_folder.c_str(), person.c_str(), person.c_str(), i);
		//cout << "appended "<< fname<<endl;
		//imwrite(fname, image);
		imwrite(fname, image);
		namedWindow(fname, CV_WINDOW_AUTOSIZE);
		imshow(fname, image);
		cout << "Image " << i<< " saved. Press a key to continue, Escape to end." << endl;
		char key = (char)waitKey(0);
		if (key == 27)
			return;
		destroyWindow(fname);
	}

	//cvReleaseImage(&kinectImgBig);
	return;
}

/* 
  Finds and crops the faces from the captured images. These cropped faces will be used in model training. 
*/
Mat CropFaces( Mat frame )
{
	Mat tFrame = frame.clone();
	std::vector<Rect> faces;
	Mat frame_gray;
	Mat cropped;

	cvtColor(frame, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray);

	// detect faces 
	haar_cascade.detectMultiScale(frame_gray, faces, 1.1, 2,
								  0|CV_HAAR_SCALE_IMAGE, Size(30,30) );

	for (int i = 0; i < faces.size(); i++ )
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, 
				 Scalar(255, 0, 255), 4, 8, 0);
		cropped = tFrame (faces[i] );
	}
	//show the crooped face 
	imshow("Face", frame);
	waitKey(0);
	return cropped;
}

/* 
  Histogram normalize the image. 
*/
static Mat norm_0_255(InputArray _src){
	Mat src = _src.getMat();
	//create and return normalized image:
	Mat dst;
	switch(src.channels()){
	case 1: 
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}
//
// Calculates the TanTriggs Preprocessing as described in:
//
//      Tan, X., and Triggs, B. "Enhanced local texture feature sets for face
//      recognition under difficult lighting conditions.". IEEE Transactions
//      on Image Processing 19 (2010), 1635\96650.
//
// Default parameters are taken from the paper.
//
Mat tan_triggs_preprocessing(InputArray src,
        float alpha = 0.1, float tau = 10.0, float gamma = 0.2, int sigma0 = 1,
        int sigma1 = 2) {

    // Convert to floating point:
    Mat X = src.getMat();
    X.convertTo(X, CV_32FC1);
    // Start preprocessing:
    Mat I;
    pow(X, gamma, I);
    // Calculate the DOG Image:
    {
        Mat gaussian0, gaussian1;
        // Kernel Size:
        int kernel_sz0 = (3*sigma0);
        int kernel_sz1 = (3*sigma1);
        // Make them odd for OpenCV:
        kernel_sz0 += ((kernel_sz0 % 2) == 0) ? 1 : 0;
        kernel_sz1 += ((kernel_sz1 % 2) == 0) ? 1 : 0;
        GaussianBlur(I, gaussian0, Size(kernel_sz0,kernel_sz0), sigma0, sigma0, BORDER_CONSTANT);
        GaussianBlur(I, gaussian1, Size(kernel_sz1,kernel_sz1), sigma1, sigma1, BORDER_CONSTANT);
        subtract(gaussian0, gaussian1, I);
    }

    {
        double meanI = 0.0;
        {
            Mat tmp;
            pow(abs(I), alpha, tmp);
            meanI = mean(tmp).val[0];

        }
        I = I / pow(meanI, 1.0/alpha);
    }

    {
        double meanI = 0.0;
        {
            Mat tmp;
            pow(min(abs(I), tau), alpha, tmp);
            meanI = mean(tmp).val[0];
        }
        I = I / pow(meanI, 1.0/alpha);
    }

    // Squash into the tanh:
    {
        for(int r = 0; r < I.rows; r++) {
            for(int c = 0; c < I.cols; c++) {
                I.at<float>(r,c) = tanh(I.at<float>(r,c) / tau);
            }
        }
        I = tau * I;
    }
    return I;
}

/*
  Reads a csv file containing training images as well as corresponding labels. 
*/

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';'){
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given file name";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			Mat img = imread(path,0);
			//imshow("Image", img);
			//waitKey(0);
			//Mat processed = tan_triggs_preprocessing(img);
			//processed = norm_0_255(processed);
			images.push_back(img);
			labels.push_back(atoi(classlabel.c_str()));
		}
	}

}


/*
  Returns true if the skeleton with specified ID is available.
*/
bool skeletonAvailable(int skltnId) 
{
	return m_bArrSkeletonsTracked[skltnId]; 
}

/*
  Checks if a face label is associated with the specified skeleton. 
*/
bool skeletonHasFaceLabel(int skeletonId)
{
	return skeletonHasFaceId[skeletonId];
}

/*
  Returns the label associated to the skeleton. 
*/
int getSkeletonFaceLabel(int skeletonId) 
{
	return sklBelongsToFaceId[skeletonId];
}

/*
  Draws the given skeleton joints on the given Mat image dest. If drawLabel == true, also shows the associated label along with a circle on the head position.
*/
void drawSkeletonByID(int id, Mat *dest, bool drawLabel) 
{
	/*
	 - id : skeleton id 
	 - *dest : destination image joints to be drawn
	 - drawLabel : true ? show assigned skltn label : do not show label 
	*/
	CvPoint jointPos = cvPoint(200,200);
	int xs = 0, ys = 0;
	for (int i = 0; i < NUI_SKELETON_COUNT; ++i) {
		if ( i == id ){ // draw selected skeleton only  
			if (nextSkeletonFrame->SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED) {
				if ( !drawLabel ) { //show all joints 
					for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; ++j) {
						scaleTo(nextSkeletonFrame->SkeletonData[i].SkeletonPositions[j], &xs, &ys);
						jointPos.x = xs;
						jointPos.y = ys;
						circle(*dest, jointPos, 10, CV_RGB(235,30,0),-1);
					}
				}
				else // Draw head joint only with its label 
				{
					scaleTo(nextSkeletonFrame->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD], &xs, &ys);
					jointPos.x = xs;
					jointPos.y = ys;
					circle(*dest, jointPos, 30, CV_RGB(235,30,220),2);
					int predictedLabel = getSkeletonFaceLabel(i);
					if ( predictedLabel == -1 ) // face not detected 
						return;
					// Create the text we will annotate the face with 
					string box_text = format("SID=%d", predictedLabel);
					//calculate the position of the annotated text:
					int pos_x = std::max(xs - 40, 0);
					int pos_y = std::max(ys - 40, 0);
					// Put the text in the image 
					putText(*dest, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(235,30,0), 2.0);
				}
			}
		}
	}
}


/*
  Assigns the given label to the corresponding head position in the skeleton data.  
*/
void assignFaceToSkeleton(Point headPoint, int fLabel) 
{
	int x1 = 0 ,y1 = 0; 

	for (int i = 0 ; i < NUI_SKELETON_COUNT; i++ )
	{
		float dThreshold = 15; // distance :50
		if (m_bArrSkeletonsTracked[i] && !skeletonHasFaceLabel(i))  // if skeleton is tracked, and not has label yet:
		{
			// obtain the head joint position coordiates
			x1 = (int) nextSkeletonFrame->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].x;
			y1 = (int) nextSkeletonFrame->SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].y;
			// see if any of detected face coordinates mathes(close enough)
			float dist = sqrt ((float) ((x1 - headPoint.x)^2 + (y1 - headPoint.y)^2));
			if (dist <= dThreshold)
			{ 
				dThreshold = dist; 
				skeletonHasFaceId[i] = true;
				sklBelongsToFaceId[i] = fLabel;
			}

		}
	}
	return;
}

/*
  Performs a face detection in the given image and finds the faces. 
*/
void detecFaces(Mat *original)
{
	/* Recognition */
	//convert current image to grayscale
	Mat gray;
	cvtColor(*original, gray, CV_BGR2GRAY);
		
	//find the faces in the frame
	vector< Rect_<int> > faces;
	CvPoint faceCenter = cvPoint(0,0); // Detected face coordinates in RGB image.

	/* To speed up: */
	//1. reduce the size of the gray image before feeding to haar_cascade  if the faces are much larger than 24x24 pixels:
	//find:small_image at  http://www710.univ-lyon1.fr/~bouakaz/OpenCV-0.9.5/docs/ref/OpenCVRef_Experimental.htm
	int downgradeScale = 2; // subject to change to 4? if using 1280x960 resolution. 
	Mat small_gray;
	// Downscale the image: 
	pyrDown(gray, small_gray, cvSize(gray.cols/downgradeScale, gray.rows/downgradeScale));

	// Search the faces in downscaled gray image:
	if (modelName == "LBPH" || modelName == "lbph") {
		haar_cascade.detectMultiScale(small_gray, faces, 1.2, 3, CV_HAAR_DO_CANNY_PRUNING, Size(50,50));
	} else {
		haar_cascade.detectMultiScale(small_gray, faces, 1.2, 3, CV_HAAR_DO_ROUGH_SEARCH | CV_HAAR_DO_CANNY_PRUNING |
				 CV_HAAR_SCALE_IMAGE, Size(40, 40)); // , Size(150,150): max size 
	}

	// At this point we have the position of faces in faces.
	// Now, we;ll get the faces, make a prediction and annotate
	// it in the video. Coooooool!
		

	for (int i = 0; i < faces.size(); i++) {
		// Process face by face
		// scale up then crop 
		Rect face_i;
		face_i.x = faces[i].x * downgradeScale;
		face_i.width = faces[i].width * downgradeScale;
		face_i.y = faces[i].y * downgradeScale;
		face_i.height = faces[i].height * downgradeScale;
		//Crop the face from the image, so simple with opencv
		Mat face = gray(face_i);
		// Return the image to the original size? and then feed to the prediction. 


		int prediction = -1;
		double confidence = 0.0;
		if (modelName == "LBPH" || modelName == "lbph") {
			//prediction = model->predict(face);
			model->predict(face, prediction, confidence); 
		}
		else 
		{
			// FOR FISHER and EIGEN MODEL
			// Resizing the face is necessary for Fisgerfaces and Eigrnfaces, but not 
			// for Local Binary Pattern Histograms. So this part depends on the algorithm used.
			Mat face_resized;

			///********* forget: (corrected: seems legit?)Probelmatic!? ONLY RESIZE THE FACE NOT HOLE IMAGE:Size(training_im_width, training_im_height) 
			cv::resize(face, face_resized,Size(training_im_width, training_im_height), 1.0, 1.0, INTER_CUBIC);
			// Now perform the prediction
			//prediction = model->predict(face_resized);
			model->predict(face_resized, prediction, confidence);
			face_resized.release(); 
		} 

		cout << modelName <<" -> Predicted: "<< prediction<< " with confidence: "<< confidence << endl;
		// And finally write all we;ve found to the original image. 
		// First, draw a green rectangle arud the detected face:
		
		CvPoint faceRectP1 = cvPoint(face_i.x, face_i.y);
		CvPoint faceRectP2 = cvPoint((face_i.x+face_i.width),
							         (face_i.y+face_i.height));
		Rect fRect = Rect(faceRectP1, faceRectP2);

		rectangle(*original, faceRectP1, faceRectP2, CV_RGB(0,255,0), 3);
		
		// get the face center 
		faceCenter.x = ( faceRectP1.x + faceRectP2.x ) / 2;
		faceCenter.y = ( faceRectP2.y + faceRectP2.y ) /2;

		// Create the text we will annotate the face with 
		string box_text = format("P=%d", prediction);

		//calculate the position of the annotated text:
		int pos_x = std::max(face_i.tl().x - 10, 0);
		int pos_y = std::max(face_i.tl().y - 10, 0);

		// Put the text in the image 
		putText(*original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 2.0, CV_RGB(0,255,0), 3.0);
		//cout << " Face Position of RGB Image " << i << " at : (" << faceCenter.x << ", " << faceCenter.y << ")\n";

		/* Detect eyes*/
		/*
		vector<Rect> eyes;
		eye_cascade.detectMultiScale(face, eyes, 1.1, 2,
									0|CV_HAAR_SCALE_IMAGE, Size(5,5) ); 
		for ( int j = 0; j < eyes.size(); j++ )
		{
			Point center ( faces[i].x + eyes[j].x + eyes[j].width*0.5,
				faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound( (eyes[j].width + eyes[j].height*0.25));
			circle(*original,center, radius, Scalar(30, 150, 220), 4, 8, 0);
		}
		*/
		//assign face to a skeleton 
		assignFaceToSkeleton(Point(pos_x, pos_y), prediction);
		
		face.release();
	}
}

/*
  Draws all of the available skeletons. 
*/
void drawAllSkeletons (Mat *anImage)
{
	for (int i = 0; i < NUI_SKELETON_COUNT; i++ )
		{
			drawSkeletonByID(i, anImage, false);
	}
}

/*
 Check if a file already exists with the given name.
*/
bool fileExist(string filename)
{
	GetFileAttributes(filename.c_str());
	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(filename.c_str()) && GetLastError() == ERROR_FILE_NOT_FOUND)
		return false;
	return true; 
}


int main() {

	if (!initKinect()) return 1; 
	Sleep(1000); // Wait for initialization 

	// if we are taking the images for traing purpose, enter to the picture mode. 
	// The program terminates once the operation is done. To start over change the
	// status to "pictureMode = false".
	if (pictureMode)
		{
		saveImages(pictureOwner);
		//cout << "Finished saving images." << endl;
		//system("pause");
		exit(0);
	}
	// Load images and corresponding labels:
	try {
		read_csv(fn_csv, images, labels);
	} catch(cv::Exception& e) {
		cerr <<"Error opening file \""<<fn_csv << "\". Reason: " <<e.msg << endl;
		system("pause");
		exit(1);
	}

	//Quit if there are not enough images for training.
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images.";
		CV_Error(CV_StsError, error_message);
		system("pause");
	}
	
	//get the hight from first image. We'll need this later in code to reshape 
	// the incoming images to their original size:
	training_im_width = images[0].cols;
	training_im_height = images[0].rows;
	
	// To save or load the model with name 
	//string modelStr = format("%s-model.yml", modelName);
	string modelStr = modelName + "_model.yml";
	/***********************************************************************************/ 
	if ( modelName == "Fisher" || modelName == "fisher")
		model = createFisherFaceRecognizer();
	else if (modelName == "Eigen" || modelName == "eigen")
		model = createEigenFaceRecognizer();
	else if (modelName == "LBPH" || modelName == "lbph")
		model = createLBPHFaceRecognizer();
	else {
		cout << "Please provide a valid recognizer type:" << endl;
		cout << "\"Fisher\", \"Eigen\" or \"LBPH\"" << endl;
		system("pause");
		exit(1);
	}
	

	// Now we are going to use the haar cascade you have specified in the command line 
	if (modelName == "LBPH" || modelName == "lbph") {
		haar_cascade.load(fn_lbp);
	} else {
		haar_cascade.load(fn_haar);
	}
	if( !eye_cascade.load(eye_cascade_name)) {printf(" Error loading eye cascade"); return -1;}
	if ( cropMode )
	{
		Mat frame = images[images.size() - 1];
		images.pop_back();

		imshow("Poped Image", frame);
		waitKey(10);
		Mat cropped = CropFaces(frame);
		//imshow("cropped", cropped);
		waitKey(0);

		exit(1);
	}
	// Training Phase
	if (!useExistingModel) {
		// train a new model 
		cout << "Training a new recognizer of type " << modelName << " model." << endl;
		// Train the model 
		model->train(images, labels);
		// Save the trained madel 
		model->save(modelStr);
	} else {
		// load the existing model 
		cout << "Loading the existing recognizer of type " << modelName<< " model." << endl;
		model->load(modelStr);
		cout << "Loading finished.\n";
	}

	// requirements for recording the video
	VideoWriter vid_unlabeled, vid_labeled, vid_skeleton;
	Size vidSize = Size(imgWidth, imgWidth);
	int codec = CV_FOURCC('F', 'L', 'V', '1');//CV_FOURCC('M', 'J', 'P', 'G');
	int fps = 4; 

	/**************************************/
	// Go!
	
	// If video recording is on, prepare ..
	if ( writeToVideo )
	{
		string pname = "oldLady"; // name of the person who is acting in the kitchen 
		string vidName_unlabeled =  format("%s_unlabeledVideo.avi",pname.c_str());
		string vidName_labeled = format("%s_LabeledVideo.avi", pname.c_str());
		string vidName_skeleton = format("%s_skeletonVideo.avi", pname.c_str());

		// check that the video file name not already exists. 
		if ( fileExist( vidName_labeled.c_str()) || fileExist(vidName_skeleton.c_str()) || fileExist(vidName_unlabeled.c_str()) )
		{
			cout << "Error! Avi file already exist! Change the file name and ";
			system("pause");
			return -8;
		}
		
		vid_unlabeled.open(vidName_unlabeled, codec , fps, vidSize, true);
		if ( !vid_unlabeled.isOpened())
		{
			cout << "Error opening "<<vidName_unlabeled << " ";
			system("pause"); return -1;
		}
	
		vid_labeled.open(vidName_labeled, codec, fps, vidSize, true);
		if ( !vid_labeled.isOpened())
		{
			cout << "Error opening "<<vidName_labeled << " ";
			system("pause"); return -1;
		}
		vid_skeleton.open(vidName_skeleton, codec, fps, vidSize, true);
		if ( !vid_skeleton.isOpened())
		{
			cout << "Error opening "<<vidName_skeleton << " ";
			system("pause"); return -1;
		}
	
	}

	

	for (;;) {	
		int tic = (int) (clock()); // start time 
		if ( useBigPic) 
		{
			getKinectSkeletalData();
			getKinectColorData(kinectColorImageBig);
			Mat originalBig(kinectColorImageBig);
			Mat rs;
			resize(originalBig, rs, Size(imgWidth, imgHeight));
			

			Mat imSkeleton = rs.clone();
			Mat rgbImage = originalBig.clone();

			detecFaces(&rgbImage);
			drawAllSkeletons(&imSkeleton); 
			Mat rgb_rsz;
			resize(rgbImage, rgb_rsz, Size(imgWidth, imgHeight));
			for ( int i = 0; i < NUI_SKELETON_COUNT; i++ ) 
			{
				if ( skeletonAvailable(i) && skeletonHasFaceLabel(i) )
					drawSkeletonByID( i , &rgb_rsz, true); 
			}
			/*Mat rgb_rsz;
			resize(rgbImage, rgb_rsz, Size(640,480));*/

		
			/* Write to video files */
			

			// Get the elapsed time 
			int t_elapsed = clock() / CLOCKS_PER_SEC; 
			string t_string = format("Elapsed time: %d", t_elapsed);
			putText(rgb_rsz, t_string, Point(300, 100), CV_FONT_HERSHEY_PLAIN, 2.0, Scalar(255, 0, 0), 2); 
			
			
			if ( writeToVideo ) 
			{
				Mat aFrame;
				// convert the color, otherwise videowriter does not work. 
				cvtColor(rs, aFrame, CV_RGB2BGR);
				// conver back again to retain the original colors 
				cvtColor(aFrame, aFrame, CV_BGR2RGB);
				resize(aFrame, aFrame, vidSize);
				//imshow("aFrame", aFrame);
				//waitKey(10); 
	
				vid_unlabeled << aFrame;
				vid_unlabeled << aFrame;
				vid_unlabeled << aFrame;
				vid_unlabeled << aFrame;

				Mat sFrame;
				cvtColor(imSkeleton, sFrame, CV_RGB2BGR);
				cvtColor(sFrame, sFrame, CV_BGR2RGB); 
				// resize the image to be square (height = width), otherwise videowriter doesnt work. 
				resize(sFrame, sFrame, vidSize);
				vid_skeleton << sFrame;
				vid_skeleton << sFrame;
				vid_skeleton << sFrame;
				vid_skeleton << sFrame;
				//waitKey(30);

				Mat rgb_vid;
				resize(rgb_rsz, rgb_vid, vidSize);
				cvtColor(rgb_vid, rgb_vid, CV_RGB2BGR);
				cvtColor(rgb_vid, rgb_vid, CV_BGR2RGB);
				vid_labeled << rgb_vid;
				vid_labeled << rgb_vid;
				vid_labeled << rgb_vid;
				vid_labeled << rgb_vid;
				//waitKey(30);

			}
			//imshow("Face recognizer(Esc to exit)", rgb_rsz);
			// put images together
			//
			//Mat twoImages = Mat::zeros(Size(imgWidth*2+3, imgHeight), rgb_rsz.type()); 
			//Rect roi = Rect(0,0, imgWidth, imgHeight);
			//Mat roiImage = twoImages(roi);
			//rs.copyTo(roiImage); 
			//// move roi 
			//roi.x = roi.x + imgWidth+2; 
			//roiImage = twoImages(roi);
			//rgb_rsz.copyTo(roiImage); 
			//namedWindow("Skeleton Joints(Esc to exit)", CV_WINDOW_AUTOSIZE);
			//imshow("Skeleton Joints(Esc to exit)", twoImages);
			//
			
			namedWindow("Skeleton Joints(Esc to exit)", CV_WINDOW_AUTOSIZE);
			resize(imSkeleton, imSkeleton, Size(320, 240));
			imshow("Skeleton Joints(Esc to exit)", imSkeleton);
			namedWindow("Face recognizer(Esc to exit)", CV_WINDOW_AUTOSIZE);
			imshow("Face recognizer(Esc to exit)",rgb_rsz); 
			

			//cout << t_elapsed << endl;
			
			// convert the RGB image to BGR, otherwise videowriter won't work!!
			

			char key =  (char) waitKey(30);
			// Exit the loop on escape:
			if (key == 27)
			{
				vid_unlabeled.release();
				vid_labeled.release();
				vid_skeleton.release(); 
				break;
			}
			
				
			//clean-up 
			originalBig.release();
			imSkeleton.release();
			//rgb_rsz.release();
			rs.release();

			int toc = (int) (clock()); // end time
			cout << " One cycle done in "<< toc - tic << " miliseconds" << endl; 

			
		}
		else // normal size images 
		{
			getKinectSkeletalData();
			getKinectColorData(kinectColorImage);
			Mat original(kinectColorImage);

			Mat imSkeleton = original.clone();
			Mat rgbImage = original.clone();

			detecFaces(&rgbImage);
			drawAllSkeletons(&imSkeleton); 

			for ( int i = 0; i < NUI_SKELETON_COUNT; i++ ) 
			{
				if ( skeletonAvailable(i) && skeletonHasFaceLabel(i) )
					drawSkeletonByID( i , &rgbImage, true); 
			}
		

			// Show the result 
			namedWindow("Skeleton Joints(Esc to exit)", CV_WINDOW_AUTOSIZE);
			imshow("Skeleton Joints(Esc to exit)", imSkeleton);
			namedWindow("Face recognizer(Esc to exit)", CV_WINDOW_AUTOSIZE);
			imshow("Face recognizer(Esc to exit)", rgbImage);

			char key =  (char) waitKey(10);
			// Exit the loop on escape:
			if (key == 27)
				break;

			//clean-up 
			original.release();
			imSkeleton.release();
			rgbImage.release();
		}
		//vid_unlabeled.release();
		//vid_labeled.release();
	}
	
	return 0;
}
