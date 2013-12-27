/*
 * video_surveillance.cpp
 *
 *  Created on: May 3, 2011
 *      Author: boatkrap
 */

#include "video_surveillance.hpp"

#include <ctime>

#include <iostream>
#include <thread>
#include <queue>
#include <string>
#include <sstream>
#include <iomanip>
using std::queue;
using std::string;

#include <glog/logging.h>

#include "acquisition/image_acquisition.hpp"
#include "processor/video_recorder.hpp"

#include "../camera/camera_factory.hpp"
#include "processor/image_processor_factory.hpp"

#include "../video/cv_video_writer.hpp"
#include "../util/multiple_image_queue.hpp"

#include "processor/motion_detector.hpp"
#include "processor/face_detector.hpp"
#include "processor/face_recognition.hpp"

namespace nokkhum {
VideoSurveillance::VideoSurveillance(){
	camera_attribute = nullptr;
	image_processor_attribute = nullptr;
	camera = nullptr;
	image_acquisition = nullptr;
}

VideoSurveillance::VideoSurveillance(Configuration &conf) :
		Job("Video Surveillance") {
	LOG(INFO) << "VideoSurveillance start constructor";

	camera_attribute = conf.getCameraAttribute();
	image_processor_attribute = conf.getImageProcessorAttribute();

	auto tmp_ipa = image_processor_attribute->getImageProcessorAttributeVector();

	// TODO: make easy check multimedia recorder is available, need complex processor check again
	is_multimedia_recorder = false;

	//LOG(INFO) << "hello for";

	for(auto &it : tmp_ipa){
		if(it->getName() == "Multimedia Recorder")
			is_multimedia_recorder = true;
	}
	if(!is_multimedia_recorder){
		//std::cout << "in constructure " << std::endl;
		CameraFactory cf;

		this->camera = cf.getCamera(camera_attribute);
		this->image_acquisition = std::make_shared<ImageAcquisition>(*camera,
				image_processor_attribute->getImageProcessorAttributeVector().size());
	}



	ImageProcessorFactory ipf(camera_attribute);

	if(!is_multimedia_recorder){
	this->image_processor_pool = ipf.getImageProcessorPool(
			image_processor_attribute,
			*this->image_acquisition->getOutputImageQueue());
	}
	else{
		MultipleImageQueue miq(1);
		this->image_processor_pool = ipf.getImageProcessorPool(
					image_processor_attribute,
					miq);
	}

}

VideoSurveillance::~VideoSurveillance() {
	//std::cerr << "delete camera" <<std::endl;
	LOG(INFO) << "VideoSurveillance Terminate";
	//std::cerr << "End Terminate VideoSurveillance :" << getName() << std::endl;
}

// This member function start video surveillance process
void VideoSurveillance::start() {
	if(!this->is_multimedia_recorder){
		acquisiting = std::make_shared<std::thread>(std::ref(*this->image_acquisition));
	}

	for (unsigned long i = 0; i < image_processor_pool.size(); ++i) {
		std::shared_ptr<std::thread> working = std::make_shared<std::thread>(std::ref(*image_processor_pool[i]));
		thread_pool.push_back(working);
	}

}

void VideoSurveillance::stop() {
	Job::stop();

//	std::cerr << "start terminate vs" << std::endl;
	LOG(INFO) << "VideoSurveillance stop";

	if (this->image_acquisition){
		this->image_acquisition->stop();
		acquisiting->join();
	}

	for (unsigned long i = 0; i < image_processor_pool.size(); ++i) {

		image_processor_pool[i]->stop();
		thread_pool[i]->join();

	}
	image_processor_pool.clear();
	thread_pool.clear();
//	std::cerr << "end" << std::endl;
}

}
