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

nokkhum::Camera *CameraFactory::getCamera(nokkhum::CameraProperty *cameraProperty) {
	LOG(INFO) << "Build camera name: " << cameraProperty->getName() << " url: " << cameraProperty->getUrl();
	return new nokkhum::CvIpCamera(cameraProperty->getWidth(), cameraProperty->getHeight(),
			cameraProperty->getFps(), cameraProperty->getUrl(), cameraProperty->getUsername(),
			cameraProperty->getPassword());
}

}
