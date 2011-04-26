//============================================================================
// Name        : main.cpp
// Author      : Thanathip Limna
// Version     :
// Copyright   :
// Description : Hello World in C++
//============================================================================

#include <iostream>
using namespace std;

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

#include "camera/cv_camera.hpp"

int main() {
	cout << "Hello World, Hello Nuk Khum" << endl; // prints Hello World, Hello Nukkhum

    namedWindow("video",1);

    nokkhum::CvCamera camera(320, 240, 10, 0);

    for(;;)
    {
            // get a new frame from camera


            // show frame on screen
            imshow("video", camera.get_image());

            if(waitKey(1) >= 2) break;
    }

    return 0;
}
