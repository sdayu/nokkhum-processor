/*
 * json_parser.cpp
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
#include <jsoncpp/json/writer.h>
#include <sstream>
#include <vector>

//#include <glog/logging.h>

#include "../camera/cv_ip_camera.hpp"

#include "../surveillance/processor/face_detector.hpp"
#include "../surveillance/processor/motion_detector.hpp"
#include "../surveillance/processor/image_recorder.hpp"
#include "../surveillance/processor/video_recorder.hpp"
#include "../surveillance/processor/multimedia_recorder.hpp"
#include "../surveillance/processor/motion_detector_background_sub.hpp"


#include "camera_attribute.hpp"
#include "face_detector_attribute.hpp"
#include "motion_detector_attribute.hpp"
#include "recorder_attribute.hpp"
#include "image_processor_attribute.hpp"
#include "video_recorder_attribute.hpp"
#include "image_recorder_attribute.hpp"
#include "image_recorder_attribute.hpp"
#include "multimedia_recorder_attribute.hpp"

namespace nokkhum {

JsonParser::JsonParser() {
}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<AttributeMap> JsonParser::parse(std::string json) {

	Json::Value value;
    Json::Reader read;
    read.parse(json,value);
//	std::cout
//			<< "JSON string: "
//			<< std::endl
//			<< Json::write(value,
//					Json::pretty_print | json_spirit::raw_utf8)
//			<< std::endl;

	Json::Value obj = value;

	std::shared_ptr<AttributeMap> property_map = std::make_shared<AttributeMap>();
	std::shared_ptr<Attribute> property = nullptr;

//	LOG(DEBUG) << "JSON :" << json;
//	LOG(DEBUG) << "parse camera :" << Json::write(value);
	property = parseCamera(obj["camera"]);
//	LOG(DEBUG) << "end parse camera";
	  // first insert function version (single parameter):
	(*property_map)["camera"] = property;
//	LOG(DEBUG) << "parse processor";
	std::shared_ptr<ImageProcessorAttribute> ipp = std::make_shared<ImageProcessorAttribute>();

	parseImageProcessor( obj["processors"], ipp);
	(*property_map)["processors"] = ipp;

//	std::cout << std::endl << "---------- end ----------" << std::endl;
//	LOG(INFO) << "success";
	return property_map;
}

std::shared_ptr<CameraAttribute> JsonParser::parseCamera(const Json::Value camera_obj) {
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
	width = camera_obj["width"].asInt();
	height = camera_obj["height"].asInt();
	fps = camera_obj["fps"].asInt();
	url = camera_obj["url"].asString();
	name = camera_obj["name"].asString();
	model = camera_obj["model"].asString();
	username = camera_obj["username"].asString();
	password = camera_obj["password"].asString();

//	std::cout << "Camera Name: " << name << std::endl;

	std::shared_ptr<CameraAttribute> cp = std::make_shared<CameraAttribute>(name, model, url, width, height, fps, username, password);
	return cp;
}


void JsonParser::parseImageProcessor(
		const Json::Value image_processor_array,
		std::shared_ptr<ImageProcessorAttribute> ipp) {

	std::shared_ptr<ImageProcessorAttribute> tmp = nullptr;

	for (unsigned int i = 0; i < image_processor_array.size();
			i++) {
		Json::Value obj = image_processor_array[i];

		std::string processor_name = obj["name"].asString();
//		std::cout << "Processor " << i << " name : "
//				<< obj, "name").asString() << std::endl;

		if (processor_name == "Motion Detector") {
			tmp = parseMotionDetector(obj);
		} else if (processor_name == "Face Detector") {
			tmp = parseFaceDetector(obj);
		} else if (processor_name == "Video Recorder") {
			tmp = parseVideoRecorder(obj);
		} else if (processor_name == "Image Recorder") {
			tmp = parseImageRecorder(obj);
		} else if (processor_name == "Multimedia Recorder") {
			tmp = parseMultimediaRecorder(obj);
		}

		ipp->addImageProcessorAttribute(tmp);

	}

	//return image_processors;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseVideoRecorder(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string directory;
	int fps;
	int width;
	int height;

	name = image_processor_obj["name"].asString();
	directory = image_processor_obj["directory"].asString();
	fps = image_processor_obj["fps"].asInt();
	width = image_processor_obj["width"].asInt();
	height = image_processor_obj["height"].asInt();

	//std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<VideoRecorderAttribute> vrp = nullptr;

	if(image_processor_obj.isMember("record_motion") && image_processor_obj.isMember("maximum_wait_motion")){
		bool record_motion = image_processor_obj.isMember("record_motion");
		int maximum_wait_motion = image_processor_obj["maximum_wait_motion"].asInt();
		name = "Video Motion Recorder";

		if(record_motion){
			vrp = std::make_shared<VideoRecorderAttribute>(name, directory, width, height, fps, record_motion, maximum_wait_motion);
		}
		else{
			vrp = std::make_shared<VideoRecorderAttribute>(name, directory, width, height, fps);
		}
	}
	else{
		vrp = std::make_shared<VideoRecorderAttribute>(name, directory, width, height, fps);
	}

	if (image_processor_obj.isMember("processors")){
		parseImageProcessor( image_processor_obj["processors"], vrp );
	}

	return vrp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseMultimediaRecorder(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string directory;
	std::string url;
	int fps;
	int width;
	int height;

	name = image_processor_obj["name"].asString();
	directory = image_processor_obj["directory"].asString();
	url=image_processor_obj["url"].asString();
	fps = image_processor_obj["fps"].asInt();
	width = image_processor_obj["width"].asInt();
	height = image_processor_obj["height"].asInt();

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<MultimediaRecorderAttribute> mrp = nullptr;

	mrp = std::make_shared<MultimediaRecorderAttribute>(name, directory, url, width, height, fps);

	if (image_processor_obj.isMember("processors")){
		parseImageProcessor( image_processor_obj["processors"], mrp );
	}

	return mrp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseImageRecorder(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string directory;
	int width;
	int height;

	name = image_processor_obj["name"].asString();
	directory = image_processor_obj["directory"].asString();
	width = image_processor_obj["width"].asInt();
	height = image_processor_obj["height"].asInt();

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<ImageProcessorAttribute> irp = std::make_shared<ImageRecorderAttribute>(name, directory, width, height);
	if (image_processor_obj.isMember("processors")){
		parseImageProcessor( image_processor_obj["processors"], irp );
	}

	return irp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseMotionDetector(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string motion_analysis;
	bool enable_area_of_interest;
	point p1,p2;
	std::shared_ptr<ImageProcessorAttribute> mdp;
	int interval = 0;
	double sensitive = 100;

	name = image_processor_obj["name"].asString();
	interval = image_processor_obj["interval"].asInt();
	sensitive = image_processor_obj["sensitive"].asDouble();
	//motion_analysis = image_processor_obj["motion_analysis_method"].asString();
	if (image_processor_obj.isMember("motion_analysis_method")){
		motion_analysis = image_processor_obj["motion_analysis_method"].asString();
	}else{
		motion_analysis = "Optical Flow";
	}

	if (image_processor_obj.isMember("region_of_interest")){
			enable_area_of_interest = true;
			p1.x = image_processor_obj["region_of_interest"]["point1"]["x"].asInt();
			p1.y = image_processor_obj["region_of_interest"]["point1"]["y"].asInt();
			p2.x = image_processor_obj["region_of_interest"]["point2"]["x"].asInt();
			p2.y = image_processor_obj["region_of_interest"]["point2"]["y"].asInt();
			mdp = std::make_shared<MotionDetectorAttribute>(name, motion_analysis, sensitive, interval, enable_area_of_interest, p1, p2);
		}
	else{
	// std::cout << "Processor name : " << name << std::endl;
		mdp = std::make_shared<MotionDetectorAttribute>(name, motion_analysis, sensitive, interval);
	}

	if (image_processor_obj.isMember("processors")){
		parseImageProcessor( image_processor_obj["processors"], mdp );
	}

	return mdp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseFaceDetector(
		const Json::Value image_processor_obj) {

	std::string name;
	int interval = 0;

	name = image_processor_obj["name"].asString();
	interval = image_processor_obj["interval"].asInt();

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<ImageProcessorAttribute> fdp = std::make_shared<FaceDetectorAttribute>(name, interval);
	if (image_processor_obj.isMember("processors")){
		parseImageProcessor( image_processor_obj["processors"], fdp );
	}

	return fdp;
}

/*const Json::Value& JsonParser::
		const Json::Value& obj, const std::string& name) {
	Json::Value::const_iterator i = obj.find(name);

	return i->second;
}

const bool JsonParser::findKey(const Json::Value& obj,
		const std::string& name) {
	bool is_key = false;

	Json::Value::const_iterator ci = obj.find(name);
	if (ci == obj.end())
		is_key = false;
	else
		is_key = true;

	return is_key;
}*/

} /* namespace nokkhum */
