/*
 * notification.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: superizer
 */

#include <jsoncpp/json/writer.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "../../command_interface/program_reporter.hpp"

#include "notification.hpp"

namespace nokkhum {
Notification::Notification(ImageQueue &input_image_queue,
		NotificationAttribute &nfp, std::string camera_id) :
		ImageProcessor("Notification", input_image_queue), camera_id(camera_id) {
	this->name = nfp.getName();
	this->type = nfp.getType();
}

Notification::~Notification() {

}

void Notification::start() {
	//std::cout << "notification start" << std::endl;
	cv::Mat frame;
	bool check = 0;
	while (running) {
		std::chrono::time_point < std::chrono::system_clock > now;
		now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto micro = std::chrono::duration_cast < std::chrono::microseconds
				> (duration).count();
		std::time_t time = std::chrono::system_clock::to_time_t(now);
		struct tm* tm = localtime(&time);

		//int last_min = tm->tm_min;
		//std::cout << std::to_string(tm->tm_min) << std::endl;
		//		std::cout<<"wait to save image"<<std::endl;

		if (input_image_queue.empty()) {
			std::this_thread::sleep_for(std::chrono::microseconds(1000));
			//std::cout<<"sleep img"<<std::endl;
			continue;
		}
		frame = input_image_queue.pop().get();
//		if(tm->tm_min % 5 == 0 && !check){
		if(type == "warning")
			this->warning();
		else if(type == "face_detected")
			this->face_detected();
//			check = 1;
//		} else if(tm->tm_min % 5 != 0){
//			check = 0;
//		}
	}
}
void Notification::warning() {
	Json::Value message;
	message["method"] 		= "notify";
	message["camera_id"] 	= this->camera_id;
	message["description"] 	= this->description;

	boost::posix_time::ptime current_time = boost::posix_time::microsec_clock::local_time();
	message["date"]			= boost::posix_time::to_iso_extended_string(current_time);
	nokkhum::ProgramReporter().report(message);
}

void Notification::face_detected() {
	Json::Value message;
	message["method"] 		= "face_detected";
	message["camera_id"] 	= this->camera_id;
	message["description"] 	= this->description;

	boost::posix_time::ptime current_time = boost::posix_time::microsec_clock::local_time();
	message["date"]			= boost::posix_time::to_iso_extended_string(current_time);
	nokkhum::ProgramReporter().report(message);
}

} /* namespace nokkhum */

