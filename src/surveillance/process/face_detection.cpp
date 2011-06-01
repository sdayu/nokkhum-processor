/*
 * face_detection.cpp
 *
 *  Created on: May 26, 2011
 *      Author: boatkrap
 */

#include "face_detection.hpp"

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace nokkhum {

FaceDetection::FaceDetection(CvMatQueue &image_queue) :
	ImageProcessor("Face Detection", image_queue) {
	// TODO Auto-generated constructor stub

}

FaceDetection::~FaceDetection() {
	// TODO Auto-generated destructor stub
}

void FaceDetection::start() {
	cv::namedWindow("Face Detection", 1);

	cv::Mat frame;
	bool is_compute = false;
	while (running) {

		while(image_queue.empty()){
			usleep(100);
		}

		frame = image_queue.pop();
		if (is_compute){
			is_compute = false;
		}
		else{
			is_compute = true;
			continue;
		}
		// TODO face detection here
	}
}

}
