/*
 * notification.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: superizer
 */

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "../../command_interface/program_reporter.hpp"

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

#include "notification.hpp"

namespace nokkhum {
Notification::Notification(ImageQueue &input_image_queue,
		NotificationAttribute &nfp, std::string camera_id) :
		ImageProcessor("Notification", input_image_queue), camera_id(camera_id) {
	this->name = nfp.getName();
}

Notification::~Notification() {

}

void Notification::start() {
	//std::cout << "notification start" << std::endl;
	cv::Mat frame;
	nokkhum::Image image;
	std::string name, type;
	std::string area;
	//bool check = 0;
	while (running) {
		//std::chrono::time_point < std::chrono::system_clock > now;
		//now = std::chrono::system_clock::now();
		//auto duration = now.time_since_epoch();
		//auto micro = std::chrono::duration_cast < std::chrono::microseconds
		//		> (duration).count();
		//std::time_t time = std::chrono::system_clock::to_time_t(now);
		//struct tm* tm = localtime(&time);

		//int last_min = tm->tm_min;
		//std::cout << std::to_string(tm->tm_min) << std::endl;
		//		std::cout<<"wait to save image"<<std::endl;

		if (input_image_queue.empty()) {
			std::this_thread::sleep_for(std::chrono::microseconds(1000));
			//std::cout<<"sleep img"<<std::endl;
			continue;
		}
		//if(input_image_queue.size() != 0)
		//	std::cout << "input image queue not empty :P" << std::endl;

		image = input_image_queue.pop();
		frame = image.get();
		Json::Value message = image.getDescription();

		if (message.isMember("face_name")) {
			name = message["face_name"].asString();
			type = "face_detected";
		}else if(message.isMember("motion_area")){
			std::cout << "Hello motion area !" << std::endl;
			area = message["motion_area"].asString();
			type = "motion_detected";
		}

//		if(tm->tm_min % 5 == 0 && !check){

		if (type == "warning")
			this->warning();
		else if (type == "face_detected") {
			std::string filename;
			std::chrono::time_point < std::chrono::system_clock > date;
			char buffer[100];
			struct tm * timeinfo;
			date = image.getDate();
			std::ostringstream oss;
			std::time_t tt = std::chrono::system_clock::to_time_t(date);
			timeinfo = localtime(&tt);
			strftime(buffer, 80, "%F-%H-%M-%S", timeinfo);
			oss <<  buffer << "-" << std::setw(6)
					<< std::setfill('0') << std::chrono::duration_cast
					< std::chrono::nanoseconds
					> (date.time_since_epoch()).count() % 1000000 << "-" << name
							<< ".png";
			filename = oss.str();
			this->face_detected(name, filename);
		}else if(type == "motion_detected"){
			this->motion_detected(area);
		}
//			check = 1;
//		} else if(tm->tm_min % 5 != 0){
//			check = 0;
//		}
	}
}
void Notification::warning() {
	Json::Value message;
	message["method"] = "notify";
	message["camera_id"] = this->camera_id;
	message["description"] = this->description;

	boost::posix_time::ptime current_time =
			boost::posix_time::microsec_clock::local_time();
	message["date"] = boost::posix_time::to_iso_extended_string(current_time);
	nokkhum::ProgramReporter().report(message);
}

void Notification::face_detected(std::string name, std::string filename) {
	Json::Value message;
	message["method"] = "face_detected";
	message["camera_id"] = this->camera_id;
	message["description"] = this->description;
	message["filename"] = filename;
	message["face_name"] = name;

	boost::posix_time::ptime current_time =
			boost::posix_time::microsec_clock::local_time();
	message["date"] = boost::posix_time::to_iso_extended_string(current_time);
	nokkhum::ProgramReporter().report(message);
}

void Notification::motion_detected(std::string area){
	Json::Value message;
	message["method"] = "motion_detected";
	message["camera_id"] = this->camera_id;
	message["description"] = this->description;
	message["area"] = area;

	boost::posix_time::ptime current_time =
				boost::posix_time::microsec_clock::local_time();
		message["date"] = boost::posix_time::to_iso_extended_string(current_time);
		nokkhum::ProgramReporter().report(message);
}

} /* namespace nokkhum */

