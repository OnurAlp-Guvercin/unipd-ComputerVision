//
//  main.cpp
//  lab5_desktop
//
//  Created by onuralp güvercin on 27.04.2023.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <stack>

#include "region_growing.hpp"
#include "watershed.hpp"
#include "kmeans.hpp"

int main() {
    // Read images from file
    cv::Mat src, src1,src2,src3,street,robocop;
    src1 = cv::imread("/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_5_Segmentation-20230415/Asphalt-1.png");
    src2 = cv::imread("/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_5_Segmentation-20230415/Asphalt-2.png");
    src3 = cv::imread("/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_5_Segmentation-20230415/Asphalt-3.png");
    street = cv::imread("/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_4_Edge_and_line_detection-2023040/street_scene.png");
    robocop = cv::imread("/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_3_Callback_and_color_segmentation-20230327/robocup.jpg");
    src = src2;
    /*
//----------------------------------------------------------------------------------------------------------
    // Find seed points in the image using a helper function
    std::vector<cv::Point> seed_points = find_seed_points(src, false, 10);
    // Set the threshold for the region growing algorithm
    int threshold = 500;
    // Apply region growing algorithm to segment the image
    cv::Mat segmented = region_grow(src, seed_points, threshold);
    // Display the original image
    show_image("original", src);
    // Display the segmented image
    show_image("segmented", segmented);
     
//----------------------------------------------------------------------------------------------------------
    
    cv::Mat segmented = watershed(street);
    show_image("Segmented", segmented);
     */
//----------------------------------------------------------------------------------------------------------

    cv::Mat clustered = kmeans_clustered(robocop, 2);
    show_image("clustered", clustered);
}
