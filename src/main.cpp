//============================================================================
// Name        : main.cpp
// Author      : Thanathip Limna
// Version     :
// Copyright   :
// Description : Hello World in C++
//============================================================================
#include <cmath>
#include <ctime>

#include <iostream>
using namespace std;

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

#include "camera/cv_ip_camera.hpp"
#include "video/cv_video_writer.hpp"
#include "surveillance/video_surveillance.hpp"

int main() {
	cout << "Hello World, Hello Nuk Khum" << endl; // prints Hello World, Hello Nukkhum

    nokkhum::VideoSurveillance vs;
    vs.start();

    return 0;
}
