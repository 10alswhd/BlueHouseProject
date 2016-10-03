void simpleHist1D(const Mat& image, OutputArray& hist) { 
     static const int channels[] = {0}; 
     static const Mat mask; 
     static const int histSize[] = {256}; 
     static const float range[] = {0.0, 255.0}; 
     static const float* ranges[] = {range}; 
     calcHist(&image, 1, channels, mask, hist, 1, histSize, ranges); 
 } 
