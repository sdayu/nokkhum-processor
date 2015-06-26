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
#include "../surveillance/processor/face_recognition.hpp"
#include "../surveillance/processor/face_preprocess.hpp"
#include "../surveillance/processor/motion_detector.hpp"
#include "../surveillance/processor/image_recorder.hpp"
#include "../surveillance/processor/video_recorder.hpp"
#include "../surveillance/processor/multimedia_recorder.hpp"
#include "../surveillance/processor/motion_detector_background_sub.hpp"
#include "../surveillance/notification/notification.hpp"
#include "../surveillance/processor/none_processor.hpp"

#include "camera_attribute.hpp"
#include "face_recognition_attribute.hpp"
#include "face_preprocess_attribute.hpp"
#include "face_detector_attribute.hpp"
#include "motion_detector_attribute.hpp"
#include "recorder_attribute.hpp"
#include "image_processor_attribute.hpp"
#include "video_recorder_attribute.hpp"
#include "image_recorder_attribute.hpp"
#include "image_recorder_attribute.hpp"
#include "multimedia_recorder_attribute.hpp"
#include "notification_attribute.hpp"
#include "none_processor_attribute.hpp"

namespace nokkhum {

JsonParser::JsonParser() {
}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<AttributeMap> JsonParser::parse(std::string json) {

	Json::Value value;
	Json::Reader read;
	read.parse(json, value);
//	std::cout
//			<< "JSON string: "
//			<< std::endl
//			<< Json::write(value,
//					Json::pretty_print | json_spirit::raw_utf8)
//			<< std::endl;

	Json::Value obj = value;

	std::shared_ptr<AttributeMap> property_map =
			std::make_shared<AttributeMap>();
	std::shared_ptr<Attribute> property = nullptr;

//	LOG(DEBUG) << "JSON :" << json;
//	LOG(DEBUG) << "parse camera :" << Json::write(value);
	property = parseCamera(obj["cameras"]);
//	LOG(DEBUG) << "end parse camera";
	// first insert function version (single parameter):
	(*property_map)["camera"] = property;
//	LOG(DEBUG) << "parse processor";
	std::shared_ptr<ImageProcessorAttribute> ipp = std::make_shared<
			ImageProcessorAttribute>();

	parseImageProcessor(obj["image_processors"], ipp);
	(*property_map)["image_processors"] = ipp;

//	std::cout << std::endl << "---------- end ----------" << std::endl;
//	LOG(INFO) << "success";
	return property_map;
}

std::shared_ptr<CameraAttribute> JsonParser::parseCamera(
		const Json::Value camera_obj) {
//	LOG(INFO) << "parse camera 0.0";
	int width = 0;
	int height = 0;
	int fps = 0;
	std::string id = "";
	std::string video_uri;
	std::string audio_uri;
	std::string image_uri;
	std::string name;
	std::string model;
	std::string username;
	std::string password;
//	LOG(INFO) << "parse camera 0";

	// for 1st camera
	const Json::Value camera = camera_obj[0];

	width = camera["width"].asInt();
	height = camera["height"].asInt();
	fps = camera["fps"].asInt();
	id = camera["id"].asString();
	video_uri = camera["video_uri"].asString();
	audio_uri = camera["audio_uri"].asString();
	image_uri = camera["image_uri"].asString();
	name = camera["name"].asString();
	model = camera["model"].asString();
	username = camera["username"].asString();
	password = camera["password"].asString();

//	std::cout << "Camera Name: " << name << std::endl;

	std::shared_ptr<CameraAttribute> cp =
			std::make_shared < CameraAttribute
					> (name, model, video_uri, audio_uri, image_uri, width, height, fps, username, password, id);
	return cp;
}

void JsonParser::parseImageProcessor(const Json::Value image_processor_array,
		std::shared_ptr<ImageProcessorAttribute> ipp) {

	std::shared_ptr<ImageProcessorAttribute> tmp = nullptr;

	for (unsigned int i = 0; i < image_processor_array.size(); i++) {
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
		} else if (processor_name == "Notification") {
			tmp = parseNotification(obj);
		} else if (processor_name == "None Processor") {
			tmp = parseNotification(obj);
		} else if (processor_name == "Face Recognition") {
			tmp = parseFaceRecognition(obj);
		} else if (processor_name == "Face Preprocess") {
			tmp = parseFacePreprocess(obj);
		}

		ipp->addImageProcessorAttribute(tmp);

	}

	//return image_processors;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseVideoRecorder(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string directory;
	std::string extension = "ogv";
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

	if (image_processor_obj.isMember("extension")) {
		extension = image_processor_obj["extension"].asString();
	}

	if (image_processor_obj.isMember("record_motion")) {
		bool record_motion = image_processor_obj.isMember("record_motion");
		name = "Video Motion Recorder";

		if (record_motion) {
			vrp = std::make_shared < VideoRecorderAttribute
					> (name, directory, width, height, fps, extension, record_motion);
		} else {
			vrp = std::make_shared < VideoRecorderAttribute
					> (name, directory, width, height, fps, extension);
		}
	} else {
		vrp = std::make_shared < VideoRecorderAttribute
				> (name, directory, width, height, fps, extension);
	}

	if (image_processor_obj.isMember("image_processors")) {
		parseImageProcessor(image_processor_obj["image_processors"], vrp);
	}

	return vrp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseMultimediaRecorder(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string directory;
	std::string extension = "ogv";
	int fps;
	int width;
	int height;

	name = image_processor_obj["name"].asString();
	directory = image_processor_obj["directory"].asString();
	//url=image_processor_obj["url"].asString();
	fps = image_processor_obj["fps"].asInt();
	width = image_processor_obj["width"].asInt();
	height = image_processor_obj["height"].asInt();

	if (image_processor_obj.isMember("extension")) {
		extension = image_processor_obj["extension"].asString();
	}

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<MultimediaRecorderAttribute> mrp = nullptr;

	mrp = std::make_shared < MultimediaRecorderAttribute
			> (name, directory, width, height, fps, extension);

	if (image_processor_obj.isMember("image_processors")) {
		parseImageProcessor(image_processor_obj["image_processors"], mrp);
	}

	return mrp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseImageRecorder(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string directory;
	std::string extension = "png";
	int width;
	int height;
	unsigned int interval = 1;

	name = image_processor_obj["name"].asString();
	directory = image_processor_obj["directory"].asString();
	width = image_processor_obj["width"].asInt();
	height = image_processor_obj["height"].asInt();
	if (image_processor_obj.isMember("interval")) {
		interval = image_processor_obj["interval"].asInt();
	}

	if (image_processor_obj.isMember("extension")) {
		extension = image_processor_obj["extension"].asString();
	}

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<ImageProcessorAttribute> irp = std::make_shared
			< ImageRecorderAttribute
			> (name, directory, width, height, extension, interval);
	if (image_processor_obj.isMember("image_processors")) {
		parseImageProcessor(image_processor_obj["image_processors"], irp);
	}

	return irp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseMotionDetector(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string motion_analysis;
	int wait_motion_time;
	bool enable_area_of_interest;
	//point p1,p2;
	cv::Point p;
	std::vector<std::vector<cv::Point> > mul_point;
	std::vector<cv::Point> tmppoint;
	std::shared_ptr<ImageProcessorAttribute> mdp;
	std::vector<std::string> area_name;
	int interval = 1;
	double sensitive = 100;

	name = image_processor_obj["name"].asString();
	interval = image_processor_obj.get("interval", 1).asInt();
	wait_motion_time = image_processor_obj.get("wait_motion_time", 10).asInt();
	sensitive = image_processor_obj.get("sensitive", 100).asDouble();
	//motion_analysis = image_processor_obj["motion_analysis_method"].asString();
	if (image_processor_obj.isMember("motion_analysis_method")) {
		motion_analysis =
				image_processor_obj["motion_analysis_method"].asString();
	} else {
		motion_analysis = "Optical Flow";
	}

	if (image_processor_obj.isMember("region_of_interest")) {
		//std::cout << "Hello New ROI" << std::endl;
		enable_area_of_interest = true;

		Json::Value aoi = image_processor_obj["region_of_interest"];
		for (std::string name : aoi.getMemberNames()) {
			area_name.push_back(name);
			//std::cout << name << std::endl;
			Json::Value array = aoi[name];
			for (int j = 0; j < (int) array.size(); j++) {
				Json::Value ar = array[j];
				p.x = ar[0].asInt();
				p.y = ar[1].asInt();
				//std::cout << p.x << " " << p.y << std::endl;
				tmppoint.push_back(p);
			}
			mul_point.push_back(tmppoint);
			tmppoint.clear();
		}
		mdp =
				std::make_shared < MotionDetectorAttribute
						> (name, motion_analysis, sensitive, interval, wait_motion_time, enable_area_of_interest, mul_point, area_name);
	} else {
		// std::cout << "Processor name : " << name << std::endl;
		mdp =
				std::make_shared < MotionDetectorAttribute
						> (name, motion_analysis, sensitive, interval, wait_motion_time);
	}

	if (image_processor_obj.isMember("image_processors")) {
		parseImageProcessor(image_processor_obj["image_processors"], mdp);
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

	std::shared_ptr<ImageProcessorAttribute> fdp = std::make_shared
			< FaceDetectorAttribute > (name, interval);
	if (image_processor_obj.isMember("image_processors")) {
		parseImageProcessor(image_processor_obj["image_processors"], fdp);
	}

	return fdp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseFaceRecognition(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string face_database;
	int interval = 0;

	name = image_processor_obj["name"].asString();
	interval = image_processor_obj["interval"].asInt();
	face_database = image_processor_obj["face_database"].asString();

//	LOG(INFO) << "ImagePro :" << name;

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<ImageProcessorAttribute> frp = std::make_shared
			< FaceRecognitionAttribute > (name, face_database, interval);
	if (image_processor_obj.isMember("image_processors")) {
		parseImageProcessor(image_processor_obj["image_processors"], frp);
	}

	return frp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseFacePreprocess(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string face_database;
	int face_num;
	int face_id;
	int interval = 0;

	name = image_processor_obj["name"].asString();
	face_id = image_processor_obj["face_id"].asInt();
	face_num = image_processor_obj["face_num"].asInt();
	face_database = image_processor_obj["face_database"].asString();
	if (image_processor_obj.isMember("interval")) {
		interval = image_processor_obj["interval"].asInt();
	}
	//std::cout << face_id << " " << face_num << " " << face_database << std::endl;
//	LOG(INFO) << "ImagePro :" << name;

	//std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<ImageProcessorAttribute> fpp = std::make_shared
			< FacePreprocessAttribute
			> (name, face_database, face_id, face_num, interval);
	if (image_processor_obj.isMember("image_processors")) {
		parseImageProcessor(image_processor_obj["image_processors"], fpp);
	}
	return fpp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseNotification(
		const Json::Value image_processor_obj) {

	std::string name;
	std::string type;

	name = image_processor_obj["name"].asString();
	type = image_processor_obj["type"].asString();

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<NotificationAttribute> nfp = std::make_shared
			< NotificationAttribute > (name, type);

	return nfp;
}

std::shared_ptr<ImageProcessorAttribute> JsonParser::parseNoneProcessor(
		const Json::Value image_processor_obj) {

	std::string name;

	name = image_processor_obj["name"].asString();

	// std::cout << "Processor name : " << name << std::endl;

	std::shared_ptr<NoneProcessorAttribute> npa = std::make_shared
			< NoneProcessorAttribute > (name);

	return npa;
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
