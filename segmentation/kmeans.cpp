//
//  kmeans.cpp
//  lab5_desktop
//
//  Created by onuralp güvercin on 27.04.2023.
//

#include "kmeans.hpp"
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <vector>

/**
 * Performs k-means clustering on an input image and returns the clustered result.
 *
 * @param src The input image to cluster.
 * @param number_clusters The number of clusters to use for k-means clustering.
 * @return A cv::Mat containing the clustered result.
 */
cv::Mat kmeans_clustered(const cv::Mat& src, int number_clusters) {

    // Creating the matrix that holds all pixel data
    cv::Mat data = cv::Mat::zeros(src.cols * src.rows, 3, CV_32F);

    // Returns from the K Means
    cv::Mat bestLabels, centers, clustered;

    // Holds the BGR channels
    std::vector<cv::Mat> bgr;
    cv::split(src, bgr);

    // Getting all pixels in the Data row column to be compatible with K Means
    for (int i = 0; i < src.cols * src.rows; i++) {
        data.at<float>(i, 0) = bgr[0].data[i] / 255.0;
        data.at<float>(i, 1) = bgr[1].data[i] / 255.0;
        data.at<float>(i, 2) = bgr[2].data[i] / 255.0;
    }

    // Performs k-means clustering on the data
    cv::kmeans(data, number_clusters, bestLabels,
        cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0),
        10, cv::KMEANS_PP_CENTERS, centers);

    // Reshape the centers and data matrices to match the input image
    centers = centers.reshape(3, centers.rows);
    data = data.reshape(3, data.rows);

    // Create a new matrix to hold the clustered result
    clustered = cv::Mat(src.rows, src.cols, CV_32F);

    // Assign the pixel values in the clustered matrix based on the cluster centers
    cv::Vec3f* p = data.ptr<cv::Vec3f>();
    for (size_t i = 0; i < data.rows; i++) {
        int center_id = bestLabels.at<int>(i);
        p[i] = centers.at<cv::Vec3f>(center_id);
    }

    // Reshape the clustered matrix to match the input image
    clustered = data.reshape(3, src.rows);

    return clustered;
}
