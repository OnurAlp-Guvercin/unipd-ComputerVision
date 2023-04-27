//
//  lab5.cpp
//  lab5_desktop
//
//  Created by onuralp güvercin on 27.04.2023.
//

#include "region_growing.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include <stack>

// Show images with fixed SIZE
void show_image(const char* name, const cv::Mat& src) {
    const int SIZE = 500;
    namedWindow(name, cv::WINDOW_NORMAL);
    cv::resizeWindow(name, SIZE, SIZE);
    cv::imshow(name, src);
    cv::waitKey(0);
}

//---------------------------------- Region growing ----------------------------------

std::vector<cv::Point> find_seed_points(cv::Mat& src, bool show_seeds, int thresh_binary) {
    
    // Define the maximum number of black pixels for a seed point.
    const int MAX_BLACK_PIXELS = 50;

    // Convert the source image to grayscale.
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // Threshold the grayscale image to create a binary image with important black points.
    cv::Mat binary;
    cv::threshold(gray, binary, thresh_binary, 255, cv::THRESH_BINARY);

    // Create a structuring element for dilation.
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    // Dilate the binary image until there are no more than MAX_BLACK_PIXELS.
    cv::Mat dilated;
    int total_black_pixels = binary.total() - cv::countNonZero(binary);
    while (total_black_pixels > MAX_BLACK_PIXELS) {
        cv::dilate(binary, dilated, kernel);
        total_black_pixels = dilated.total() - cv::countNonZero(dilated);
        binary = dilated;
    }

    // Find the black pixel coordinates in the image and create a list of seed points.
    std::vector<cv::Point> seed_points;
    for (int y = 0; y < binary.rows; y++) {
        for (int x = 0; x < binary.cols; x++) {
            if (binary.at<uchar>(y, x) == 0) {
                seed_points.push_back(cv::Point(x, y));
            }
        }
    }

    // Show the seed image if show_seeds is true.
    if (show_seeds) {
        cv::imshow("Seed Image", binary);
        cv::waitKey(0);
    }

    // Return the list of seed points.
    return seed_points;
}



/**
 * This function grows a region in an image using a seed point and a threshold.
 * It adds neighboring pixels to the region if they are within the threshold
 * distance from the center pixel.
 *
 * @param src The source image.
 * @param dest The destination image.
 * @param mask A binary mask indicating which pixels are already included in the region.
 * @param seed The seed point to start the region growth.
 * @param threshold The maximum distance between pixels to be included in the region.
 */
void grow(cv::Mat& src, cv::Mat& dest, cv::Mat& mask, cv::Point seed, int threshold) {
    // Define an array of eight 2D shifts to represent the eight neighboring pixels.
    const cv::Point PointShift2D[8] =
    {
        cv::Point(1, 0),
        cv::Point(1, -1),
        cv::Point(0, -1),
        cv::Point(-1, -1),
        cv::Point(-1, 0),
        cv::Point(-1, 1),
        cv::Point(0, 1),
        cv::Point(1, 1)
    };

    // Create a stack to store the seed point and initialize it with the given seed point.
    std::stack<cv::Point> point_stack;
    point_stack.push(seed);

    // Loop while there are still pixels to be processed in the stack.
    while (!point_stack.empty()) {
        // Pop the next pixel to be processed from the top of the stack.
        cv::Point center = point_stack.top();
        mask.at<uchar>(center) = 1;  // Mark the center pixel as included in the current region.
        point_stack.pop();

        // Check the eight neighboring pixels around the center pixel.
        for (int i = 0; i < 8; ++i) {
            // Calculate the coordinates of the neighboring pixel.
            cv::Point estimating_point = center + PointShift2D[i];
            // Skip the neighboring pixel if it is out of range of the image.
            if (estimating_point.x < 0 || estimating_point.x > src.cols - 1 ||
                estimating_point.y < 0 || estimating_point.y > src.rows - 1) {
                continue;
            }
            else {
                // Calculate the Euclidean distance between the center pixel and the neighboring pixel.
                int delta = int(pow(src.at<cv::Vec3b>(center)[0] - src.at<cv::Vec3b>(estimating_point)[0], 2)
                    + pow(src.at<cv::Vec3b>(center)[1] - src.at<cv::Vec3b>(estimating_point)[1], 2)
                    + pow(src.at<cv::Vec3b>(center)[2] - src.at<cv::Vec3b>(estimating_point)[2], 2));
                // Add the neighboring pixel to the current region if it meets the conditions.
                if (dest.at<uchar>(estimating_point) == 0 && mask.at<uchar>(estimating_point) == 0 && delta < threshold) {
                    mask.at<uchar>(estimating_point) = 1;
                    point_stack.push(estimating_point);
                }
            }
        }
    }
}


/**
* This function applies a seed-growing algorithm to segment the input image into connected regions based on the similarity of pixel values between neighboring pixels.
*
* @param src The source image to segment.
* @param seed_points A list of seed points to start the segmentation.
* @param threshold A threshold value for the pixel value similarity.
*
* @return A binary image where each connected region is labeled with a unique integer value.
*/
cv::Mat region_grow(cv::Mat& src, std::vector<cv::Point> seed_points, int threshold) {

    uchar pixel_range = 255;
    
    // create a binary image `dest` to store the segmented image
    cv::Mat dest = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    // create a binary image `mask` to store the current region being segmented
    cv::Mat mask = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);

    // loop over each seed point to segment the image
    for (const auto& seed_point : seed_points) {

        // check if the seed point has not been segmented already
        if (dest.at<uchar>(seed_point) == 0) {
            // apply seed-growing algorithm to segment the image
            grow(src, dest, mask, seed_point, threshold);

            // record new region to `dest`
            dest = dest + mask * pixel_range;

            // zero mask, ready for next segmentation
            mask = mask - mask;
        }
    }
    // return the segmented image
    return dest;
}
