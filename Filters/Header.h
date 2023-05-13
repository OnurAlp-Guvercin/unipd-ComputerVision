//
//  Header.h
//  lab_2
//
//  Created by onuralp güvercin on 20.03.2023.
//

#ifndef Header_h
#define Header_h

void gray_scale(cv::Mat img);
void minFilter(cv::Mat& img, int kernel_size);
void maxFilter(cv::Mat& img, int kernel_size);
void GaussianFilter(cv::Mat img, cv::Size Size = cv::Size(5,5), float Sigma=1.0);
void MedianFilter(cv::Mat img, cv::Mat filtered_img, int Size = 5);
void gray_histogram(cv::Mat& img);
void maxFilter_manual(cv::Mat& img, int kernelSize);
#endif /* Header_h */
