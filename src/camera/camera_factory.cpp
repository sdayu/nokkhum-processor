/*
 * camera_factory.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: boatkrap
 */

#include "camera_factory.hpp"
#include <glog/logging.h>

namespace nokkhum {

CameraFactory::CameraFactory() {
	// TODO Auto-generated constructor stub

}

CameraFactory::~CameraFactory() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<nokkhum::Camera> CameraFactory::getCamera(std::shared_ptr<nokkhum::CameraAttribute> cameraAttribute) {
	LOG(INFO) << "Build camera name: " << cameraAttribute->getName() << " url: " << cameraAttribute->getUrl();
	return std::make_shared<nokkhum::CvIpCamera> (cameraAttribute->getWidth(), cameraAttribute->getHeight(),
			cameraAttribute->getFps(), cameraAttribute->getUrl(), cameraAttribute->getUsername(),
			cameraAttribute->getPassword());
}

}
