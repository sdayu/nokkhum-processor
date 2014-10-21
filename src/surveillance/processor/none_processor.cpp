/*
 * video_recorder.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "none_processor.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <thread>
#include <chrono>
#include <exception>


#include <glog/logging.h>


namespace nokkhum {

NoneProcessor::NoneProcessor(ImageQueue& input_image_queue) :
		ImageProcessor("None Processor", input_image_queue) {
	this->running = false;
}

NoneProcessor::NoneProcessor(ImageQueue & input_image_queue,
		NoneProcessorAttribute &npa) :
		ImageProcessor(npa.getName(), input_image_queue) {
	this->running = false;

}

NoneProcessor::~NoneProcessor() {
}

void NoneProcessor::start() {
	LOG(INFO) << "Start None Processor";
	this->popImage();
}

void NoneProcessor::stop() {
	LOG(INFO)<<"Stop None Processor";
	Job::stop();

}

void NoneProcessor::popImage() {
	while (running) {

			if (input_image_queue.empty()) {
				std::this_thread::sleep_for(std::chrono::microseconds(1000));
				continue;
			}

			input_image_queue.pop();
		}

}



}
