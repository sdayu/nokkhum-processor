/*
 * cv_camera.cpp
 *
 *  Created on: Apr 17, 2011
 *      Author: boatkrap
 */

#include "cv_camera.hpp"

#include <iostream>
#include <exception>

namespace nokkhum {

CvCamera::CvCamera(int width, int height, int fps, int device) :
	Camera(width, height, fps), device(device) {

	capture = new VideoCapture(device);
	// cerr << "capture: " <<capture->get(CV_CAP_PROP_FPS)<<endl;

	if (!capture->isOpened()) {
		std::cerr << "Camera failed to open!\n";
		throw std::exception(); //TODO need to specify exception
	}

}

CvCamera::~CvCamera() {
	delete this->capture;
}

void CvCamera::getImage(Mat& image) {
	*(this->capture) >> image;
}

bool CvCamera::isOpen(){
	if (capture == nullptr)
		return false;
	else
		return capture->isOpened();
}
}
