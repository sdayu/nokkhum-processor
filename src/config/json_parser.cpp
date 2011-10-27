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

//#include <glog/logging.h>

#include "../camera/cv_ip_camera.hpp"

#include "../surveillance/processor/face_detector.hpp"
#include "../surveillance/processor/motion_detector.hpp"
#include "../surveillance/processor/image_recorder.hpp"
#include "../surveillance/processor/video_recorder.hpp"


#include "camera_property.hpp"
#include "face_detector_property.hpp"
#include "motion_detector_property.hpp"
#include "recorder_property.hpp"
#include "image_processor_property.hpp"
#include "video_recorder_property.hpp"
#include "image_recorder_property.hpp"

namespace nokkhum {

JsonParser::JsonParser() {
}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

PropertyMap* JsonParser::parse(std::string json) {

	json_spirit::mValue value;
	json_spirit::read(json, value);

//	std::cout
//			<< "JSON string: "
//			<< std::endl
//			<< json_spirit::write(value,
//					json_spirit::pretty_print | json_spirit::raw_utf8)
//			<< std::endl;

	json_spirit::mObject obj = value.get_obj();

	PropertyMap *property_map = new PropertyMap();
	Property *property = nullptr;

//	LOG(DEBUG) << "JSON :" << json;
//	LOG(DEBUG) << "parse camera :" << json_spirit::write(value);
	property = this->parseCamera(obj["camera"].get_obj());
//	LOG(DEBUG) << "end parse camera";
	  // first insert function version (single parameter):
	(*property_map)["camera"] = property;
//	LOG(DEBUG) << "parse processor";
	ImageProcessorProperty* ipp = new ImageProcessorProperty();

	this->parseImageProcessor( obj["processors"].get_array(), ipp);
	(*property_map)["processors"] = ipp;

//	std::cout << std::endl << "---------- end ----------" << std::endl;
//	LOG(INFO) << "success";
	return property_map;
}

CameraProperty* JsonParser::parseCamera(const json_spirit::mObject camera_obj) {
//	LOG(INFO) << "parse camera 0.0";
	int width = 0;
	int height = 0;
	int fps = 0;
	std::string url;
	std::string name;
	std::string model;
	std::string username;
	std::string password;
//	LOG(INFO) << "parse camera 0";
	width = this->findValue(camera_obj, "width").get_int();
	height = this->findValue(camera_obj, "height").get_int();
	fps = this->findValue(camera_obj, "fps").get_int();
	url = this->findValue(camera_obj, "url").get_str();
	name = this->findValue(camera_obj, "name").get_str();
	model = this->findValue(camera_obj, "model").get_str();
	username = this->findValue(camera_obj, "username").get_str();
	password = this->findValue(camera_obj, "password").get_str();

//	std::cout << "Camera Name: " << name << std::endl;

	CameraProperty *cp = new CameraProperty(name, model, url, width, height, fps, username, password);
	return cp;
}


void JsonParser::parseImageProcessor(
		const json_spirit::mArray image_processor_array,
		ImageProcessorProperty* ipp) {

	ImageProcessorProperty* tmp = nullptr;

	for (json_spirit::mArray::size_type i = 0; i < image_processor_array.size();
			i++) {
		json_spirit::mObject obj = image_processor_array[i].get_obj();

		std::string processor_name = this->findValue(obj, "name").get_str();
//		std::cout << "Processor " << i << " name : "
//				<< this->findValue(obj, "name").get_str() << std::endl;

		if (processor_name == "Motion Detector") {
			tmp = parseMotionDetector(obj);
		} else if (processor_name == "Face Detector") {
			tmp = parseFaceDetector(obj);
		} else if (processor_name == "Video Recorder") {
			tmp = parseVideoRecorder(obj);
		} else if (processor_name == "Image Recorder") {
			tmp = parseImageRecorder(obj);
		}

		ipp->addImageProcessorProperty(tmp);

	}

	//return image_processors;
}

ImageProcessorProperty* JsonParser::parseVideoRecorder(
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

	//std::cout << "Processor name : " << name << std::endl;

	VideoRecorderProperty* vrp = nullptr;

	if(this->findKey(image_processor_obj, "record_motion") && this->findKey(image_processor_obj, "maximum_wait_motion")){
		bool record_motion = this->findValue(image_processor_obj, "record_motion").get_bool();
		int maximum_wait_motion = this->findValue(image_processor_obj, "maximum_wait_motion").get_int();
		name = "Video Motion Recorder";

		if(record_motion){
			vrp = new VideoRecorderProperty(name, directory, width, height, fps, record_motion, maximum_wait_motion);
		}
		else{
			vrp = new VideoRecorderProperty(name, directory, width, height, fps);
		}
	}
	else{
		vrp = new VideoRecorderProperty(name, directory, width, height, fps);
	}

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array(), vrp );
	}

	return vrp;
}

ImageProcessorProperty* JsonParser::parseImageRecorder(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	std::string directory;
	int width;
	int height;

	name = this->findValue(image_processor_obj, "name").get_str();
	directory = this->findValue(image_processor_obj, "directory").get_str();
	width = this->findValue(image_processor_obj, "width").get_int();
	height = this->findValue(image_processor_obj, "height").get_int();

	// std::cout << "Processor name : " << name << std::endl;

	ImageRecorderProperty *irp = new ImageRecorderProperty(name, directory, width, height);
	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array(), irp );
	}

	return irp;
}

ImageProcessorProperty* JsonParser::parseMotionDetector(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	int interval = 0;
	int resolution = 100;

	name = this->findValue(image_processor_obj, "name").get_str();
	interval = this->findValue(image_processor_obj, "interval").get_int();
	resolution = this->findValue(image_processor_obj, "resolution").get_int();

	// std::cout << "Processor name : " << name << std::endl;

	MotionDetectorProperty* mdp = new MotionDetectorProperty(name, resolution, interval);
	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array(), mdp );
	}

	return mdp;
}

ImageProcessorProperty* JsonParser::parseFaceDetector(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	int interval = 0;

	name = this->findValue(image_processor_obj, "name").get_str();
	interval = this->findValue(image_processor_obj, "interval").get_int();

	// std::cout << "Processor name : " << name << std::endl;

	FaceDetectorProperty* fdp = new FaceDetectorProperty(name, interval);
	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array(), fdp );
	}

	return fdp;
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
