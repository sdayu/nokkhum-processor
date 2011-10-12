/*
 * surveillance_manager.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: boatkrap
 */

#include "surveillance_manager.hpp"

#include <iostream>
#include <glog/logging.h>

#include "../surveillance/video_surveillance.hpp"
#include "../command_interface/command_parser.hpp"

namespace nokkhum {

SurveillanceManager::SurveillanceManager(std::string config) {

	conf = new nokkhum::Configuration(config);
	// need to check configuration is available
	vs = new nokkhum::VideoSurveillance(*conf);
	vs->start();
	LOG(INFO) << "SurveillanceManager start: " << conf->getCameraProperty()->getName();
}

SurveillanceManager::~SurveillanceManager() {
	//std::cout << "Terminate SurveillanceManager" << conf->getCameraProperty()->getName() << std::endl;
	LOG(INFO) << "Terminate SurveillanceManager name: " << conf->getCameraProperty()->getName();
	delete vs;
	vs = nullptr;
	delete conf;
	conf = nullptr;
}

void SurveillanceManager::processCommand() {
	std::string command_string;
	json_spirit::Object result_json;
	nokkhum::CommandParser cp;
	LOG(INFO) << "SurveillanceManager name: " << conf->getCameraProperty()->getName();
	while(true){
		std::cin >> command_string;
		cp.paseCommand(command_string);

		if(cp.getCommand() == "stop"){
			this->stopSurveillanceApplication();
			result_json.push_back( json_spirit::Pair( "result", "stop ok" ) );
			std::cout<<json_spirit::write(result_json)<<std::endl;
			break;
		}
		else if (cp.getCommand() == "start"){
			this->startSurveillanceApplication();
			result_json.push_back( json_spirit::Pair( "result", "start ok" ) );
			std::cout<<json_spirit::write(result_json)<<std::endl;
		}

		result_json.clear();
	}
}

void SurveillanceManager::startSurveillanceApplication() {
	vs->start();
}

void SurveillanceManager::stopSurveillanceApplication() {
	vs->stop();
}

} /* namespace nokkhum */
