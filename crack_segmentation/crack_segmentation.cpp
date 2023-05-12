//
//  crack_segmentation.cpp
//  segmentation
//
//  Created by onuralp güvercin on 16.04.2023.
//

#include "crack_segmentation.hpp"
using namespace cv;
using namespace std;

ImageSegmentation::ImageSegmentation(string filename) {
    src = imread(filename);
    if (src.empty()) {
        cout << "Could not open or find the image!\n" << endl;
    }
    imshow("src", src);
}

void ImageSegmentation::thresholdImage() {
    Mat mask_2;
    inRange(src, Scalar(0, 0, 0), Scalar(40, 40, 40), mask_2);
    src.setTo(Scalar(255, 255, 255), mask_2);
    inRange(src, Scalar(0, 0, 0), Scalar(254, 254, 254), mask_2);
    src.setTo(Scalar(0, 0, 0), mask_2);
    imshow("thresholded", src);
}

void ImageSegmentation::applyGaussianBlur(int n) {
    GaussianBlur(src, src, Size(n, n), 0);
    imshow("blur", src);
}

void ImageSegmentation::applyMorphologicalOperations(int n1, int n2) {
    Mat element = getStructuringElement(MORPH_RECT, Size(n1, n2));
    erode(src, src, element);
    dilate(src, src, element);
    imshow("eroded", src);
}

void ImageSegmentation::applyMeanShiftFiltering() {
    pyrMeanShiftFiltering(src, src, 10, 50);
    imshow("meanshift", src);
}

//------------------------------ possible functions task2 -----------------------------

void ImageSegmentation::meanFilter(int n){
    Mat kernel = Mat::ones(n, n, CV_32F)/9;
    filter2D(src, src, -1, kernel);
    imshow("meanBlur", src);
}

void ImageSegmentation::MedianBlur(int n){
    medianBlur(src,src,n);
    imshow("medianBlur", src);
}

void ImageSegmentation::grayScale(){
    cvtColor(src, src, COLOR_BGR2GRAY);
    imshow("gray_image", src);
}

void ImageSegmentation::applyKmeans(){
    
    Mat data = src.reshape(1, src.rows * src.cols);
    data.convertTo(data, CV_32F);

    Mat labels, centers;
    kmeans(data, 3, labels, TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);

    labels = labels.reshape(1, src.rows);
    Mat segmented_image(src.size(), CV_8UC3);
    
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            int cluster_idx = labels.at<int>(i, j);
            if (cluster_idx == 0) {
                segmented_image.at<Vec3b>(i, j) = Vec3b(255, 0, 0); // blue color for first segment
            } else if (cluster_idx == 1) {
                segmented_image.at<Vec3b>(i, j) = Vec3b(0, 255, 0); // green color for second segment
            } else {
                segmented_image.at<Vec3b>(i, j) = Vec3b(0, 0, 255); // red color for third segment
            }
        }
    }

    imshow("KMeans Segmentation", segmented_image);
}

void ImageSegmentation::maxFilter(int kernelSize) {

    if (kernelSize % 2 == 0){
        std::cerr << "Error: kernel size must be odd" << std::endl;
        return;
    }

    // Add padding to the image
    int padding = kernelSize / 2;
    cv::Mat paddedImg;
    cv::copyMakeBorder(src, paddedImg, padding, padding, padding, padding, cv::BORDER_REPLICATE);

    // Apply the max filter to the padded image
    for(int i = padding; i < paddedImg.rows - padding; i++){
        for(int j = padding; j < paddedImg.cols - padding; j++){
            int max = 0;
            for(int k = i - padding; k <= i + padding; k++){
                for(int l = j - padding; l <= j + padding ; l++){
                    uchar location = paddedImg.at<uchar>(k, l);
                    if (max <= location){ max = location; }
                }
            }
            src.at<uchar>(i - padding, j - padding) = max;
        }
    }
    
    imshow("max_filter", src);
}

void ImageSegmentation::minFilter(int kernelSize) {
    // Create a temporary image to hold the filtered result
    cv::Mat tempImage = src.clone();

    // Ensure kernel size is odd
    if (kernelSize % 2 == 0) {
        std::cerr << "Error: kernel size must be odd" << std::endl;
        return;
    }

    // Iterate over each pixel in the image
    for (int i = kernelSize / 2; i < src.rows - kernelSize / 2; ++i) {
        for (int j = kernelSize / 2; j < src.cols - kernelSize / 2; ++j) {
            // Extract a kernel of size kernelSize x kernelSize around the current pixel
            cv::Rect roi(j - kernelSize / 2, i - kernelSize / 2, kernelSize, kernelSize);
            cv::Mat kernel = tempImage(roi);

            // Find the minimum pixel value in the kernel
            double minVal, maxVal;
            cv::Point minLoc, maxLoc;
            cv::minMaxLoc(kernel, &minVal, &maxVal, &minLoc, &maxLoc);

            // Set the current pixel to the minimum value in the kernel
            src.at<uchar>(i - kernelSize / 2, j - kernelSize / 2) = static_cast<uchar>(minVal);
        }
    }
    imshow("min_filter", src);
}

//--------------------------- possible functions for task 3 -----------------------------
