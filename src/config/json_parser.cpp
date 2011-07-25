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


#include "camera_property.hpp"
#include "face_detector_property.hpp"
#include "motion_detector_property.hpp"
#include "recorder_property.hpp"
#include "image_processor_property.hpp"

namespace nokkhum {

JsonParser::JsonParser() {
}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

PropertyMap& JsonParser::parse(std::string json) {

	json_spirit::mValue value;
	std::cout << "Read JSON string: " << json_spirit::read(json, value)
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
//	camera->setModel(model);    void setCameraProperty(CameraProperty *camera_property);
//	return camera;
}

ImageProcessorProperty* JsonParser::parseImageProcessor(
		const json_spirit::mArray image_processor_array) {
//	std::cout << std::endl
//			<< "obj: "
//			<< std::endl
//			<< json_spirit::write(image_processor_array,
//					json_spirit::pretty_print | json_spirit::raw_utf8)
//			<< std::endl;

	std::vector<ImageProcessorProperty*> image_processors;
	ImageProcessorProperty* tmp = nullptr;

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

	std::cout << "Processor name : " << name << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
	}

	//VideoRecorder* video_recorder = new VideoRecorder();
	//return video_recorder;

	VideoRecorderProperty* vrp = new VideoRecorderProperty(name, directory, width, height, fps);

	return nullptr;
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

	std::cout << "Processor name : " << name << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
	}

//	ImageRecorder* image_recorder = new ImageRecorder();
//	return image_recorder;



	return nullptr;
}

ImageProcessorProperty* JsonParser::parseMotionDetector(
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

	MotionDetectorProperty* mdp = new MotionDetectorProperty(name, resolution, interval);

	return mdp;
}

ImageProcessorProperty* JsonParser::parseFaceDetector(
		const json_spirit::mObject image_processor_obj) {

	std::string name;
	int interval = 0;

	name = this->findValue(image_processor_obj, "name").get_str();
	interval = this->findValue(image_processor_obj, "interval").get_int();

	std::cout << "Processor name : " << name << std::endl;

	if (this->findKey(image_processor_obj, "processors")){
		this->parseImageProcessor( this->findValue(image_processor_obj, "processors").get_array() );
	}

	FaceDetectorProperty* fdp = new FaceDetectorProperty(name, interval);
	//FaceDetection* face_detection = new FaceDetection();
	//return face_detection;

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
