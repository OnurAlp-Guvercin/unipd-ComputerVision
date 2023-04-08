#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

// Function to apply a max filter to an image
void maxFilter(cv::Mat& img, int kernelSize) {
    // Create a temporary image to hold the filtered result
    cv::Mat tempImage = img.clone();

    // Ensure kernel size is odd
    if (kernelSize % 2 == 0) {
        std::cerr << "Error: kernel size must be odd" << std::endl;
        return;
    }

    // Iterate over each pixel in the image
    for (int i = kernelSize / 2; i < img.rows - kernelSize / 2; ++i) {
        for (int j = kernelSize / 2; j < img.cols - kernelSize / 2; ++j) {
            // Extract a kernel of size kernelSize x kernelSize around the current pixel
            cv::Rect roi(j - kernelSize / 2, i - kernelSize / 2, kernelSize, kernelSize);
            cv::Mat kernel = tempImage(roi);

            // Find the maximum pixel value in the kernel
            double minVal, maxVal;
            cv::Point minLoc, maxLoc;
            cv::minMaxLoc(kernel, &minVal, &maxVal, &minLoc, &maxLoc);

            // Set the current pixel to the maximum value in the kernel
            img.at<uchar>(i - kernelSize / 2, j - kernelSize / 2) = static_cast<uchar>(maxVal);
        }
    }
}
//-------------------------------- Tried to implement max filter without minMaxLoc with extra padding ---------------------------------
// Function to apply a max filter to an image
void maxFilter_manual(cv::Mat& img, int kernelSize) {

    if (kernelSize % 2 == 0){
        std::cerr << "Error: kernel size must be odd" << std::endl;
        return;
    }

    // Add padding to the image
    int padding = kernelSize / 2;
    cv::Mat paddedImg;
    cv::copyMakeBorder(img, paddedImg, padding, padding, padding, padding, cv::BORDER_REPLICATE);

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
            img.at<uchar>(i - padding, j - padding) = max;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------

// Function to apply a min filter to an image
void minFilter(cv::Mat& img, int kernelSize) {
    // Create a temporary image to hold the filtered result
    cv::Mat tempImage = img.clone();

    // Ensure kernel size is odd
    if (kernelSize % 2 == 0) {
        std::cerr << "Error: kernel size must be odd" << std::endl;
        return;
    }

    // Iterate over each pixel in the image
    for (int i = kernelSize / 2; i < img.rows - kernelSize / 2; ++i) {
        for (int j = kernelSize / 2; j < img.cols - kernelSize / 2; ++j) {
            // Extract a kernel of size kernelSize x kernelSize around the current pixel
            cv::Rect roi(j - kernelSize / 2, i - kernelSize / 2, kernelSize, kernelSize);
            cv::Mat kernel = tempImage(roi);

            // Find the minimum pixel value in the kernel
            double minVal, maxVal;
            cv::Point minLoc, maxLoc;
            cv::minMaxLoc(kernel, &minVal, &maxVal, &minLoc, &maxLoc);

            // Set the current pixel to the minimum value in the kernel
            img.at<uchar>(i - kernelSize / 2, j - kernelSize / 2) = static_cast<uchar>(minVal);
        }
    }
}

void GaussianFilter(cv::Mat img, cv::Size Size = cv::Size(5,5), float Sigma=1.0){
    cv::GaussianBlur(img, img, Size, Sigma);
}

void MedianFilter(cv::Mat img, cv::Mat filtered_img, int Size = 5){
    cv::medianBlur(img, filtered_img, Size);
}
