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

#include "../surveillance/video_surveillance.hpp"
#include "../command_interface/command_parser.hpp"

namespace nokkhum {

SurveillanceManager::SurveillanceManager(std::string name) :
		name(name) {
	this->conf = nullptr;
}

SurveillanceManager::~SurveillanceManager() {
	//std::cout << "Terminate SurveillanceManager" << conf->getCameraProperty()->getName() << std::endl;
	LOG(INFO) << "Terminate SurveillanceManager name: " << this->name;
	delete vs;
	vs = nullptr;
	delete conf;
	conf = nullptr;
}

void SurveillanceManager::processCommand() {
	std::string command_string;
	json_spirit::Object result_json;
	nokkhum::CommandParser cp;
	while (true) {

		json_spirit::Object result_json;

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
				result_json.push_back(json_spirit::Pair("result", "can not process command"));
				std::cout << json_spirit::write(result_json) << std::endl;
				LOG(INFO) << json_spirit::write(result_json);
				continue;
			}
		} catch (std::exception e) {
			LOG(ERROR) << "camera id: " << this->name
					<< " get command error " << e.what();
			continue;
		}

		if (cp.getCommand() == "stop") {
			this->stopSurveillanceApplication();
			result_json.push_back(json_spirit::Pair("result", "stop ok"));
			std::cout << json_spirit::write(result_json) << std::endl;
			LOG(INFO) << json_spirit::write(result_json);
			break;
		} else if (cp.getCommand() == "start") {
			try {
				this->startSurveillanceApplication(cp.getCameraAttribute());
			} catch (std::exception e) {
				result_json.push_back(json_spirit::Pair("result", e.what()));
				LOG(ERROR) << e.what();
				result_json.push_back(json_spirit::Pair("result", "stop because cannot start capture or configuration wrong"));
				std::cout << json_spirit::write(result_json) << std::endl;
				LOG(INFO) << json_spirit::write(result_json);
				break;
			}
			result_json.push_back(json_spirit::Pair("result", "start ok"));
			std::cout << json_spirit::write(result_json) << std::endl;
			LOG(INFO) << json_spirit::write(result_json);
		} else if (cp.getCommand() == "get_attributes") {
			result_json.push_back(json_spirit::Pair("result", this->conf->getAttributes()));
			std::cout << json_spirit::write(result_json) << std::endl;
			LOG(INFO) << json_spirit::write(result_json);
		} else if (cp.getCommand() == "get_name") {
			result_json.push_back(json_spirit::Pair("result", this->name));
			std::cout << json_spirit::write(result_json) << std::endl;
			LOG(INFO) << json_spirit::write(result_json);
		}

	}
}

void SurveillanceManager::startSurveillanceApplication(std::string config) {

	if (conf) {
		LOG(INFO) << "Try to start but ignore command";
		return;
	}

	LOG(INFO) << "Start build configuration for camera id: " << this->name;
	conf = new nokkhum::Configuration(config);

	LOG(INFO) << "Start construct VideoSurveillance for camera id: "
			<< this->name;
	// need to check configuration is available
	vs = new nokkhum::VideoSurveillance(*conf);
	vs->start();
	LOG(INFO) << "SurveillanceManager start: " << this->name;
}

void SurveillanceManager::stopSurveillanceApplication() {
	if (vs)
		vs->stop();
}

} /* namespace nokkhum */
