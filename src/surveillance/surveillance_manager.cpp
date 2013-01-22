/*
 * surveillance_manager.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: boatkrap
 */

#include "surveillance_manager.hpp"

#include <iostream>
#include <exception>
#include <glog/logging.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include "../surveillance/video_surveillance.hpp"
#include "../command_interface/command_parser.hpp"

namespace nokkhum {

SurveillanceManager::SurveillanceManager(std::string name) :
		name(name) {
}

SurveillanceManager::~SurveillanceManager() {
	LOG(INFO) << "Terminate SurveillanceManager name: " << this->name;
}

void SurveillanceManager::processCommand() {
	std::string command_string;
	Json::Value result_json;
    Json::FastWriter writer;
	nokkhum::CommandParser cp;
	while (true) {

		Json::Value result_json;

		if (std::cin.eof()) {
			LOG(INFO) << "camera id: " << this->name
					<< " terminate because compute is unavailable ";
			this->stopSurveillanceApplication();
			break;
		}

		std::getline(std::cin, command_string);
		LOG(INFO) << "camera id: " << this->name << " get command -> "
				<< command_string;

		try {
			if (!cp.paseCommand(command_string)){
				result_json["result"]="can not process command";
				std::cout << writer.write(result_json);
				LOG(INFO) << writer.write(result_json);
				continue;
			}/*else{
				std::cout << "camera id : " << cp.getCameraId() << std::endl;
			}*/
		} catch (std::exception e) {
			LOG(ERROR) << "camera id: " << this->name
					<< " get command error " << e.what();
			continue;
		}

		if (cp.getCommand() == "stop") {
			this->stopSurveillanceApplication();
			result_json["result"]="stop ok";
			std::cout << writer.write(result_json);
			LOG(INFO) << writer.write(result_json);
			break;
		} else if (cp.getCommand() == "start") {

			try {
				this->startSurveillanceApplication(cp.getCameraAttribute());
			} catch (std::exception &e) {
				LOG(ERROR) << e.what();
				result_json["result"]=e.what();
				result_json["result"] = result_json["result"].asString() + "\nstop because cannot start capture or configuration wrong";
				std::cout << writer.write(result_json);
				LOG(INFO) << writer.write(result_json);
				break;
			}
			result_json["result"]="start ok";
			std::cout << writer.write(result_json);
			LOG(INFO) << writer.write(result_json);
		} else if (cp.getCommand() == "get_attributes") {
			result_json["result"]=this->conf.getAttributes();
			std::cout << writer.write(result_json);
			LOG(INFO) << writer.write(result_json);
		} else if (cp.getCommand() == "get_name") {
			result_json["result"]=this->name;
			std::cout << writer.write(result_json);
			LOG(INFO) << writer.write(result_json);
		}

	}
}

void SurveillanceManager::startSurveillanceApplication(std::string config) {

	if (config.empty()) {
		LOG(INFO) << "Try to start but ignore command";
		return;
	}

	LOG(INFO) << "Start build configuration for camera id: " << this->name;
	conf = nokkhum::Configuration(config);

	LOG(INFO) << "Start construct VideoSurveillance for camera id: "
			<< this->name;
	// need to check configuration is available
	vs = nokkhum::VideoSurveillance(conf);
	vs.start();
	LOG(INFO) << "SurveillanceManager start: " << this->name;
}

void SurveillanceManager::stopSurveillanceApplication() {
	LOG(INFO) << "Try to stop VS";
	vs.stop();
	LOG(INFO) << "Stop, Bye";
}

} /* namespace nokkhum */
