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

#include "../surveillance/process/face_detection.hpp"
#include "../surveillance/process/motion_detection.hpp"
#include "../surveillance/process/image_recorder.hpp"
#include "../surveillance/process/video_recorder.hpp"

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

	this->parseImageProcessor(obj["processors"].get_array());

	std::cout << std::endl << "---------- end ----------" << std::endl;
}

Camera* JsonParser::parseCamera(const json_spirit::mObject camera_obj) {

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

	std::cout << "Camera Name: " << name << std::endl;
//	CvIpCamera camera(width, height, fps, url);
//	camera.setName(name);
//	camera.setModel(model);

	return nullptr;
}

ImageProcessor* JsonParser::parseImageProcessor(
		const json_spirit::mArray image_processor_array) {
//	std::cout << std::endl
//			<< "obj: "
//			<< std::endl
//			<< json_spirit::write(image_processor_array,
//					json_spirit::pretty_print | json_spirit::raw_utf8)
//			<< std::endl;
	for (json_spirit::mArray::size_type i = 0; i < image_processor_array.size();
			i++) {
		json_spirit::mObject obj = image_processor_array[i].get_obj();

		std::string processor_name = this->findValue(obj, "name").get_str();
		std::cout << "Processor " << i << " name : "
				<< this->findValue(obj, "name").get_str() << std::endl;

		if (processor_name == "Motion Detector") {
			parseMotionDetector(obj);
		} else if (processor_name == "Face Detector") {
			parseFaceDetector(obj);
		} else if (processor_name == "Video Recorder") {
			parseVideoRecorder(obj);
		} else if (processor_name == "Image Recorder") {
			parseImageRecorder(obj);
		}

	}
	return nullptr;
}

ImageProcessor* JsonParser::parseVideoRecorder(
		const json_spirit::mObject image_processor_obj) {

	std::cout << "Processor name : "
					<< this->findValue(image_processor_obj, "name").get_str() << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		std::cout<<"This is child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
		//std::cout<<"yes has processor: "<<this->findValue(image_processor_obj, "processors").get_array().size()<<std::endl;
		std::cout<<"End of child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
	}

	return nullptr;

}

ImageProcessor* JsonParser::parseImageRecorder(
		const json_spirit::mObject image_processor_obj) {

	std::cout << "Processor name : "
					<< this->findValue(image_processor_obj, "name").get_str() << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		std::cout<<"This is child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
		//std::cout<<"yes has processor: "<<this->findValue(image_processor_obj, "processors").get_array().size()<<std::endl;
		std::cout<<"End of child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
	}

	return nullptr;
}

ImageProcessor* JsonParser::parseMotionDetector(
		const json_spirit::mObject image_processor_obj) {

	std::cout << "Processor name : "
					<< this->findValue(image_processor_obj, "name").get_str() << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		std::cout<<"This is child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
		//std::cout<<"yes has processor: "<<this->findValue(image_processor_obj, "processors").get_array().size()<<std::endl;
		std::cout<<"End of child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
	}

	return nullptr;
}

ImageProcessor* JsonParser::parseFaceDetector(
		const json_spirit::mObject image_processor_obj) {

	std::cout << "Processor name : "
					<< this->findValue(image_processor_obj, "name").get_str() << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		std::cout<<"This is child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
		//std::cout<<"yes has processor: "<<this->findValue(image_processor_obj, "processors").get_array().size()<<std::endl;
		std::cout<<"End of child of processor: "<< this->findValue(image_processor_obj, "name").get_str() <<std::endl;
	}

	return nullptr;
}

const json_spirit::mValue& JsonParser::findValue(
		const json_spirit::mObject& obj, const std::string& name) {
	json_spirit::mObject::const_iterator i = obj.find(name);

	return i->second;
}

const bool JsonParser::findKey(const json_spirit::mObject& obj,
		const std::string& name) {
	bool is_key = false;

	json_spirit::mObject::const_iterator ci = obj.find(name);
	if (ci == obj.end())
		is_key = false;
	else
		is_key = true;

	return is_key;
}

} /* namespace nokkhum */
