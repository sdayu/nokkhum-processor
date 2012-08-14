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
#include "../config/camera_attribute.hpp"
#include <memory>

namespace nokkhum {

class CameraFactory {
public:
	CameraFactory();
	virtual ~CameraFactory();
	std::shared_ptr<nokkhum::Camera> getCamera(std::shared_ptr<nokkhum::CameraAttribute>);
};

}

#endif /* NOKKHUM_CAMERA_FACTORY_HPP_ */
