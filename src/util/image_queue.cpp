/*
 * cv_mat_queue.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: boatkrap
 */

#include "image_queue.hpp"

#include <iostream>

#include <glog/logging.h>

#include <thread>
#include <chrono>

#include "../command_interface/program_reporter.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

namespace nokkhum {

ImageQueue::ImageQueue() {
	// TODO Auto-generated constructor stub
//	std::cout<<"construct "<<" this->"<<this <<std::endl;

}

ImageQueue::~ImageQueue() {
	// TODO Auto-generated destructor stub
}

void ImageQueue::push(nokkhum::Image mat) {


	queue_mutex.lock();
	image_queue.push(mat);
	queue_mutex.unlock();

	if (this->size() > 300 ){
		if(this->drop){
			this->drop = false;
			LOG(INFO) << "thread: " << std::this_thread::get_id() << " cv_mat_queue drop";
			this->pop();
			Json::Value message;
			message["method"] = "drop_motion";
			message["description"] = "queue drop motion";

			boost::posix_time::ptime current_time = boost::posix_time::microsec_clock::local_time();
			message["date"]			= boost::posix_time::to_iso_extended_string(current_time);
			nokkhum::ProgramReporter().report(message);

		}
		else{
			this->drop = true;
		}
	}

	if (this->size() > 100 ){
		LOG(INFO) << "thread: " << std::this_thread::get_id() << " cv_mat_queue size: " << this->size();
		std::chrono::milliseconds duration( 100 );
		std::this_thread::sleep_for( duration );
	}

	if (this->size() > 500 ){
		throw std::runtime_error("Queue not consume");
	}

}

nokkhum::Image ImageQueue::pop() {
	queue_mutex.lock();
	nokkhum::Image mat = image_queue.front();
	image_queue.pop();
	queue_mutex.unlock();
	return mat;
}

bool ImageQueue::empty() {
	return image_queue.empty();
}

unsigned int ImageQueue::size() {
	return image_queue.size();
}

}
