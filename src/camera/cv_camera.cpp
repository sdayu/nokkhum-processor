/*
 * cv_camera.cpp
 *
 *  Created on: Apr 17, 2011
 *      Author: boatkrap
 */

#include "cv_camera.hpp"

#include <iostream>
using namespace std;

namespace nokkhum {

CvCamera::CvCamera(int width, int height, int frame_rate, int device) :
	Camera(width, height, frame_rate), device(device) {

	capture = new VideoCapture(device);
	// cerr << "capture: " <<capture->get(CV_CAP_PROP_FPS)<<endl;

	if (!capture->isOpened()) {
		cerr << "Camera failed to open!\n";
	}

}

CvCamera::~CvCamera() {
	delete this->capture;
}

void CvCamera::getImage(Mat& image) {
	*(this->capture) >> image;
}

}
