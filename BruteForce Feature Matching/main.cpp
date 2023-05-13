#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Header.h"


int main()
{
    // Load the images
    std::string img1 = "/Users/onuralpguvercin/Desktop/Images/all_souls_000002.jpg";
    std::string img2 = "/Users/onuralpguvercin/Desktop/Images/all_souls_000006.jpg";
    
    ORB_FeatureDetector ORB(img1, img2);
    ORB.compareImages();
    
//    SIFT_FeatureDetector SIFT(img1, img2);
//    SIFT.CompareImages();
    return 0;
}
