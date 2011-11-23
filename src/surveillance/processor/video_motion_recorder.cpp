/*
 * video_record_motion.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: boatkrap
 */

#include "video_motion_recorder.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

namespace nokkhum {

VideoMotionRecorder::VideoMotionRecorder(CvMatQueue & input_image_queue,
		VideoRecorderAttribute *vrp) : VideoRecorder(input_image_queue, vrp) {
	this->maximum_wait_motion = vrp->getMaximumWaitMotion();

	// std::cout<<"construct VideoMotionRecorder"<<std::endl;
}

VideoMotionRecorder::~VideoMotionRecorder() {
	// std::cout<<"destroy VideoMotionRecorder"<<std::endl;
}

void VideoMotionRecorder::start(){
	this->startRecord();
}

void VideoMotionRecorder::startRecord() {

	cv::Mat frame;
	boost::posix_time::ptime current_time, start_time;

	while (running) {
		start_time = boost::posix_time::microsec_clock::local_time();

		if (input_image_queue.empty()) {
			usleep(1000);

			if(writer){
				current_time = boost::posix_time::microsec_clock::local_time();
				boost::posix_time::time_duration td = current_time - start_time;
				//std::cout<<"current_time: "<<current_time<<std::endl;
				if((unsigned int)td.seconds() > this->maximum_wait_motion){
					stopTimer();
					delete writer;
					// std::cout<<"stop timer: "<<td<<std::endl;
				}
			}

			continue;
		}
		else{
			if(!writer){
				getNewVideoWriter();
				startTimer();
			}
		}

		frame = input_image_queue.pop();

		writer_mutex.lock();
		//std::cout<<"write to: "<<filename<<std::endl;
		*writer << frame;
		writer_mutex.unlock();

	}

}

} /* namespace nokkhum */
