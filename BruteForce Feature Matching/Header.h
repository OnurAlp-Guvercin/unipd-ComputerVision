//
//  Header.h
//  lab6
//
//  Created by onuralp güvercin on 12.05.2023.
//

#ifndef Header_h
#define Header_h
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

class ORB_FeatureDetector {
public:
    ORB_FeatureDetector(const std::string& path1, const std::string& path2);
    void compareImages();
    
private:
    cv::Mat img1;
    cv::Mat img2;
    cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> descriptor;
    cv::BFMatcher matcher;
    std::vector<cv::KeyPoint> keypoints1;
    std::vector<cv::KeyPoint> keypoints2;
    cv::Mat descriptors1;
    cv::Mat descriptors2;
    std::vector<cv::DMatch> matches;
    std::vector<cv::DMatch> topMatches;
    float avgDistance;
    float similarityThreshold;
    
    void detectKeypoints();
    void computeDescriptors();
    void matchDescriptors();
    void selectTopMatches(int k = 10);
    void calculateAverageDistance();
    void checkSimilarity();
    void drawFilteredMatches(float distanceThreshold);
    
};


class SIFT_FeatureDetector {
public:
    SIFT_FeatureDetector(const std::string& path1, const std::string& path2);
    void CompareImages();
    
private:
    cv::Mat img1;
    cv::Mat img2;
    cv::Ptr <cv::SIFT> sift;
    std::vector<cv::KeyPoint> kp1;
    std::vector<cv::KeyPoint> kp2;
    cv::Mat des1;
    cv::Mat des2;
    cv::BFMatcher bf;
    std::vector<std::vector<cv::DMatch>> matches;
    
    void detect_keypoints();
    void compute_descriptors();
    void find_good_matches();
    
};


#endif /* Header_h */
