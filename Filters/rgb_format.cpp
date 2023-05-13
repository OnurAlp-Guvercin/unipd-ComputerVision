//
//  gray_scale.cpp
//  lab_2
//
//  Created by onuralp güvercin on 20.03.2023.
//

#include <opencv2/highgui.hpp>
#include <iostream>

void gray_scale(cv::Mat img){
    
    if(img.channels()==3){
        for(int i=0; i<img.rows; i++){
            for(int j=0; j<img.cols; j++){
                img.at<cv::Vec3b>(i,j)[0] = 0;
                img.at<cv::Vec3b>(i,j)[2] = 2;
            }
        }
    }
}
