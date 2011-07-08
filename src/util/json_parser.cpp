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
#include <sstream>
#include "../camera/cv_ip_camera.hpp"

namespace nokkhum {

JsonParser::JsonParser() {
	// TODO Auto-generated constructor stub

	camera_schema["name"] = "string";
	camera_schema["model"] = "string";
	camera_schema["url"] = "string";
	camera_schema["fps"] = "int";
	camera_schema["width"] = "int";
	camera_schema["hight"] = "int";

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

	json_spirit::mValue value;
	std::cout << "Read JSON string: " << json_spirit::read(ifs, value)
			<< std::endl;

	std::cout
			<< "JSON string: "
			<< std::endl
			<< json_spirit::write(value,
					json_spirit::pretty_print | json_spirit::raw_utf8)
			<< std::endl;

	json_spirit::mObject obj = value.get_obj();

	this->parseCamera(obj["camera"].get_obj());
	this->parseImageProcessor(obj["processors"].get_obj());

}

void JsonParser::parseCamera(const json_spirit::mObject camera_obj) {

	int width = 0;
	int height = 0;
	int fps = 0;
	std::string url;
	std::string name;
	std::string model;

	width = this->findValue(camera_obj, "width").get_int();
	height = this->findValue(camera_obj, "height").get_int();
	fps = this->findValue(camera_obj, "fps").get_int();
	url = this->findValue(camera_obj, "url").get_str();
	name = this->findValue(camera_obj, "name").get_str();
	model = this->findValue(camera_obj, "model").get_str();

//	CvIpCamera camera(width, height, fps, url);
//	camera.setName(name);
//	camera.setModel(model);

}

void JsonParser::parseImageProcessor(const json_spirit::mObject image_processor_obj) {

}

const json_spirit::mValue& JsonParser::findValue(
		const json_spirit::mObject& obj, const std::string& name) {
	json_spirit::mObject::const_iterator i = obj.find(name);

	return i->second;
}

} /* namespace nokkhum */
