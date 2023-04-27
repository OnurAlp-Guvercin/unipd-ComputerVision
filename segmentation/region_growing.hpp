//
//  lab5.hpp
//  lab5_desktop
//
//  Created by onuralp güvercin on 27.04.2023.
//

#ifndef lab5_hpp
#define lab5_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"

void show_image(const char* name, const cv::Mat& src);

//task1
std::vector<cv::Point> find_seed_points(cv::Mat& src, bool show_seeds = false, int thresh_binary = 10);
void grow(cv::Mat& src, cv::Mat& dest, cv::Mat& mask, cv::Point seed, int threshold);
cv::Mat region_grow(cv::Mat& src, std::vector<cv::Point> seed_points, int threshold);

#endif /* lab5_hpp */
