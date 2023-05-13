#include "Header.h"
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

SIFT_FeatureDetector::SIFT_FeatureDetector(const std::string& path1, const std::string& path2)
    // Load the two grayscale images
        : img1(cv::imread(path1, cv::IMREAD_GRAYSCALE)),
          img2(cv::imread(path2, cv::IMREAD_GRAYSCALE)),
    // Create a SIFT detector
          sift(cv::SIFT::create())
    {}
    
void SIFT_FeatureDetector::CompareImages(){
        detect_keypoints();
        compute_descriptors();
        find_good_matches();
    }
    
void SIFT_FeatureDetector::detect_keypoints(){
        // Detect keypoints and compute descriptors for the first image
        sift->detectAndCompute(img1, cv::noArray(), kp1, des1);
        sift->detectAndCompute(img2, cv::noArray(), kp2, des2);
    }

void SIFT_FeatureDetector::compute_descriptors(){
        // Perform k-nearest neighbor matching between the descriptors of the two images
        bf.knnMatch(des1, des2, matches, 2);
    }

void SIFT_FeatureDetector::find_good_matches(){
        std::vector<cv::DMatch> good;
        
        for (size_t i = 0; i < matches.size(); i++) {
            if (matches[i][0].distance < 0.75 * matches[i][1].distance) {
                good.push_back(matches[i][0]);
                }
            }
    
        cv::Mat img3;
        cv::drawMatches(img1, kp1, img2, kp2, good, img3);
        cv::imshow("Matches", img3);
        cv::waitKey(0);
    }
    

