//
//  lane line detection.hpp
//  edge_line_detection
//
//  Created by onuralp güvercin on 9.04.2023.
//

#ifndef lane_line_detection_hpp
#define lane_line_detection_hpp

#include <stdio.h>

cv::Mat line_detection(cv::Mat src);
cv::Mat line_detection2 (cv::Mat src);
cv::Mat HoughTransformationP(Mat src_gray, Mat img);
cv::Mat HoughTransformation(Mat src_gray, Mat img);

Mat HoughTransformation2(Mat src_gray, Mat img);

#endif /* lane_line_detection_hpp */

