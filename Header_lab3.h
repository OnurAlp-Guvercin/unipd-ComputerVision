//
//  Header_lab3.h
//  Callback_and_color_segmentation
//
//  Created by onuralp güvercin on 30.03.2023.
//

#ifndef HEADER_LAB3_H
#define HEADER_LAB3_H

#include <opencv2/opencv.hpp>

void onMouse(int event, int x, int y, int flags, void* userdata);
void onMouse_square(int event, int x, int y, int flags, void* userdata);
void onMouse_detect_tshirt(int event, int x, int y, int flags, void* userdata);
void onMouse_detect_tshirt_color(int event, int x, int y, int flags, void* userdata);

#endif

