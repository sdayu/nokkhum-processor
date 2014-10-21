/*
 * cv_camera.cpp
 *
 *  Created on: Apr 17, 2011
 *      Author: boatkrap
 */

#include "cv_camera.hpp"

#include <iostream>
#include <exception>

#include <opencv2/opencv.hpp>

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
	cv::Mat aq_image;
	*(this->capture) >> aq_image;
	if (aq_image.size() != cv::Size(this->getWidth(), this->getHeight())){
		cv::resize(aq_image, image, cv::Size(this->getWidth(), this->getHeight()));
	}
	else {
		image = aq_image;
	}
}

bool CvCamera::isOpen(){
	if (capture == nullptr)
		return false;
	else
		return capture->isOpened();
}
}
