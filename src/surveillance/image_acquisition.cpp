/*
 * image_acquisition.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "image_acquisition.hpp"

namespace nokkhum {

ImageAcquisition::ImageAcquisition(nokkhum::Camera& camera,
		MultipleMatQueue& multiple_queue):
		camera(camera), multiple_queue(multiple_queue)
		{

	this->running = false;
}

ImageAcquisition::~ImageAcquisition() {
	// TODO Auto-generated destructor stub
}

void ImageAcquisition::start() {
	cv::Mat image;
	running = true;
	int i = 0;

	while (running) {
		camera >> image;
		for(i = 0; i < multiple_queue.getSize(); ++i){
			multiple_queue.get(i).push(image.clone());
		}
	}
}

void ImageAcquisition::operator()() {
	this->start();
}

void ImageAcquisition::stop() {
	this->running = false;
}

}
