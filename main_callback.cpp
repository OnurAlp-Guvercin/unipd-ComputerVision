//
//  main.cpp
//  Callback_and_color_segmentation
//
//  Created by onuralp güvercin on 30.03.2023.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include "Header_lab3.h"

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("/Users/onuralpguvercin/Desktop/computer_vision_unipd/labs/Lab_3_Callback_and_color_segmentation-20230327/robocup.jpg");

    if (image.empty()) {
        cout << "Error: Could not open or find the image." << endl;
        return -1;
    }

    namedWindow("Image");
    //setMouseCallback("Image", onMouse, (void*)&image);
    //setMouseCallback("Image", onMouse_square, (void*)&image);
    //setMouseCallback("Image", onMouse_detect_tshirt, (void*)&image);
    setMouseCallback("Image", onMouse_detect_tshirt_color, (void*)&image);
    imshow("Image", image);
    waitKey(0);

    return 0;
}


