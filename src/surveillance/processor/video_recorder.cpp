/*
 * video_recorder.cpp
 *
 *  Created on: May 4, 2011
 *      Author: boatkrap
 */

#include "video_recorder.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

#include <exception>

#include <opencv2/highgui/highgui.hpp>
#include "../../video/cv_video_writer.hpp"

#include <sys/time.h>

namespace nokkhum {

VideoRecorder::VideoRecorder(CvMatQueue& input_image_queue) :
		ImageProcessor("VDO Recorder", input_image_queue) {
	this->running = false;
	this->writer = nullptr;

	std::cout << "Construct video recorder without property" << std::endl;
}

VideoRecorder::VideoRecorder(CvMatQueue & input_image_queue,
		VideoRecorderProperty *vrp) :
		ImageProcessor("VDO Recorder", input_image_queue) {
	this->running = false;

	std::ostringstream oss;
	time_t rawtime;
	time(&rawtime);

	timeval tv;
	gettimeofday(&tv, NULL);

	tm* time_struct = localtime(&rawtime);
	oss << time_struct->tm_year + 1900 << "-" << std::setw(2)
			<< std::setfill('0') << time_struct->tm_mon + 1 << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_mday << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_hour << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_min << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_sec << "-"
			<< std::setw(5) << std::setfill('0') << tv.tv_usec << ".avi";

	this->filename = oss.str();
	this->directory = vrp->getDirectory();
	this->width = vrp->getWidth();
	this->height = vrp->getHeight();
	this->fps = vrp->getFps();

	this->writer = new CvVideoWriter(oss.str(), vrp->getDirectory(),
			vrp->getWidth(), vrp->getHeight(), vrp->getFps());

}

VideoRecorder::~VideoRecorder() {

	delete this->writer;
	this->writer = nullptr;

//	std::cerr << "Terminate record tread" << std::endl;
}

void VideoRecorder::start() {

	cv::Mat frame;
//	cv::namedWindow("video", 1);

//	std::cout << "Start record tread/running status: " << running << " this-> "
//			<< this << std::endl;

	while (running) {
		if (input_image_queue.empty()) {
//			std::cout << "sleep .zZ" << std::endl;
			usleep(1000);
			continue;
		}
		std::cout << "write to file " << this->filename<< std::endl;

		frame = input_image_queue.pop();

//		cv::imshow("video", frame);
		*writer << frame;

//		if (cv::waitKey(30) >= 0)
//			break;
	}

}

}
