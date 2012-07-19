/*
 * image_acquisition.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "image_acquisition.hpp"
#include <iostream>
#include <exception>
#include <glog/logging.h>

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
	unsigned int i = 0;


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
					if (count > 30){
						LOG(INFO) << "Image Empty more than 30";
						throw std::exception();
					}
				}
			}
		}
		copy_image = image.clone();
		for (i = 0; i < multiple_queue.getSize(); ++i) {
			multiple_queue.get(i)->push(copy_image);
		}
	}
}

void ImageAcquisition::operator()() {
	this->start();
}

void ImageAcquisition::stop() {
	this->running = false;
}

CvMatQueue* ImageAcquisition::getNewOutputImageQueue() {
	return this->multiple_queue.getNew();
}

nokkhum::MultipleMatQueue *ImageAcquisition::getOutputImageQueue() {
	return &this->multiple_queue;
}

}
