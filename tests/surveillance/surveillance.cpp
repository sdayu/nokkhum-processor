/*
 * surveillance.cpp
 *
 *  Created on: Aug 26, 2011
 *      Author: boatkrap
 */

#include "surveillance.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glog/logging.h>

#include "../../src/surveillance/surveillance_manager.hpp"

namespace nokkhum {

Surveillance::Surveillance() {
	google::InitGoogleLogging("nokkhum-processor-test");

}

Surveillance::~Surveillance() {
	// TODO Auto-generated destructor stub
}

void Surveillance::testSurveillance() {

	std::cout << "Hello from surveillance test" << std::endl; // prints Hello World, Hello Nukkhum

	std::string file_name = "config/camera.json";
	std::ifstream ifs(file_name.c_str(), std::ios::in);

	if (!ifs) {
		std::cerr << "file error: " << file_name << std::endl;
		return;
	}
	std::ostringstream oss;

	oss << ifs.rdbuf();
	std::cout << "Surveillance constructor ... " << std::endl;
	LOG(INFO) << "Surveillance constructor ... " ;
	SurveillanceManager sm(oss.str());
	ifs.close();

	std::cout << "sleep Surveillance" << std::endl;
	LOG(INFO) << "sleep Surveillance" ;
	sleep(60);

	std::cout << "Stop Surveillance ... " << std::endl;
	sm.stopSurveillanceApplication();
	std::cout << "End Surveillance ... " << std::endl;
	LOG(INFO) << "End Surveillance ... ";

}

} /* namespace nokkhum */
