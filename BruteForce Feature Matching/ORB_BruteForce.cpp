//
//  ORB_BruteForce.cpp
//  lab6
//
//  Created by onuralp güvercin on 12.05.2023.
//


#include "Header.h"
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//-------------------------- public --------------------------
ORB_FeatureDetector::ORB_FeatureDetector(const std::string& path1, const std::string& path2)
    : img1(cv::imread(path1)),
      img2(cv::imread(path2)),
      detector(cv::ORB::create()),
      descriptor(cv::ORB::create()),
      matcher(cv::BFMatcher(cv::NORM_HAMMING)),
      similarityThreshold(50.0f)
{}

void ORB_FeatureDetector::compareImages() {
    cv::cvtColor(img1, img1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2, img2, cv::COLOR_BGR2GRAY);
    
    detectKeypoints();
    computeDescriptors();
    matchDescriptors();
    selectTopMatches(50);
    calculateAverageDistance();
    checkSimilarity();
    drawFilteredMatches(30.0f);
}

//-------------------------- private --------------------------
void ORB_FeatureDetector::detectKeypoints(){
    detector -> detect(img1, keypoints1);
    detector -> detect(img2, keypoints2);
}

void ORB_FeatureDetector::computeDescriptors(){
    descriptor->compute(img1, keypoints1, descriptors1);
    descriptor->compute(img2, keypoints2, descriptors2);
}
void ORB_FeatureDetector::matchDescriptors(){
    matcher.match(descriptors1, descriptors2, matches);
}
void ORB_FeatureDetector::selectTopMatches(int k) {
    std::sort(matches.begin(), matches.end(), [](const cv::DMatch& a, const cv::DMatch& b) {
        return a.distance < b.distance;
    });

    k = std::min(k, static_cast<int>(matches.size())); // Ensure k is within the range of matches
    topMatches.assign(matches.begin(), matches.begin() + k);
}
void ORB_FeatureDetector::calculateAverageDistance(){
    avgDistance = 0;
    for(const cv::DMatch& match : topMatches){
        avgDistance += match.distance;
    }
    avgDistance /= topMatches.size();
}
void ORB_FeatureDetector::checkSimilarity(){
    if (avgDistance <= similarityThreshold) {
        std::cout << "The two images have similar content." << std::endl;
    }
    else {
        std::cout << "The two images have different content." << std::endl;
    }
}
void ORB_FeatureDetector::drawFilteredMatches(float distanceThreshold){
    std::vector<cv::DMatch> filteredMatches;
    
    for(const cv::DMatch& match : topMatches){
        if (match.distance < distanceThreshold){
            filteredMatches.push_back(match);
        }
    }
    cv::Mat imgMatches;
    cv::drawMatches(img1, keypoints1, img2, keypoints2, filteredMatches, imgMatches);
    cv::namedWindow("Matches", cv::WINDOW_NORMAL);
    cv::imshow("Matches", imgMatches);
    cv::waitKey(0);
}
