/*
 * image_acquisition.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "image_acquisition.hpp"

namespace nokkhum {

ImageAcquisition::ImageAcquisition(nokkhum::Camera& camera,
		std::queue<cv::Mat>& image_queue):
		camera(camera), image_queue(image_queue)
		{

	this->running = false;
}

ImageAcquisition::~ImageAcquisition() {
	// TODO Auto-generated destructor stub
}

void ImageAcquisition::start() {
	cv::Mat image;
	running = true;

	while (running) {
		camera >> image;
		image_queue.push(image);
	}
}

void ImageAcquisition::operator()() {
	this->start();
}

void ImageAcquisition::stop() {
	this->running = false;
}

}
