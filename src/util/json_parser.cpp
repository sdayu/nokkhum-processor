/*
 * json-parser.cpp
 *
 *  Created on: Jul 5, 2011
 *      Author: boatkrap
 */

#include "json_parser.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <typeinfo>
#include <json_spirit.h>

namespace nokkhum {

JsonParser::JsonParser() {
	// TODO Auto-generated constructor stub

	camera_schema["name"] = "string";
	camera_schema["model"] = "string";
	camera_schema["url"] = "string";
	camera_schema["fps"] = "int";
	camera_schema["width"] = "width";
	camera_schema["hight"] = "hight";
}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

void JsonParser::parse(std::string file_name) {

	std::ifstream ifs(file_name.c_str(), std::ios::in);

	if (!ifs) {
		std::cerr << "file error: " << file_name << std::endl;
		return;
	}

	json_spirit::Value value;
	std::cout << "Read JSON string: " << json_spirit::read(ifs, value)
			<< std::endl;

	std::cout
			<< "JSON string: "
			<< std::endl
			<< json_spirit::write(value,
					json_spirit::pretty_print | json_spirit::raw_utf8)
			<< std::endl;

	json_spirit::Object obj = value.get_obj();

	for (int i = 0; i < obj.size(); i++) {
		json_spirit::Pair pair = obj[i];
		json_spirit::Value val = pair.value_;
		std::cout << "Key: " << pair.name_ << std::endl;
		if (pair.name_ == "camera") {
			std::cout << "yes is camera" << std::endl;
			json_spirit::Object cameraObj = val.get_obj();
			for (int j = 0; j < cameraObj.size(); j++) {
				json_spirit::Pair pairCamera = cameraObj[j];
				std::cout << " -> Key: " << pairCamera.name_;
				if (pairCamera.name_ == "name") {
					parseValue(pairCamera.value_, camera_schema[pairCamera.name_]);
					//std::cout << " Value: " << parseValue(pairCamera.value_, camera_schema[pairCamera.name_]);

				}
				std::cout << std::endl;
			}
		}
	}
}

void JsonParser::parseValue(json_spirit::Value allocator, std::string type) {

}

} /* namespace nokkhum */
