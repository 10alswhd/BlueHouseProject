/****************************************************************************************************
This code is part of the code supplied with the OpenCV Blueprints book.
It was written by Steven Puttemans, who can be contacted via steven.puttemans[at]kuleuven.be
License can be found at https://github.com/OpenCVBlueprints/OpenCVBlueprints/blob/master/license.txt
*****************************************************************************************************
This is software for performing a simple detection using a trained cascade classifier model.
USAGE:
./detect_simple -model <model.xml> -testfiles <list.txt> -detections <output.txt>
***********************************************************************************************/

#include <iostream>
#include <fstream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;


struct annotation {
    string filename;
    int numOfRects;
    vector<Rect> regions;
};

bool isCentersNear(Rect r1, Rect r2){
	Point firstCenter = Point(r1.x + r1.width/2, r1.y + r1.height/2);
	Point secondCenter = Point(r2.x + r2.width/2, r2.y + r2.height/2);
	return ( norm(firstCenter - secondCenter) < (0.8*min(r1.width, r2.width)) );
}

void writeImageSeq(Mat src, int counter){
	string folderName = "falsepositives";
	string name = "falsepositive_";
	string type = ".png";
	
 	string folderCreateCommand = "mkdir " + folderName;
 	system(folderCreateCommand.c_str());

	stringstream ss;
	ss<<folderName<<"/"<<name<<(counter)<<type;
 	string fullPath = ss.str();
 	ss.str("");

    // Resize and save a model-sized FP image
    Mat model_roi;
	Size model_size(24,24);
    resize(src, model_roi, model_size); 
 	imwrite(fullPath, model_roi);
}


int main( int argc, const char** argv )
{

    // If no parameters are give, then a usage template should be provided
    if(argc == 1){
	cout << "This is software for performing a simple detection using a trained cascade classifier model." << endl;
        cout << "USAGE ./detect_simple -model <model.xml> -annotations <annotations.txt> -detections <output.txt> -box <0 or 1>" << endl;
        return 0;
    }

    // Read in the input arguments
    string model = "";
    string annotation_file = "";
    string detections = "";
    int showBox = 0;
    for(int i = 1; i < argc; ++i )
    {
        if( !strcmp( argv[i], "-model" ) )
        {
            model = argv[++i];
        }else if( !strcmp( argv[i], "-annotations" ) ){
            annotation_file = argv[++i];
        }else if( !strcmp( argv[i], "-detections" ) ){
            detections = argv[++i];
        }else if( !strcmp( argv[i], "-box" ) ){
            showBox = atoi(argv[++i]);
        }
    }

    // Start by initiating the detector
    CascadeClassifier detector(model);
    if(detector.empty()){
        cerr << "The model could not be loaded." << endl;
    }

    
    // Read groundtruth annotations
    ifstream input ( annotation_file.c_str() );
	string current_line;
	vector<annotation> groundtruth;

	while ( getline(input, current_line) ){
	    // A complete line is read, now check how many detections happened
	    // First split the string into elements
        vector<string> line_elements;
        stringstream temp (current_line);
        string item;
        while ( getline(temp, item, ' ') ) {
            line_elements.push_back(item);
        }

        annotation current;
        current.filename = line_elements[0];
        current.numOfRects = atoi( line_elements[1].c_str() );                // 1 num of annotations; 
        for (int i = 0; i < current.numOfRects; i++){
        	Rect box = Rect(atoi(line_elements[2+(i*4)].c_str()), atoi(line_elements[3+(i*4)].c_str()), atoi(line_elements[4+(i*4)].c_str()), atoi(line_elements[5+(i*4)].c_str()));
            (current.regions).push_back(box);
        }
        groundtruth.push_back(current);
    }
    input.close();


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Now we compare the ground truth versus the detections based on
    //      - TP = detection that is in ground truth
    //      - FP = detection that is not in ground truth
    //      - FN = in ground truth but no detection
    // We want to define two values for each threshold, being recall and precision
    //      - recall        TP/(TP+FN)
    //      - precision     TP/(TP+FP)
    // Threshold is defined on the certainty score of the detection output
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    int TP = 0, FP = 0, FN = 0;

    // Loop over images, perform detection and store result
    ofstream result(detections.c_str());  

    for(int i = 0; i < (int)groundtruth.size(); i++){
        Mat current_image, grayscale, equalize;

        // Read in image and perform preprocessing
        current_image = imread(groundtruth[i].filename);
        cvtColor(current_image, grayscale, CV_BGR2GRAY);
        equalizeHist(grayscale,equalize);

        // Perform detection
        // Retrieve detection certainty scores
        // Perform non maxima suppression
        vector<Rect> outputs;
        detector.detectMultiScale(equalize, outputs, 1.05, 1);


        // Loop over detections and store them correctly
        stringstream outputline;
        outputline << groundtruth[i].filename << " " << outputs.size() << " ";
        cout << groundtruth[i].filename << " " << outputs.size() << " ";
        vector<Rect> current_regions = groundtruth[i].regions;
        
        for(int rectIdx = 0; rectIdx < (int)outputs.size(); rectIdx++){
        
        	Rect region_det = outputs[rectIdx];
            outputline << region_det.x << " " << region_det.y << " " << region_det.width << " " << region_det.height << " ";
            cout << region_det.x << " " << region_det.y << " " << region_det.width << " " << region_det.height << " " << endl;
           
            
            // Compare the detection to each groundtruth 
         	bool false_positive = true; // assume 
         	  	
         	  	
         	// For each detection, see if the 		re is a match with all of the annotations
            for (int annoIdx = 0; annoIdx < (int)current_regions.size(); annoIdx++){
                        Rect region_anno = current_regions[annoIdx];

                        // Definining of a matching pair of regions is a match is done based on overlapping area
                        int x_overlap = std::max(0, std::min(region_det.x + region_det.width, region_anno.x + region_anno.width) - std::max(region_det.x, region_anno.x));
                        int y_overlap = std::max(0, std::min(region_det.y + region_det.height, region_anno.y + region_anno.height) - std::max(region_det.y, region_anno.y));

                        int surface_det = region_det.width * region_det.height;
                        int surface_anno = region_anno.width * region_anno.height;
                        int surface_overlap = x_overlap * y_overlap;

                        // Rule to define what to increase - dependent on 50% overlap for a good match AND a max 50% larger detection
                        // if( (surface_overlap > 0.5 * surface_det) && (surface_overlap > 0.5 * surface_anno) && (surface_det < (1.5 * surface_anno)) && (surface_det > (0.5 * surface_anno))){
                        if( ((surface_overlap > 0.5 * surface_det) && (surface_overlap > 0.5 * surface_anno)) || (isCentersNear(region_det, region_anno) && (surface_overlap > (0.9 * min(surface_det, surface_anno))))  ){
                             TP++;
                             false_positive = false;                             
                        }
             }
             // Check if a TP was given, else a FP needs to be added
             if (false_positive){
             
                   FP++;
                   
                   // Save FP roi image for negative mining
                   Mat fp_roi(current_image, region_det);                    
                   writeImageSeq(fp_roi, FP);
             } 
         	
         	 // Show detections 
         	 if (showBox != 0)
            	rectangle(current_image, region_det, Scalar(0, 255, 10), 5);
        	}
        
        
        // For each groundtruth, see if there's a matching detection (for false negative)
        for (int annoIdx = 0; annoIdx < (int)current_regions.size(); annoIdx++){
                Rect region_anno = current_regions[annoIdx];
                bool no_matches = true;
                
                      
                for(int rectIdx = 0; rectIdx < (int)outputs.size(); rectIdx++){

                        Rect region_det = outputs[rectIdx];

                        // Definining of a matching pair of regions is a match is done based on overlapping area
                        int x_overlap = std::max(0, std::min(region_det.x + region_det.width, region_anno.x + region_anno.width) - std::max(region_det.x, region_anno.x));
                        int y_overlap = std::max(0, std::min(region_det.y + region_det.height, region_anno.y + region_anno.height) - std::max(region_det.y, region_anno.y));

                        int surface_det = region_det.width * region_det.height;
                        int surface_anno = region_anno.width * region_anno.height;
                        int surface_overlap = x_overlap * y_overlap;

                        // Rule to define what to increase - dependend on 50% overlap for a good match AND a max 50% larger detection
                        if( ((surface_overlap > 0.5 * surface_det) && (surface_overlap > 0.5 * surface_anno)) || (isCentersNear(region_det, region_anno) && (surface_overlap > (0.9 * min(surface_det, surface_anno)))) ){
                          // TP++;  // error: this doubles the TP count
                             no_matches = false;
                        }

                }
                // Add a FN increment if there are no detections matching the ground truth annotation
                if (no_matches) {
                    FN++;
                }

           		// Show groundtruth 
           		if (showBox != 0)
            		rectangle(current_image, region_anno, Scalar(0, 10, 255), 5);
            }
              

        outputline << endl;
        result << outputline.str();
        cerr << "\nTest image " << i+1 << ":";
        
        // Show current tally
        cout << "\nThe number of true positives (TP) are: TP = " << TP << "." << endl;
        cout << "The number of false positives (FP) are: FP = " << FP << "." << endl;
        cout << "The number of false negatives (FN) are: FN = " << FN << "." << endl;
        
        // Show image for debugging
        if (showBox != 0){
        	imshow("Current Image", current_image);
        	waitKey(0);
        }
    }
    
    
     // Now calculate the precision recall based on the TP FP FN
        double precision = (double)TP / (double)(TP + FP);
        double recall = (double)TP / (double)(TP + FN);
        
        double f1_score = 2.0 * (precision * recall) / (precision + recall); 
        
     cout << "Precision = " << precision<< "." << endl;
     cout << "Recall = " << recall << "." << endl;
     cout << "F1 Score = " << f1_score << "." << endl;

    return 0;
}
