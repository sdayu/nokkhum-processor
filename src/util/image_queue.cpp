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
