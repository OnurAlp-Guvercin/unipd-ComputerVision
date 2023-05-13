
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
#include "lane line detection.hpp"

Mat src, src_gray;
Mat dst, detected_edges;

int lowThreshold = 0;
const int max_lowThreshold = 100;

int max_Threshold = 100;
const int max_maxThreshold = 200;

const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold_(int, void*)
{
    /*
     detected_edges: Source image, grayscale
     detected_edges: Output of the detector (can be the same as the input)
     lowThreshold: The value entered by the user moving the Trackbar
     highThreshold: Set in the program as three times the lower threshold (following Canny's recommendation)
     kernel_size: We defined it to be 3 (the size of the Sobel kernel to be used internally)
     */
    //this is recomended version
    //Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    
    blur( src_gray, detected_edges, Size(3,3) );
    Canny(detected_edges, detected_edges, lowThreshold, max_Threshold, kernel_size);
    dst = Scalar::all(0); //fill the dst with zeros
    src.copyTo(dst, detected_edges); //copy src image to dst but the only colored pixels are the ones that are detected as edges
    imshow( window_name, dst );
}


int main()
{
  src = imread("/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_4_Edge_and_line_detection-2023040/street_scene.png");
    //Load an image
  if( src.empty() )
  {
    std::cout << "Could not open or find the image!\n" << std::endl;
    return -1;
  }
    
    //src_gray = line_detection(src);
    src_gray = line_detection2(src);
    namedWindow("src_gray");
    imshow("src_gray", src_gray);
    
    /*
    //---------------------------------- createing trackbar and getting optimal value --------------------------------------
    //make the size and type of dst image as the same with src
    dst.create(src_gray.size(), src_gray.type() );
    //convert it to gray scale
    //cvtColor( img, src_gray, COLOR_BGR2GRAY );
    namedWindow( window_name, WINDOW_AUTOSIZE );
    //create trackbar for Min Threshold
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold_ );
    //create trackbar for Max Threshold
    createTrackbar( "Max Threshold:", window_name, &max_Threshold, max_maxThreshold, CannyThreshold_ );

    //initialize the canny
    CannyThreshold_(0, 0);
    waitKey(0);
    //-----------------------------------------------------------------------------------------------------------------------
     */
    
    //cv::Mat out = HoughTransformation(src_gray, src);
    cv::Mat out = HoughTransformation2(src_gray, src);
    //cv::Mat out = HoughTransformationP(src_gray, src);

    namedWindow("Hough Transformation");
    imshow("Hough Transformation", out);
    waitKey(0);
    
  return 0;
}
