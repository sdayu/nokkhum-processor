/*
 * camera_factory.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_FACTORY_HPP_
#define NOKKHUM_CAMERA_FACTORY_HPP_

#include "camera.hpp"
#include "cv_ip_camera.hpp"
#include "../config/camera_property.hpp"

namespace nokkhum {

class CameraFactory {
public:
	CameraFactory();
	virtual ~CameraFactory();
	nokkhum::Camera* getCamera(nokkhum::CameraProperty*);
};

}

#endif /* NOKKHUM_CAMERA_FACTORY_HPP_ */
