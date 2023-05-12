//
//  crack_segmentation.hpp
//  segmentation
//
//  Created by onuralp güvercin on 16.04.2023.
//

#ifndef crack_segmentation_hpp
#define crack_segmentation_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class ImageSegmentation {
public:
    ImageSegmentation(string filename);

    void thresholdImage();

    void applyGaussianBlur(int n);

    void applyMorphologicalOperations(int n1, int n2);

    void applyMeanShiftFiltering();
    
    //---------------------------
    
    void meanFilter(int n);
    
    void MedianBlur(int n);
    
    void grayScale();
    
    void applyKmeans();
    
    void maxFilter(int kernelSize);
    
    void minFilter(int kernelSize);

private:
    Mat src;
    Mat eroded;
    Mat result;
};


#endif /* crack_segmentation_hpp */
