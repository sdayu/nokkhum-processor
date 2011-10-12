//============================================================================
// Name        : main.cpp
// Author      : Thanathip Limna
// Version     :
// Copyright   :
// Description : Hello World in C++
//============================================================================

#include <glog/logging.h>

#include "surveillance/surveillance_manager.hpp"

int main(int argc, char** argv) {
	if(argc < 2)
		return -1;

	google::InitGoogleLogging("nokkhum-processor");
	LOG(INFO) << "Surveillance constructor ... " ;
	nokkhum::SurveillanceManager sm(argv[1]);

	sm.processCommand();

	sm.stopSurveillanceApplication();
	LOG(INFO) << "End Surveillance ... ";


    return 0;
}
