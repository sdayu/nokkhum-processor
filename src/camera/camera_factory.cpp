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

nokkhum::Camera *CameraFactory::getCamera(nokkhum::CameraAttribute *cameraAttribute) {
	LOG(INFO) << "Build camera name: " << cameraAttribute->getName() << " url: " << cameraAttribute->getUrl();
	return new nokkhum::CvIpCamera(cameraAttribute->getWidth(), cameraAttribute->getHeight(),
			cameraAttribute->getFps(), cameraAttribute->getUrl(), cameraAttribute->getUsername(),
			cameraAttribute->getPassword());
}

}
