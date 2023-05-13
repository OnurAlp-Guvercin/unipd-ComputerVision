//
//  callback_task1.cpp
//  Callback_and_color_segmentation
//
//  Created by onuralp güvercin on 30.03.2023.
//

#include "Header_lab3.h"
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        Mat image = *(Mat*)userdata;
        Mat image_out = image.clone();

        Vec3b pixel = image_out.at<Vec3b>(y, x);
        cout << (int)pixel[0] << ", " << (int)pixel[1] << ", " << (int)pixel[2] << ", " << endl;
    }
}

void onMouse_square(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        Mat image = *(Mat*)userdata;
        Mat image_out = image.clone();
        
        int BGR[] = {0,0,0};
        for(int i = y-4; i <= y + 4; i++){
            for(int j = x-4; j <= x + 4; j++){
                Vec3b pixel = image_out.at<Vec3b>(i, j);
                BGR[0]+=(int)pixel[0];
                BGR[1]+=(int)pixel[1];
                BGR[2]+=(int)pixel[2];
            }
        }
        int B_mean = BGR[0] / 81;
        int G_mean = BGR[1] / 81;
        int R_mean = BGR[2] / 81;
        
        cout << B_mean << ", " << G_mean << ", " << R_mean << ", " << endl;
    }
}

void onMouse_detect_tshirt(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        Mat image = *(Mat*)userdata;
        Mat image_out = image.clone();
        
        Mat mask(image_out.rows, image_out.cols, CV_8UC1, Scalar(0));
        
        int count=0;
        int BGR[] = {0,0,0};
        for(int i = y-4; i <= y + 4; i++){
            for(int j = x-4; j <= x + 4; j++){
                if (i >= 0 && i < image.rows && j >= 0 && j < image.cols) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    BGR[0] += (int)pixel[0];
                    BGR[1] += (int)pixel[1];
                    BGR[2] += (int)pixel[2];
                    count++;
                }
            }
        }
        
        int B_mean = BGR[0] / count;
        int G_mean = BGR[1] / count;
        int R_mean = BGR[2] / count;
        
        int trashold = 50;
        
        for(int i=0; i<image.rows; i++){
            for(int j=0; j<image.cols; j++){
                Vec3b pixel = image_out.at<Vec3b>(i,j);
                int B_diff = abs((int)pixel[0] - B_mean);
                int G_diff = abs((int)pixel[1] - G_mean);
                int R_diff = abs((int)pixel[2] - R_mean);
                
                if(B_diff<=trashold && G_diff<=trashold && R_diff<=trashold){
                    mask.at<uchar> (i,j) = 255;
                }
            }
        }
        cout << B_mean << ", " << G_mean << ", " << R_mean << ", " << endl;
        imshow("mask", mask);
    }
}

void onMouse_detect_tshirt_color(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        Mat image = *(Mat*)userdata;
        Mat image_out = image.clone();
        
        Mat mask(image_out.rows, image_out.cols, CV_8UC1, Scalar(0));
        
        int count=0;
        int BGR[] = {0,0,0};
        for(int i = y-4; i <= y + 4; i++){
            for(int j = x-4; j <= x + 4; j++){
                if (i >= 0 && i < image.rows && j >= 0 && j < image.cols) {
                    Vec3b pixel = image.at<Vec3b>(i, j);
                    BGR[0] += (int)pixel[0];
                    BGR[1] += (int)pixel[1];
                    BGR[2] += (int)pixel[2];
                    count++;
                }
            }
        }
        
        int B_mean = BGR[0] / count;
        int G_mean = BGR[1] / count;
        int R_mean = BGR[2] / count;
        
        int trashold = 50;
        
        for(int i=0; i<image.rows; i++){
            for(int j=0; j<image.cols; j++){
                Vec3b pixel = image_out.at<Vec3b>(i,j);
                int B_diff = abs((int)pixel[0] - B_mean);
                int G_diff = abs((int)pixel[1] - G_mean);
                int R_diff = abs((int)pixel[2] - R_mean);
                
                if(B_diff<=trashold && G_diff<=trashold && R_diff<=trashold){
                    mask.at<uchar> (i,j) = 255;
                }
            }
        }
        
        Mat output_img(image_out.rows, image_out.cols, CV_8UC3, Scalar(0,0,0));
        
        for(int i=0; i<image.rows; i++){
            for(int j=0; j<image.cols; j++){

                if(mask.at<uchar>(i,j)==0){
                    output_img.at<Vec3b>(i,j) = image_out.at<Vec3b>(i,j);
                }
                else { // otherwise, set the output pixel to the new color
                    output_img.at<Vec3b>(i, j) = Vec3b(92, 37, 201);
                }
            }
        }
        
        cout << B_mean << ", " << G_mean << ", " << R_mean << ", " << endl;
        imshow("output_img", output_img);
    }
}

