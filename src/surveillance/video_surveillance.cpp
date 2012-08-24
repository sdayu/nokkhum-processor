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

	CameraFactory cf;
	this->camera = cf.getCamera(camera_attribute);
	this->image_acquisition = std::make_shared<ImageAcquisition>(*camera,
			image_processor_attribute->getImageProcessorAttributeVector().size());

	ImageProcessorFactory ipf;
	this->image_processor_pool = ipf.getImageProcessorPool(
			image_processor_attribute,
			*this->image_acquisition->getOutputImageQueue());

}

VideoSurveillance::~VideoSurveillance() {
	//std::cerr << "delete camera" <<std::endl;
	LOG(INFO) << "VideoSurveillance Terminate";
	//std::cerr << "End Terminate VideoSurveillance :" << getName() << std::endl;
}

// This member function start video surveillance process
void VideoSurveillance::start() {
	acquisiting = std::make_shared<std::thread>(std::ref(*this->image_acquisition));
	for (unsigned long i = 0; i < image_processor_pool.size(); ++i) {
		std::shared_ptr<std::thread> working = std::make_shared<std::thread>(std::ref(*image_processor_pool[i]));
		thread_pool.push_back(working);
	}

}

void VideoSurveillance::stop() {
	Job::stop();

//	std::cerr << "start terminate vs" << std::endl;
	LOG(INFO) << "VideoSurveillance stop";

	this->image_acquisition->stop();
	acquisiting->join();

	for (unsigned long i = 0; i < image_processor_pool.size(); ++i) {

		image_processor_pool[i]->stop();
		thread_pool[i]->join();

	}
	image_processor_pool.clear();
	thread_pool.clear();
//	std::cerr << "end" << std::endl;
}

}
