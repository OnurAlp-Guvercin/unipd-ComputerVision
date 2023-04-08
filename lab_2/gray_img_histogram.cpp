//
//  gray_img_histogram.cpp
//  lab_2
//
//  Created by onuralp güvercin on 20.03.2023.
//


#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void gray_histogram(cv::Mat& img){
    //cvtColor can modify the contents of the img object directly,
    //even though you only intended to modify the gray_img object.
    //This is why making a copy of the img object before passing it to cvtColor using the clone() function solved the problem.
    
    // ---------------------loads the image and converts it to gray scale--------------------------
    cv::Mat gray_img = img.clone();
    cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
    std::cout << gray_img.channels() << std::endl;
    cv::imwrite("/Users/onuralpguvercin/Desktop/gray_image.jpg", gray_img);
    //---------------------------------------------------------------------------------------------
    
    // ---------------------histogram equalization---------------------
    equalizeHist(gray_img, gray_img);
    //-----------------------------------------------------------------
    
    
    // Initialize variables for histogram calculation
    int histSize = 256; // number of bins (tunable)
    float range[] = {0, 256};
    const float* histRange = {range};
    bool uniform = true, accumulate = false;

    // Create the Mat object
    cv::Mat hist;
    //histogram calculation
    calcHist(&gray_img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
    
    //Create an image to display the histograms:
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(0,0,0));
    
    //Notice that before drawing, we first cv::normalize the histogram
    //so its values fall in the range indicated by the parameters entered
    normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    
    for( int i = 1; i < histSize; i++ )
        {
            line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ),
                 Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                 Scalar( 255, 0, 0), 2, 8, 0  );
        }
    
    cv::namedWindow("histogram");
    cv::namedWindow("gray_img");
    
    cv::imshow("histogram", histImage);
    cv::imshow("gray_img", gray_img);
    
    cv::waitKey(0);
}

