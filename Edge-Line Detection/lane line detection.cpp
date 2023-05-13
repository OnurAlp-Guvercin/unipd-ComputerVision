//
//  lane line detection.cpp
//  edge_line_detection
//
//  Created by onuralp güvercin on 9.04.2023.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;

static int lowThreshold = 0;
static int max_Threshold = 100;
static const int kernel_size = 3;



cv::Mat line_detection(cv::Mat src){
    
    Mat hsvImg;
    cvtColor(src, hsvImg, COLOR_BGR2HSV);

    // Define the range of white color in HSV
    cv::Scalar lowerWhite = cv::Scalar(0, 0, 200);
    cv::Scalar upperWhite = cv::Scalar(0, 0, 255);

    // Create a mask for white color in the HSV image
    cv::Mat whiteMask;
    cv::inRange(hsvImg, lowerWhite, upperWhite, whiteMask);

    // Apply the mask to the original image
    cv::Mat whiteImg;
    src.copyTo(whiteImg, whiteMask);
    
    namedWindow("whiteMask");
    imshow("whiteMask", whiteMask);
    return whiteMask;
}

cv::Mat line_detection2 (cv::Mat src){
    Mat gray_img;
    cvtColor(src, gray_img, COLOR_BGR2GRAY);
    threshold(gray_img, gray_img, 240, 255, THRESH_BINARY);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(gray_img, gray_img, kernel); // perform erosion
    dilate(gray_img, gray_img, kernel);
    medianBlur(gray_img, gray_img, 5);
    
    return gray_img;
}


Mat HoughTransformation(Mat src_gray, Mat img){

    Mat out;
    Mat detected_edges;

    blur(src_gray, detected_edges, Size(3,3));
    Canny(detected_edges, detected_edges, lowThreshold, max_Threshold, kernel_size);
    cvtColor(detected_edges, out, COLOR_GRAY2BGR);

    std::vector<Vec2f> lines; // will hold the results of the detection
    HoughLines(detected_edges, lines, 1, CV_PI/180, 50); // runs the actual detection

    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        std::cout << lines[i][0] << "----" << lines[i][1] << std::endl;
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( img, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }
    
    return img;
}

Mat HoughTransformation2(Mat src_gray, Mat img){
    Mat out;
    Mat detected_edges;

    blur(src_gray, detected_edges, Size(3,3));
    Canny(detected_edges, detected_edges, lowThreshold, max_Threshold, kernel_size);
    cvtColor(detected_edges, out, COLOR_GRAY2BGR);

    std::vector<Vec2f> lines; // will hold the results of the detection
    HoughLines(detected_edges, lines, 1, CV_PI/180, 50); // runs the actual detection

    // Find the two strongest lines
    Vec2f line1(0,0), line2(0,0);
    float max_rho1 = 0, max_rho2 = 0;

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];

        if (rho > max_rho1) {
            if (abs(theta - line2[1]) > 0.7) {
                line2 = line1;
                max_rho2 = max_rho1;
                line1 = lines[i];
                max_rho1 = rho;
            }
        } else if (rho > max_rho2) {
            if (abs(theta - line1[1]) > 0.7) {
                line2 = lines[i];
                max_rho2 = rho;
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        float rho = (i == 0) ? line1[0] : line2[0];
        float theta = (i == 0) ? line1[1] : line2[1];

        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line(img, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    }

    return img;
}


Mat HoughTransformationP(Mat src_gray, Mat img){
    
    Mat out;
    Mat detected_edges;
    
    blur(src_gray, detected_edges, Size(3,3));
    Canny(detected_edges, detected_edges, lowThreshold, max_Threshold, kernel_size);
    cvtColor(detected_edges, out, COLOR_GRAY2BGR);
    
    //cv::Mat hough = HoughTransformation(detected_edges);
    //cv::Mat out = detected_edges.clone();
    
    // Probabilistic Line Transform
    std::vector<Vec4i> lines; // will hold the results of the detection
    HoughLinesP(detected_edges, lines, 1, CV_PI/180, 45, 10, 15); // runs the actual detection
    
    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
        {
            Vec4i l = lines[i];
            line( img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }
    
    return img;
}








