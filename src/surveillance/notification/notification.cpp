/*
 * notification.cpp
 *
 *  Created on: Jan 22, 2013
 *      Author: superizer
 */


#include <jsoncpp/json/writer.h>
#include <iostream>
//#include <command_interface/command_parser.hpp>
//#include <command_interface/command_parser.cpp>

#include "notification.hpp"

namespace nokkhum{
	Notification::Notification(ImageQueue &input_image_queue, int camera_id, std::string description) :
			  ImageProcessor( "Notification", input_image_queue), camera_id(camera_id), description(description){
		// TODO Auto-generated constructor stub
	}

	Notification::~Notification(){

	}

	void Notification::start(){

		if(!this->input_image_queue.empty()){
			//warn();
		}
	}
	/*void Notification::warn(){
			Json::Value event;
			event["notification"]["camera_id"] = this->camera_id;
			event["notification"]["description"] = this->description;
			std::cout << event << std::endl;
	}*/
} /* namespace nokkhum */




