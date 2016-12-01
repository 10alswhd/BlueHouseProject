#include <iostream>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>

using namespace std;
using namespace cv;

const int BLOCK_SIZE = 32;
const double PI = 4 * atan2(1,1);
Mat L;
Mat R;
Mat P;


// from OpenCV
Scalar getMSSIM( const Mat& i1, const Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d     = CV_32F;

    Mat I1, I2;
    i1.convertTo(I1, d);           // cannot calculate on one byte large values
    i2.convertTo(I2, d);

    Mat I2_2   = I2.mul(I2);        // I2^2
    Mat I1_2   = I1.mul(I1);        // I1^2
    Mat I1_I2  = I1.mul(I2);        // I1 * I2

    /*************************** END INITS **********************************/

    Mat mu1, mu2;   // PRELIMINARY COMPUTING
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);

    Mat mu1_2   =   mu1.mul(mu1);
    Mat mu2_2   =   mu2.mul(mu2);
    Mat mu1_mu2 =   mu1.mul(mu2);

    Mat sigma1_2, sigma2_2, sigma12;

    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;

    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;

    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;

    ///////////////////////////////// FORMULA ////////////////////////////////
    Mat t1, t2, t3;

    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

    Mat ssim_map;
    divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;

    Scalar mssim = mean( ssim_map ); // mssim = average of ssim map
    return mssim;
}


vector<vector<double>> calculateSSIM(Mat inputImage1, Mat inputImage2) {
    vector<vector<double>> working;

    if(inputImage1.cols != inputImage2.cols || inputImage1.rows != inputImage2.rows){
        cout << "calculateSSIM can only take 2 same sized images" << endl;
    }

    for (int i = 0; i < inputImage1.cols / BLOCK_SIZE + 1; i++) {
        vector<double> curCol;
        for (int j = 0; j < inputImage1.rows / BLOCK_SIZE + 1; j++) {
            if (i * BLOCK_SIZE + BLOCK_SIZE < inputImage1.cols && j * BLOCK_SIZE + BLOCK_SIZE < inputImage1.rows) {
                Rect region_of_interest = Rect(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
                Mat curr1 = inputImage1(region_of_interest);
                Mat curr2 = inputImage2(region_of_interest);
                //imwrite("ROI split" + to_string(j) + to_string(i) + ".jpg", curr);
                Scalar currSSIM = getMSSIM(curr1, curr2);
                curCol.push_back((double) currSSIM.val[0] );
                //cout << currSSIM.val[0] << " ";
            }
        }
        //cout << endl;
        working.push_back(curCol);
    }
    return working;
}

Mat splitLeftImg(Mat inImg, int percentage){
    int startx = inImg.cols * (100 - percentage) / 100;
    int starty = 0;
    Rect region_of_interest = Rect(startx, starty,  inImg.cols - startx, inImg.rows);
    return inImg(region_of_interest);
}

Mat splitRightImg(Mat inImg, int percentage){
    int startx = 0;
    int starty = 0;
    Rect region_of_interest = Rect(startx, starty, inImg.cols * percentage / 100, inImg.rows);
    return inImg(region_of_interest);
}

Mat splitStitchedImg(Mat inImg, int percentage, int img1_cols, int img2_cols){
    int startx = img1_cols * (100 - percentage) / 100;
    int starty = 0;
    Rect region_of_interest = Rect(startx, starty, img2_cols * percentage / 100, inImg.rows);
    return inImg(region_of_interest);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage <img1>";
        return -1;
    }

    L = imread("1.jpg");
    R = imread("2.jpg");
    P = imread("out58.jpg");
    splitpercentage  = 58;

    Mat L_ol = splitLeftImg(L,splitpercentage);
    Mat R_ol = splitRightImg(R,splitpercentage);
    Mat P_ol = splitStitchedImg(P, splitpercentage, L.cols, R.cols);

    Mat L_hp_ol;
    Mat R_hp_ol;
    Mat P_hp_ol;
    Mat L_lp_ol;
    Mat R_lp_ol;
    Mat P_lp_ol;
    bilateralFilter(L_ol, L_lp_ol,18,150,150);
    bilateralFilter(R_ol, R_lp_ol, 18, 150, 150);
    bilateralFilter(P_ol, P_lp_ol, 18, 150, 150);

    L_hp_ol = L_ol - L_lp_ol;
    R_hp_ol = R_ol - R_lp_ol;
    P_hp_ol = P_ol - P_lp_ol;

    vector<vector<double>> L_SSIM;
    vector<vector<double>> R_SSIM;
    vector<vector<double>> L_SSIM_HFI;
    vector<vector<double>> R_SSIM_HFI;
    vector<vector<double>> HFI_SSIM;

    L_SSIM = calculateSSIM(L_ol, P_ol);
    R_SSIM = calculateSSIM(R_ol, P_ol);

    L_SSIM_HFI = calculateSSIM(L_hp_ol, P_hp_ol);
    R_SSIM_HFI = calculateSSIM(R_hp_ol, P_hp_ol);

    // Calculation of Geometric Quality
    double tot = 0;
    double num = 0;
    double tot_hfi = 0;

    for(int i = 0; i < L_SSIM.size(); i ++){
        vector<double> L_SSIM_ = L_SSIM[i];
        vector<double> R_SSIM_ = R_SSIM[i];
        vector<double> L_SSIM_HFI_ = L_SSIM_HFI[i];
        vector<double> R_SSIM_HFI_ = R_SSIM_HFI[i];
        vector<double> currHFI_SSIM;
        for(int j = 0; j < L_SSIM_.size(); j ++){
          if(L_SSIM_[j] > R_SSIM_[j]) {
              tot += L_SSIM_[j];
              tot_hfi += L_SSIM_HFI_[j];
              currHFI_SSIM.push_back(L_SSIM_HFI_[j]);
          }
          else {
              tot += R_SSIM_[j];
              tot_hfi += R_SSIM_HFI_[j];
              currHFI_SSIM.push_back(R_SSIM_HFI_[j]);
          }
            num ++;
        }
        HFI_SSIM.push_back(currHFI_SSIM);
    }

    cout << "Geometric Quality with HFI: "<< (double) tot_hfi / (double) num << endl;

    return 0;
}
