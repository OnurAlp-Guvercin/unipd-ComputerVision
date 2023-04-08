//
//  main.cpp
//  lab_2
//
//  Created by onuralp güvercin on 20.03.2023.
//


#include <iostream>
#include "Header.h"


int main(){
    

    cv::Mat img = cv::imread("/Users/onuralpguvercin/Desktop/image.jpg");
    cv::Mat gray_image = cv::imread("/Users/onuralpguvercin/Desktop/gray_image.jpg");
    
    cv::cvtColor(gray_image, gray_image, cv::COLOR_BGR2GRAY);
    std::cout << gray_image.channels() << std::endl;
    
    //maxFilter(gray_image, 5);
    //maxFilter_manual(gray_image, 19);
    //minFilter(gray_img_2, 5);
    //MedianFilter(gray_image, gray_image, 5);
    //GaussianFilter(gray_image, cv::Size(9,9), 2.0);
    gray_histogram(img);

    

    
    //cv::namedWindow("image");
    cv::namedWindow("gray_img");
    //cv::imshow("image", img);
    cv::imshow("gray_img", gray_image);
    
    cv::waitKey(0);
    
    
    
    return 0;
}

