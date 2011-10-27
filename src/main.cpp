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

#include "surveillance/surveillance_manager.hpp"

int main(int argc, char** argv) {
	if(argc < 2){
		std::cerr << "arg miss match" << std::endl;
		return -1;
	}


	google::InitGoogleLogging(argv[0]);
	FLAGS_logbufsecs = 0;

	LOG(INFO) << "argv[1]: " << argv[1] ;

	LOG(INFO) << "Surveillance constructor ... " ;
	std::string attribute = argv[1];
	nokkhum::SurveillanceManager sm(attribute);

	LOG(INFO) << "Wait for command ... " ;
	sm.processCommand();

	sm.stopSurveillanceApplication();
	LOG(INFO) << "End Surveillance ... ";


    return 0;
}
