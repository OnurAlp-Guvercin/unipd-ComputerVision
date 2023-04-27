//
//  kmeans.hpp
//  lab5_desktop
//
//  Created by onuralp güvercin on 27.04.2023.
//

#ifndef kmeans_hpp
#define kmeans_hpp
#include "opencv2/opencv.hpp"
#include <stdio.h>

cv::Mat kmeans_clustered(const cv::Mat& src, int number_clusters);

#endif /* kmeans_hpp */
