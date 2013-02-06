/*
 * camera_factory.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: boatkrap
 */

#include "camera_factory.hpp"
#include <glog/logging.h>
#include <stdexcept>

namespace nokkhum {

CameraFactory::CameraFactory() {
	// TODO Auto-generated constructor stub

}

CameraFactory::~CameraFactory() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<nokkhum::Camera> CameraFactory::getCamera(std::shared_ptr<nokkhum::CameraAttribute> cameraAttribute) {
	LOG(INFO) << "Build camera name: " << cameraAttribute->getName() << " url: " << cameraAttribute->getVideoUrl();

	CameraStartTimer cst(100000); //100 s
	cst.start();

	std::shared_ptr<nokkhum::Camera> camera = std::make_shared<nokkhum::CvIpCamera> (cameraAttribute->getWidth(), cameraAttribute->getHeight(),
			cameraAttribute->getFps(), cameraAttribute->getVideoUrl(), cameraAttribute->getUsername(),
			cameraAttribute->getPassword());

	cst.stop();
	//LOG(INFO) << "return camera";
	return camera;
}

CameraStartTimer::CameraStartTimer(unsigned long millisecond):runnable(false){
	this->sleep_duration = std::chrono::milliseconds(millisecond);
}

CameraStartTimer::~CameraStartTimer(){
	if(this->timer.joinable()){
		this->timer.join();
	}
//	LOG(INFO) << "Terminate camera timer";
}

void CameraStartTimer::start(){
	LOG(INFO) << "Start camera timer";
	this->runnable = true;
	this->timer = std::thread(&CameraStartTimer::run, this);
}

void CameraStartTimer::stop(){
	LOG(INFO) << "Stop camera timer";
	this->runnable = false;
	this->timer.join();
}

void CameraStartTimer::run(){
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	while(this->runnable){
		std::this_thread::sleep_for( std::chrono::milliseconds(100) );
		end = std::chrono::system_clock::now();
		if (end - start > this->sleep_duration){
			LOG(INFO) << "Start build video time out";
			throw std::runtime_error("start camera time out");
		}
	}
}

}
