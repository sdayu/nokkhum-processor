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
#include <vector>

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

	return nullptr;
//	CvIpCamera camera = new CvIpCamera(width, height, fps, url);
//	camera->setName(name);
//	camera->setModel(model);
//	return camera;
}

ImageProcessor* JsonParser::parseImageProcessor(
		const json_spirit::mArray image_processor_array) {
//	std::cout << std::endl
//			<< "obj: "
//			<< std::endl
//			<< json_spirit::write(image_processor_array,
//					json_spirit::pretty_print | json_spirit::raw_utf8)
//			<< std::endl;

	std::vector<ImageProcessor*> image_processors;
	ImageProcessor* tmp = nullptr;

	for (json_spirit::mArray::size_type i = 0; i < image_processor_array.size();
			i++) {
		json_spirit::mObject obj = image_processor_array[i].get_obj();

		std::string processor_name = this->findValue(obj, "name").get_str();
		std::cout << "Processor " << i << " name : "
				<< this->findValue(obj, "name").get_str() << std::endl;

		if (processor_name == "Motion Detector") {
			tmp = parseMotionDetector(obj);
		} else if (processor_name == "Face Detector") {
			tmp = parseFaceDetector(obj);
		} else if (processor_name == "Video Recorder") {
			tmp = parseVideoRecorder(obj);
		} else if (processor_name == "Image Recorder") {
			tmp = parseImageRecorder(obj);
		}

		image_processors.push_back(tmp);

	}

	return nullptr;
}

ImageProcessor* JsonParser::parseVideoRecorder(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	std::string directory;
	int fps;
	int width;
	int height;

	name = this->findValue(image_processor_obj, "name").get_str();
	directory = this->findValue(image_processor_obj, "directory").get_str();
	fps = this->findValue(image_processor_obj, "fps").get_int();
	width = this->findValue(image_processor_obj, "width").get_int();
	height = this->findValue(image_processor_obj, "height").get_int();

	std::cout << "Processor name : " << name << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
	}

	//VideoRecorder* video_recorder = new VideoRecorder();
	//return video_recorder;

	return nullptr;
}

ImageProcessor* JsonParser::parseImageRecorder(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	std::string directory;
	int width;
	int height;

	name = this->findValue(image_processor_obj, "name").get_str();
	directory = this->findValue(image_processor_obj, "directory").get_str();
	width = this->findValue(image_processor_obj, "width").get_int();
	height = this->findValue(image_processor_obj, "height").get_int();

	std::cout << "Processor name : " << name << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
	}

//	ImageRecorder* image_recorder = new ImageRecorder();
//	return image_recorder;

	return nullptr;
}

ImageProcessor* JsonParser::parseMotionDetector(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	int interval = 0;
	int resolution = 100;

	name = this->findValue(image_processor_obj, "name").get_str();
	interval = this->findValue(image_processor_obj, "interval").get_int();
	resolution = this->findValue(image_processor_obj, "resolution").get_int();

	std::cout << "Processor name : " << name << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
	}

//	MotionDetection* motion_detection = new MotionDetection();
//	return motion_detection;

	return nullptr;
}

ImageProcessor* JsonParser::parseFaceDetector(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	int interval = 0;

	name = this->findValue(image_processor_obj, "name").get_str();
	interval = this->findValue(image_processor_obj, "interval").get_int();

	std::cout << "Processor name : " << name << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
	}

	//FaceDetection* face_detection = new FaceDetection();
	//return face_detection;

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
