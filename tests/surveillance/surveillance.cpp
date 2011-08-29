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

#include "../../src/surveillance/video_surveillance.hpp"

namespace nokkhum {

Surveillance::Surveillance() {
	// TODO Auto-generated constructor stub

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

	nokkhum::Configuration conf(oss.str());
	ifs.close();

	std::cout << "Surveillance constructor ... " << std::endl;
	nokkhum::VideoSurveillance vs(conf);

	std::cout << "Start Surveillance ... " << std::endl;
	vs.start();

	std::cout << "Stop Surveillance ... " << std::endl;
	vs.stop();
	std::cout << "End Surveillance ... " << std::endl;

}

} /* namespace nokkhum */
