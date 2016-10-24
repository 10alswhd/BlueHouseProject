#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <assert.h>

#define mp make_pair
#define pb push_back

#define A 0.1
#define P 1
#define B 1
#define FRAMENUM 80
#define GAIN 10.0

using namespace std;
using namespace cv;

inline double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-GAIN * (x - 0.5)));
}

inline double lengthSquare (double x, double y) {
  return pow(x,2)+pow(y,2);
}

inline double length (double x, double y) {
  return pow(lengthSquare(x,y),0.5);
}

CvPoint getMappingPoint (CvPoint p, CvPoint q, double u, double v) {
  double vx =  q.y - p.y;
  double vy = -q.x + p.x;
  double hx =  q.x - p.x;
  double hy =  q.y - p.y;
  double vu = length(vx, vy);
  
  double sx = p.x + u*hx + (vx/vu)*v;
  double sy = p.y + u*hy + (vy/vu)*v;
  //printf("u=%f hx=%f vx/vu=%f v=%f \n", u, hx, vx/vu, rv);

  return cvPoint(sx, sy);
}

int main(int argc, char** argv) {
  if (argc != 5) {
    cerr << "specify 4 arguments" << endl;
    exit(-1);
  }

  const char* srcImageFile = argv[1];
  const char* srcFeatureFile = argv[2];
  const char* destImageFile = argv[3];
  const char* destFeatureFile = argv[4];

  IplImage* srcImage = cvLoadImage(srcImageFile, CV_LOAD_IMAGE_ANYCOLOR|CV_LOAD_IMAGE_ANYDEPTH);
  IplImage* destImage = cvLoadImage(destImageFile, CV_LOAD_IMAGE_ANYCOLOR|CV_LOAD_IMAGE_ANYDEPTH);
  IplImage* morphImage = cvCreateImage(cvGetSize(destImage), IPL_DEPTH_8U, 3);

  if (!srcImage || !destImage) {
    cerr << "cannot find image file" << endl;
    exit(-1);
  }

  // load feature line mapping from text files
  int srcFeatureNum;
  int destFeatureNum;
  vector< pair <CvPoint, CvPoint> > srcFeatures;
  vector< pair <CvPoint, CvPoint> > destFeatures;

  {
    ifstream srcFeatureStream(srcFeatureFile);
    ifstream destFeatureStream(destFeatureFile);
    
    srcFeatureStream >> srcFeatureNum;
    for (int i=0; i<srcFeatureNum; i++) {
      int x1,y1,x2,y2;
      srcFeatureStream >> x1 >> y1 >> x2 >> y2;
      CvPoint p1=cvPoint(x1,y1);
      CvPoint p2=cvPoint(x2,y2);
      srcFeatures.pb(mp(p1,p2));
    }

    destFeatureStream >> destFeatureNum;
    for (int i=0; i<destFeatureNum; i++) {
      int x1,y1,x2,y2;
      destFeatureStream >> x1 >> y1 >> x2 >> y2;
      CvPoint p1=cvPoint(x1,y1);
      CvPoint p2=cvPoint(x2,y2);
      destFeatures.pb(mp(p1,p2));
    }
      
    srcFeatureStream.close();
    destFeatureStream.close();
  }
  
  int w = destImage->width;
  int h = destImage->height;

  vector< pair <CvPoint, CvPoint> > targetFeatures(destFeatureNum);
  int fileIndex = 0;
  
  cvNamedWindow("mywindow");
  // increase time parameter
  for (double t=0; t<=1.0F; t+=1.0F/FRAMENUM) {
    // calculate intermediate feature line
    for (int i=0; i<destFeatureNum; i++) {
      pair <CvPoint, CvPoint> sp = srcFeatures[i];
      pair <CvPoint, CvPoint> dp = destFeatures[i];
      CvPoint t1 = cvPoint( (1.0F-t)*sp.first.x + t*dp.first.x, (1.0F-t)*sp.first.y + t*dp.first.y );
      CvPoint t2 = cvPoint( (1.0F-t)*sp.second.x + t*dp.second.x, (1.0F-t)*sp.second.y + t*dp.second.y );
      targetFeatures[i] = mp(t1, t2);
    }
    
    // calculate warped images from src image and dest image, and cross-dissolve two warped images into target image
    for (int y=0; y<h; y++) {
      for (int x=0; x<w; x++) {
        double sumsdx=0, sumsdy=0, sumddx=0, sumddy=0, sumweight=0;
        for (int i=0; i<destFeatureNum; i++) {
          // calculate weight for point(x,y) with line(i)
          double u,v,rawv,weight;
          {
            pair<CvPoint,CvPoint> tp = targetFeatures[i];
            // vertical vector is ps.second.y-ps.first.y, -ps.second.x+ps.first.x
            double vx =  tp.second.y - tp.first.y;
            double vy = -tp.second.x + tp.first.x;
            double hx =  tp.second.x - tp.first.x;
            double hy =  tp.second.y - tp.first.y;
            double tx =  x - tp.first.x;
            double ty =  y - tp.first.y;
            
            // calc u
            u = (tx*hx + ty*hy) / lengthSquare(hx,hy);
            double vu = length(vx, vy);
            rawv = (vx*tx + vy*ty) / vu;
            if (u <= 0) {
              // v = PX
              v = length(tx, ty);
            } else if (u >= 1) {
              // v = QX
              v = length(x - tp.second.x, y - tp.second.y);
            } else {
              // vertical vector length
              v = abs(rawv);
            }
            double lineLength = length(hx, hy);
            weight = pow ((pow(lineLength, P)/(A+v)), B);
            assert(weight >= 0);
          }
          
          {
            pair<CvPoint, CvPoint> sf = srcFeatures[i];
            CvPoint sp = getMappingPoint(sf.first, sf.second, u, rawv);
            double sdx = x - sp.x;
            double sdy = y - sp.y;
            //printf("sdx=%f sdy=%f weight=%f\n", sdx, sdy, weight);
            sumsdx += sdx*weight;
            sumsdy += sdy*weight;
          }
          
          {
            pair<CvPoint, CvPoint> df = destFeatures[i];
            CvPoint dp = getMappingPoint(df.first, df.second, u, rawv);
            double ddx = x - dp.x;
            double ddy = y - dp.y;
            sumddx += ddx*weight;
            sumddy += ddy*weight;
          }
          
          sumweight += weight;
        }
        double avesdx = sumsdx/sumweight;
        double avesdy = sumsdy/sumweight;
        double aveddx = sumddx/sumweight;
        double aveddy = sumddy/sumweight;
        
        int sx = (int)(x - avesdx);
        int sy = (int)(y - avesdy);
        int dx = (int)(x - aveddx);
        int dy = (int)(y - aveddy);
        if (sx < 0 || sx > srcImage->width || sy < 0 || sy > srcImage->height) {
          continue;
        }
        if (dx < 0 || dx > destImage->width || dy < 0 || dy > destImage->height) {
          continue;
        }
        int destIndex = destImage->widthStep * dy + dx * destImage->nChannels;
        int srcIndex = srcImage->widthStep * sy + sx * srcImage->nChannels;
        int targetIndex = morphImage->widthStep * y + x * morphImage->nChannels;
        for (int i=0; i<morphImage->nChannels; i++) {
          uchar dp = (destImage->imageData[destIndex+i]);
          uchar sp = (srcImage->imageData[srcIndex+i]);
          int diff =  (int)dp - (int)sp;
          int newvalue = diff * sigmoid(t) + sp;
          //int newvalue = diff * t + sp;
          //printf("diff=%d old=%d new=%d\n", diff, sp, newvalue);
          assert(newvalue <= 255 && newvalue >= 0);
          morphImage->imageData[targetIndex+i] = (uchar)newvalue;
        }
        //printf("source=(%d,%d) dest=(%d,%d)\n", sx, sy, x, y);
      }
    }
    char outfile[256];
    sprintf(outfile, "/Users/takahiro/Desktop/morph/morph%03d.jpg", fileIndex++);
    //int res = cvSaveImage(outfile, morphImage);
    cvShowImage("mywindow", morphImage);
    cvWaitKey(2);
    //printf("save to %s\n", outfile);
  }
  cvWaitKey(0);
  
  // 後始末
  cvReleaseImage(&srcImage);
  cvReleaseImage(&destImage);
  cvReleaseImage(&morphImage);

  return 0;
}
