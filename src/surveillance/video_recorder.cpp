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
		std::queue<cv::Mat>& image_queue) :
		writer(writer), image_queue(image_queue){

	this->running = false;
}

VideoRecorder::~VideoRecorder() {
	// TODO Auto-generated destructor stub
}

void VideoRecorder::start() {
	cv::Mat frame;
//	cv::namedWindow("video",1);

	this->running = true;

	while (this->running) {
		if(image_queue.empty()){
			usleep(100);
			continue;
		}
		frame = image_queue.front();
		image_queue.pop();
//		cv::imshow("video", frame);
		writer << frame;

//		if(cv::waitKey(30) >= 0) break;
	}

}
void VideoRecorder::stop() {
	this->running = false;
}

void VideoRecorder::operator()() {
	this->start();
}

}
