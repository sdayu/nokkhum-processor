/*
 * image_acquisition.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "image_acquisition.hpp"
#include "../../image/image.hpp"
#include <iostream>
#include <thread>
#include <glog/logging.h>

#include <string>
#include <cstdlib>
#include <ctime>

namespace nokkhum {

ImageAcquisition::ImageAcquisition(nokkhum::Camera& camera,
		unsigned int queue_size) :
		Job("ImageAcquisition"), camera(camera) {

	this->running = false;

	for(unsigned int i = 0; i < queue_size; ++i){
		this->multiple_queue.getNew();
	}

}

ImageAcquisition::~ImageAcquisition() {
}

void ImageAcquisition::start() {

	cv::Mat image, copy_image;
	running = true;
	unsigned int counter = 0;

	ImageAcquisitionMonitor iam(running, counter);
	std::thread monitor = std::thread(std::ref(iam));

//	camera >> image;
//	std::srand(std::time(0));
//
//	cv::imwrite("/tmp/"+std::to_string(std::rand())+".png", image);
	while (running) {
		camera >> image;
		if(image.empty()){
			LOG(INFO) << "Image Empty ";
			unsigned int count = 0;
			if(camera.isOpen()){
				while (running) {
					camera >> image;
					if(image.empty()){
						count++;
					}
					else{
						break;
					}
					if (count > 30 && multiple_queue.get(0)->empty()){
						LOG(INFO) << "Image Empty more than 30";
						throw std::runtime_error("Image Empty more than 30");
					}
				}
			}
		}

		copy_image = image.clone();
		nokkhum::Image the_image(copy_image);

		for (unsigned int  i = 0; i < multiple_queue.getSize(); ++i) {
			multiple_queue.get(i)->push(the_image);
		}
		++counter;
	}

	monitor.join();
}

void ImageAcquisition::stop() {
	this->running = false;
}

std::shared_ptr<ImageQueue> ImageAcquisition::getNewOutputImageQueue() {
	return this->multiple_queue.getNew();
}

nokkhum::MultipleImageQueue *ImageAcquisition::getOutputImageQueue() {
	return &this->multiple_queue;
}

}
