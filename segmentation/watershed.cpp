//
//  watershed.cpp
//  lab5_desktop
//
//  Created by onuralp güvercin on 27.04.2023.
//

#include "watershed.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include <stack>

// Watershed functions

/**
 * @brief Creates a binary image from the input image.
 *
 * @param _inputImage The input image to be converted to binary image.
 *
 * @return The binary image created from the input image.
 */
cv::Mat create_binary_image(const cv::Mat& _inputImage) {
    // Convert the input image to grayscale
    cv::Mat bw;
    cv::cvtColor(_inputImage, bw, cv::COLOR_BGR2GRAY);
    // Threshold the grayscale image to create a binary image
    cv::threshold(bw, bw, 40, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    // Return the binary image
    return bw;
}

/**
 * @brief Creates a distance image from the binary image using the distance transform algorithm.
 *
 * @param _binaryImage The binary image to be used for creating the distance image.
 *
 * @return The distance image created from the binary image.
 */
cv::Mat distance_image(const cv::Mat& _binaryImage) {

    // Perform the distance transform algorithm
    cv::Mat dist;
    cv::distanceTransform(_binaryImage, dist, cv::DIST_L2, 3);
    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    cv::normalize(dist, dist, 0, 1., cv::NORM_MINMAX);
    // Threshold the distance image to obtain the peaks
    // This will be the markers for the foreground objects
    cv::threshold(dist, dist, .2, 1., cv::THRESH_BINARY);
    // Return the distance image
    return dist;
}

/**
 * @brief Finds the contours in a distance image.
 *
 * @param _distance_image The distance image in which contours are to be found.
 *
 * @return A vector of contours found in the distance image.
 */
std::vector<std::vector<cv::Point>> find_contours(const cv::Mat& _distance_image) {
    // Convert the distance image to CV_8U format, which is required by findContours()
    cv::Mat dist_8u;
    _distance_image.convertTo(dist_8u, CV_8U);
    // Find the contours in the distance image using RETR_EXTERNAL retrieval mode and CHAIN_APPROX_SIMPLE approximation method
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(dist_8u, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Return the contours found in the distance image
    return contours;
}

/**
 * @brief Finds the markers for the watershed algorithm.
 *
 * @param _dist The distance image.
 * @param contours A vector of contours in the distance image.
 * @param ncomp The number of components.
 *
 * @return A matrix of markers for the watershed algorithm.
 */
cv::Mat find_markers(const cv::Mat& _dist, std::vector<std::vector<cv::Point>> contours, int ncomp) {

    // Create a new matrix for markers with the same size as the distance image
    cv::Mat markers = cv::Mat::zeros(_dist.size(), CV_32SC1);

    // Draw the foreground markers
    for (int i = 0; i < ncomp; i++) {
        // Draw a contour on the markers matrix with a value of i+1 for each contour in the vector
        cv::drawContours(markers, contours, i, cv::Scalar::all(i + 1), -1);
    }
    // Draw the background marker
    cv::circle(markers, cv::Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
    // Normalize the markers image so it can be visualized
    //cv::Mat normalized;
    //cv::normalize(markers, normalized, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    //cv::imshow("markers", normalized);

    // Return the markers matrix
    return markers;
}

/**
 * @brief Performs the watershed algorithm on an input image.
 *
 * @param _inputImage The input image to apply watershed to.
 *
 * @return The resulting image after applying watershed.
 */
cv::Mat watershed(const  cv::Mat& _inputImage) {

    // Create a binary image from the input image
    cv::Mat binary_image = create_binary_image(_inputImage);

    // Generate a distance image from the binary image
    cv::Mat dist = distance_image(binary_image);

    // Find the contours in the distance image
    std::vector<std::vector<cv::Point>> contours = find_contours(dist);

    // Determine the number of components in the contours
    int ncomp = contours.size();

    // Generate markers for the watershed algorithm
    cv::Mat markers = find_markers(dist, contours, ncomp);

    // Perform the watershed algorithm on the input image using the generated markers
    cv::watershed(_inputImage, markers);

    // Generate random colors for each labeled object
    std::vector<cv::Vec3b> colors;
    for (int i = 0; i < ncomp; i++)
    {
        int b = cv::theRNG().uniform(0, 255);
        int g = cv::theRNG().uniform(0, 255);
        int r = cv::theRNG().uniform(0, 255);

        colors.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    // Create a result image to hold the labeled objects
    cv::Mat dst = cv::Mat::zeros(markers.size(), CV_8UC3);

    // Fill each labeled object with a random color
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i, j);
            if (index > 0 && index <= ncomp)
                dst.at<cv::Vec3b>(i, j) = colors[index - 1];
            else
                dst.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
        }
    }

    // Return the resulting image after applying watershed
    return dst;
}
