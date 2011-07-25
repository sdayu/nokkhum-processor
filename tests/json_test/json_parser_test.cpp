/*
 * JsonParserTest.cpp
 *
 *  Created on: Jul 7, 2011
 *      Author: boatkrap
 */

#include "json_parser_test.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "../../src/config/configuration.hpp"

namespace nokkhum {

JsonParserTest::JsonParserTest() {
	// TODO Auto-generated constructor stub

}

JsonParserTest::~JsonParserTest() {
	// TODO Auto-generated destructor stub
}

void JsonParserTest::testJsonParser() {
	std::cout << "Hello from json test" << std::endl;

	std::string file_name = "config/camera.json";
	std::ifstream ifs(file_name.c_str(), std::ios::in);

	if (!ifs) {
		std::cerr << "file error: " << file_name << std::endl;
		return;
	}
	std::ostringstream oss;
//	while (ifs) {
//		oss << ifs.readline();
//		std::cout << "The json :" << oss.str() << std::endl;
//	}
	oss << ifs.rdbuf();

	//std::cout << "The json :" << oss.str() << std::endl;
	nokkhum::Configuration(oss.str());

	ifs.close();
}

} /* namespace nokkhum */
