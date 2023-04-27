//
//  watershed.hpp
//  lab5_desktop
//
//  Created by onuralp güvercin on 27.04.2023.
//

#ifndef watershed_hpp
#define watershed_hpp
#include "opencv2/opencv.hpp"
#include <stdio.h>

cv::Mat create_binary_image(const cv::Mat& _inputImage);
std::vector<std::vector<cv::Point>> find_contours(const cv::Mat& _distance_image);
cv::Mat find_markers(const cv::Mat& _dist, std::vector<std::vector<cv::Point>> contours, int ncomp);
cv::Mat watershed(const  cv::Mat& _inputImage);

#endif /* watershed_hpp */
