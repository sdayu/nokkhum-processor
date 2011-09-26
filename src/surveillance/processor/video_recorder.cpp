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

	this->period = 10;

	std::cout << "Construct video recorder without property" << std::endl;
}

VideoRecorder::VideoRecorder(CvMatQueue & input_image_queue,
		VideoRecorderProperty *vrp) :
		ImageProcessor(vrp->getName(), input_image_queue) {
	this->running = false;
	this->directory = vrp->getDirectory();
	this->width = vrp->getWidth();
	this->height = vrp->getHeight();
	this->fps = vrp->getFps();
	this->period = 10;
	this->writer = nullptr;

	this->getNewVideoWriter();

}

VideoRecorder::~VideoRecorder() {

	delete this->writer;
	this->writer = nullptr;

//	std::cerr << "Terminate record tread" << std::endl;
}

void VideoRecorder::start() {
	this->startTimer();
	this->startRecord();
}

void VideoRecorder::stop() {
	Job::stop();
	this->stopTimer();
}

void VideoRecorder::getNewVideoWriter() {

	std::ostringstream oss;
	time_t rawtime;
	time(&rawtime);
//	std::cout << "get new writer time: " <<ctime(&rawtime)<< std::endl;
	timeval tv;
	gettimeofday(&tv, NULL);

	tm* time_struct = localtime(&rawtime);
	oss << time_struct->tm_year + 1900 << "-" << std::setw(2)
			<< std::setfill('0') << time_struct->tm_mon + 1 << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_mday << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_hour << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_min << "-"
			<< std::setw(2) << std::setfill('0') << time_struct->tm_sec << "-"
			<< std::setw(6) << std::setfill('0') << tv.tv_usec << ".avi";

	writer_mutex.lock();
	delete this->writer;
	this->writer = nullptr;

	this->writer = new CvVideoWriter(oss.str(), this->directory, this->width,
			this->height, this->fps);
	writer_mutex.unlock();

	this->filename = oss.str();
}

void VideoRecorder::startRecord() {

	cv::Mat frame;
	//	cv::namedWindow("video", 1);

	//	std::cout << "Start record tread/running status: " << runnin//	time_t rawtime;

	//	std::cout<<"runing: "<<this->running<<std::endl;

	//	time(&rawtime);
	//	std::cout<<"start join timer:"<<ctime(&rawtime)<<std::endl;
		//this->timer.join();
	//	time(&rawtime);
	//	std::cout<<"start end join timer:"<<ctime(&rawtime)<<std::endl;g << " this-> "
	//			<< this << std::endl;

	while (running) {

		if (input_image_queue.empty()) {
			//			std::cout << "sleep .zZ" << std::endl;
			usleep(1000);
			continue;
		}
//		std::cout << "write to file " << this->filename << std::endl;

		frame = input_image_queue.pop();

		//		cv::imshow("video", frame);
		writer_mutex.lock();
		*writer << frame;
		writer_mutex.unlock();

		//		if (cv::waitKey(30) >= 0)
		//			break;
	}
//	std::cout<<"record stop"<<std::endl;
}

void VideoRecorder::startTimer() {
	timer = std::thread(&VideoRecorder::clock, this);
}

void VideoRecorder::stopTimer() {
	try {
		this->timer.detach();
	} catch (std::exception e) {
		//std::cout<<"exception:  !!!!"<<e.what()<<std::endl;
	}
}
void VideoRecorder::clock() {

//	std::cout<<"This in clock: "<<this<<std::endl;
//	int counter = 0;
	while (running) {
		time_t rawtime;
		time(&rawtime);

		tm* begin_time = localtime(&rawtime);
		int minute = begin_time->tm_min;
		// std::cout << "current time start: " << ctime(&rawtime) << " count: " << counter << std::endl;
		if (minute % this->period == 0) {
//			std::cout << " minute: " << minute << std::endl;
			this->getNewVideoWriter();
		}
		time(&rawtime);
		tm* current_time = localtime(&rawtime);
		// std::cout << "current time: " << ctime(&rawtime) << " count: " << counter++ << std::endl;
		int sleep_time = (this->period
				- ((this->period + current_time->tm_min) % this->period)) * 60;
		sleep_time = sleep_time - current_time->tm_sec;

		// std::cout << "sleep ---> " << sleep_time << std::endl;
		sleep(sleep_time);

	}
}

}
