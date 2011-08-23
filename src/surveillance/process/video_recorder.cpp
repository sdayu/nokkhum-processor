/*
 * video_recorder.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "video_recorder.hpp"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "../../video/cv_video_writer.hpp"

namespace nokkhum {

VideoRecorder::VideoRecorder(CvMatQueue& input_image_queue) : ImageProcessor("VDO Recorder", input_image_queue), writer(writer) {

	this->running = false;
	this->writer = new CvVideoWriter();
}

VideoRecorder::~VideoRecorder() {
	std::cerr << "Terminate record tread" << std::endl;
}

void VideoRecorder::start() {

	std::cerr << "Start record tread" << std::endl;

	cv::Mat frame;
//	cv::namedWindow("video",1);

	while (running) {
		if(input_image_queue.empty()){
			// std::cout<<"sleep .zZ"<<std::endl;
			usleep(100);
			continue;
		}
		frame = input_image_queue.pop();
//		cv::imshow("video", frame);
		*writer << frame;
//
//
//		if(cv::waitKey(30) >= 0) break;
	}

}

}
