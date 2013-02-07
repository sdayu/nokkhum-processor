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

VideoMotionRecorder::VideoMotionRecorder(ImageQueue & input_image_queue,
		VideoRecorderAttribute &vrp) : VideoRecorder(input_image_queue, vrp) {

}

VideoMotionRecorder::~VideoMotionRecorder() {
	// std::cout<<"destroy VideoMotionRecorder"<<std::endl;
}

void VideoMotionRecorder::startRecord() {

	cv::Mat frame;
	nokkhum::Image image;
	//boost::posix_time::ptime current_time, start_time;

	while (running) {
		// LOG(INFO)<<"start "<<std::endl;

		//start_time = boost::posix_time::microsec_clock::local_time();

		while(input_image_queue.empty()) {
			std::this_thread::sleep_for( std::chrono::microseconds( 1000 ) );

			// LOG(INFO)<<"Empty "<<std::endl;
//			if(writer){
//				current_time = boost::posix_time::microsec_clock::local_time();
//				boost::posix_time::time_duration td = current_time - start_time;
//				if((unsigned int)td.total_seconds() >= this->maximum_wait_motion){
//					stopTimer();
//					stopRecord();
//					LOG(INFO) << "stop timer: "<<td<<std::endl;
//				}
//			}

			if(!running)
				return;
		}

		image = input_image_queue.pop();
		frame = image.get();

		if(!isWriterAvailable() or image.getMotionStatus() == nokkhum::MotionStatus::BeginMotion){
//			LOG(INFO) << "get new writer --> "<<input_image_queue.size()<<std::endl;
			this->getNewVideoWriter();
			startTimer();
		}
		// LOG(INFO)<<"write "<<std::endl;



		writer_mutex.lock();
		// LOG(INFO)<<"write to: "<<filename<<std::endl;
		*writer << frame;
		writer_mutex.unlock();
		// LOG(INFO)<<"end "<<std::endl;

		if(image.getMotionStatus() == nokkhum::MotionStatus::EndMotion){
			stopTimer();
			stopRecord();
//			LOG(INFO) << "stop timer: "<<td<<std::endl;
		}


	}

}

} /* namespace nokkhum */
