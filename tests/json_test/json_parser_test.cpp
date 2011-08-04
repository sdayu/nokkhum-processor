/*
 * JsonParserTest.cpp
 *
 *  Created on: Jul 7, 2011
 *      Author: boatkrap
 */

#include "json_parser_test.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

	oss << ifs.rdbuf();

	nokkhum::Configuration(oss.str());

	ifs.close();
}

} /* namespace nokkhum */
