//============================================================================
// Name        : main.cpp
// Author      : Thanathip Limna
// Version     :
// Copyright   :
// Description : Hello World in C++
//============================================================================
#include <iostream>
#include <string>
#include <glog/logging.h>
#include <boost/filesystem.hpp>

#include "surveillance/surveillance_manager.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "arg miss match" << std::endl;
		return -1;
	}

	google::InitGoogleLogging(argv[0]);
	FLAGS_logbufsecs = 0;

	std::string p = "/tmp/nokkhum/processor";
	p = p + argv[1];

	if (!boost::filesystem::exists(p)) {

		if (boost::filesystem::create_directories(p)) {
			LOG(INFO) << "Create log name: " << p;
		}
	}
	FLAGS_log_dir = p.c_str();

	LOG(INFO) << "Surveillance constructor ... ";
	std::string attribute = argv[1];
	nokkhum::SurveillanceManager sm(attribute);

	LOG(INFO) << "Wait for command ... ";
	sm.processCommand();
	LOG(INFO) << "End command ... ";

//	sm.stopSurveillanceApplication();
	LOG(INFO) << "End Surveillance ... ";

	return 0;
}
