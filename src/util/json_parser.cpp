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

	json_spirit::mObject camera = obj["camera"].get_obj();

	//json_spirit::mObject camera = obj["camera"];

	//std::cout << "Value: " << obj["camera"]["name"]<< std::endl;

	for (unsigned int i = 0; i < obj.size(); i++) {

		//json_spirit::Pair pair = obj[i];
//		json_spirit::Value val = pair.value_;
//		std::cout << "Key: " << pair.name_ << std::endl;
//		if (pair.name_ == "camera") {
//			this->parse_camera(pair.value_);
//		}
	}
}

void JsonParser::parse_camera(json_spirit::Value value) {

	//const json_spirit::mObject cameraObj = value.get_obj();
	const json_spirit::mObject cameraObj;

	std::cout << "yes is camera size: "<< cameraObj.size() << std::endl;

	std::map<std::string, std::string> camera_property;

	int width = 0;
	int higth = 0;
	std::string url;
	std::string name;
	int fps = 0;



	std::ostringstream oss;
	name = this->find_value(cameraObj, "name").get_str();

//	for (unsigned int i = 0; i < cameraObj.size(); i++) {

//		name = this->find_value(cameraObj[i].get_obj(), "name").get_str();
//		json_spirit::Pair pairCamera = cameraObj[i];
//		std::cout << " -> Key: " << pairCamera.name_;
//
//
//
////		if ("width" == pairCamera.name_){
////			width = pairCamera.value_.get_int();
////		} else if ("hight" == pairCamera.name_){
////			higth = pairCamera.value_.get_int();
////		} else if ("fps" == pairCamera.name_){
////			fps = pairCamera.value_.get_int();
////		}
//
////		std::string type = camera_schema[pairCamera.name_];
////		if (type == "int") {
////			oss << pairCamera.value_.get_int();
////		} else if (type == "string") {
////			oss << pairCamera.value_.get_str();
////		} else if (type == "double") {
////			oss << pairCamera.value_.get_real();
////		} else if (type == "bool") {
////			oss << pairCamera.value_.get_bool();
////		}
////		camera_property[pairCamera.name_] = oss.str();
////		oss.str("");
////		std::cout << " Value: " << camera_property[pairCamera.name_];
//
//		std::cout << std::endl;
//	}

	CvIpCamera camera(320, 240, 10, "rtsp://172.30.143.249/play2.sdp");

}

const json_spirit::mValue& JsonParser::find_value( const json_spirit::mObject& obj, const std::string& name  )
{
	json_spirit::mObject::const_iterator i = obj.find( name );

assert( i != obj.end() );
	assert( i->first == name);

	return i->second;
}

} /* namespace nokkhum */
