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
using std::thread;
using std::queue;
using std::string;

#include "acquisition/image_acquisition.hpp"
#include "processor/video_recorder.hpp"

#include "../camera/camera_factory.hpp"
#include "processor/image_processor_factory.hpp"

#include "../video/cv_video_writer.hpp"
#include "../util/multiple_mat_queue.hpp"

#include "processor/motion_detector.hpp"
#include "processor/face_detector.hpp"

namespace nokkhum {

VideoSurveillance::VideoSurveillance(Configuration &conf) : Job("Video Surveillance") {
	camera_property = conf.getCameraProperty();
	image_processor_property = conf.getImageProcessorProperty();

	CameraFactory cf;
	this->camera = cf.getCamera(camera_property);
	this->image_acquisition = new ImageAcquisition(*camera, image_processor_property->getImageProcessorPropertyVector().size());

	ImageProcessorFactory ipf;
	this->image_processor_pool = ipf.getImageProcessorPool(image_processor_property, *this->image_acquisition->getOutputImageQueue());
}

VideoSurveillance::~VideoSurveillance() {
	delete camera_property;
	delete image_processor_property;

	camera_property = nullptr;
	image_processor_property = nullptr;
}

// This member function start video surveillance process
void VideoSurveillance::start() {

	vector<thread*> thread_pool;

    thread acquisiting(std::ref(*this->image_acquisition));

    for(unsigned long i = 0; i < image_processor_pool.size(); ++i){
    	thread *working = new thread(std::ref(*image_processor_pool[i]));
    	thread_pool.push_back(working);
    }

    std::cout<<"sleep in vs"<<std::endl;
    sleep(700);

    std::cout<<"start terminate vs"<<std::endl;
    this->image_acquisition->stop();
    acquisiting.join();

    for(unsigned long i = 0; i < image_processor_pool.size(); ++i){
    	std::cout<<"start to stop"<<std::endl;
    	image_processor_pool[i]->stop();
    	std::cout<<"start to join"<<std::endl;
    	thread_pool[i]->join();
    	std::cout<<"start to delete"<<std::endl;
    	delete thread_pool[i];
    	std::cout<<"delete success"<<std::endl;
    	thread_pool[i] = nullptr;
    }



    std::cout<< "end"<<std::endl;
}

}
