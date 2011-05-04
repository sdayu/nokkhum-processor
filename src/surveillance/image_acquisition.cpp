/*
 * image_acquisition.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "image_acquisition.hpp"

namespace nokkhum {

ImageAcquisition::ImageAcquisition(nokkhum::Camera& camera,
		std::queue<cv::Mat>& image_queue){
	this->camera = &camera;
	this->image_queue = &image_queue;

}

ImageAcquisition::~ImageAcquisition() {
	// TODO Auto-generated destructor stub
}

void ImageAcquisition::start(){
	cv::Mat image;
	running = true;

	while(running){
		*(this->camera) >> image;
		this->image_queue->push(image);
	}
}

}
