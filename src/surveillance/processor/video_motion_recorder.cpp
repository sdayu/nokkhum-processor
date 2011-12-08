/*
 * video_record_motion.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: boatkrap
 */

#include "video_motion_recorder.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

#include <glog/logging.h>

namespace nokkhum {

VideoMotionRecorder::VideoMotionRecorder(CvMatQueue & input_image_queue,
		VideoRecorderAttribute *vrp) : VideoRecorder(input_image_queue, vrp) {
	this->maximum_wait_motion = vrp->getMaximumWaitMotion();

	// std::cout<<"construct VideoMotionRecorder"<<std::endl;
}

VideoMotionRecorder::~VideoMotionRecorder() {
	// std::cout<<"destroy VideoMotionRecorder"<<std::endl;
}

void VideoMotionRecorder::startRecord() {

	cv::Mat frame;
	boost::posix_time::ptime current_time, start_time;

	while (running) {

		start_time = boost::posix_time::microsec_clock::local_time();

		while(input_image_queue.empty()) {
			usleep(1000);

			// LOG(INFO)<<"Empty "<<std::endl;
			if(writer){
				current_time = boost::posix_time::microsec_clock::local_time();
				boost::posix_time::time_duration td = current_time - start_time;
				if((unsigned int)td.total_seconds() >= this->maximum_wait_motion){
					stopTimer();
					delete writer;
					writer = nullptr;
					LOG(INFO) << "stop timer: "<<td<<std::endl;
				}
			}

			continue;
		}

		if(!writer){
			LOG(INFO) << "Wait for start timer --> "<<input_image_queue.size()<<std::endl;
			this->getNewVideoWriter();
			startTimer();
			LOG(INFO) << "End Wait"<<std::endl;
		}

		frame = input_image_queue.pop();

		writer_mutex.lock();
		// LOG(INFO)<<"write to: "<<filename<<std::endl;
		*writer << frame;
		writer_mutex.unlock();

	}

}

} /* namespace nokkhum */
