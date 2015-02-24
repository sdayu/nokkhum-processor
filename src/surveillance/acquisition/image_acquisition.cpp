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
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
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
	unsigned int counter = 0;
	int frame_counter = 0;
	unsigned int wait_time = 1000000 / camera.getFps(); // sleep in micro secound

	ImageAcquisitionMonitor iam(running, counter);
	std::thread monitor = std::thread(std::ref(iam));
	std::chrono::high_resolution_clock::time_point first_frame_time = std::chrono::high_resolution_clock::now();

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
		++frame_counter;

		std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed =  current_time - first_frame_time;
		if(elapsed.count() > 1 ){
			if(frame_counter < camera.getFps()){
				wait_time -= 10;
				if(wait_time < 0)
					wait_time = 0;
			}
			else if(frame_counter > camera.getFps()){
				wait_time += 10;
			}
			first_frame_time = current_time;

			std::time_t check_time = std::chrono::system_clock::to_time_t(current_time);
			std::cout << "finished computation at " << std::ctime(&check_time);
			std::cout << "fps: " << frame_counter << " wait time: " << wait_time << " e: " << elapsed.count() << std::endl;
			frame_counter = 0;
		}


		std::this_thread::sleep_for(std::chrono::microseconds(wait_time));

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
