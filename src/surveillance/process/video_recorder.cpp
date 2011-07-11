/*
 * video_recorder.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "video_recorder.hpp"

#include <iostream>
#include <opencv/highgui.h>

namespace nokkhum {

VideoRecorder::VideoRecorder(nokkhum::VideoWriter& writer,
		CvMatQueue& image_queue) :
		writer(writer), image_queue(image_queue){

	this->running = false;
}

VideoRecorder::~VideoRecorder() {
	std::cerr << "Terminate record tread" << std::endl;
}

void VideoRecorder::start() {

	std::cerr << "Start record tread" << std::endl;

	cv::Mat frame;
//	cv::namedWindow("video",1);

	this->running = true;

	while (this->running) {
		if(image_queue.empty()){
			// std::cout<<"sleep .zZ"<<std::endl;
			usleep(100);
			continue;
		}
		frame = image_queue.pop();
//		cv::imshow("video", frame);
		writer << frame;
//
//
//		if(cv::waitKey(30) >= 0) break;
	}

}

}
