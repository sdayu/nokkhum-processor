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
//#include <command_interface/command_parser.hpp>
//#include <command_interface/command_parser.cpp>

#include "notification.hpp"

namespace nokkhum{
	Notification::Notification(ImageQueue &input_image_queue, NotificationAttribute &nfp, int camera_id):
			ImageProcessor("Notification", input_image_queue), camera_id(camera_id) {
		this->name = nfp.getName();
	}

	Notification::~Notification(){

	}

	void Notification::start(){
		std::cout << "notification start" << std::endl;
		cv::Mat frame;

			while (running) {
		//		std::cout<<"wait to save image"<<std::endl;

				if (input_image_queue.empty()) {
					std::this_thread::sleep_for( std::chrono::microseconds( 1000 ) );
					//std::cout<<"sleep img"<<std::endl;
					continue;
				}
				frame = input_image_queue.pop().get();
				this->warning();
			}
	}
	void Notification::warning(){
			Json::Value event;
			Json::FastWriter writer;
			event["method"] = "notify";
			event["camera_id"] = this->camera_id;
			event["description"] = this->description;
			std::cout << writer.write(event);
	}
} /* namespace nokkhum */




