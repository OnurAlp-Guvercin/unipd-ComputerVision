//
//  main.cpp
//  segmentation
//
//  Created by onuralp güvercin on 16.04.2023.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"


#include <opencv2/opencv.hpp>
#include <iostream>
#include "crack_segmentation.hpp"

using namespace cv;
using namespace std;

int main() {
//    string filename = "/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_5_Segmentation-20230415/Asphalt-3.png";
//    ImageSegmentation segmentation(filename);
//    segmentation.thresholdImage();
//    segmentation.applyGaussianBlur(3);
//    segmentation.applyMorphologicalOperations(1,2);
//    segmentation.applyMeanShiftFiltering();
    
    string filename = "/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_4_Edge_and_line_detection-2023040/street_scene.png";
    ImageSegmentation segmentation_2(filename);
    segmentation_2.grayScale();
    segmentation_2.minFilter(7);
    segmentation_2.applyMorphologicalOperations(2,3);
    segmentation_2.applyKmeans();
    
    
    waitKey(0);
    return 0;
}


