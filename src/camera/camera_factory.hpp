/*
 * camera_factory.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_FACTORY_HPP_
#define NOKKHUM_CAMERA_FACTORY_HPP_

#include "camera.hpp"
using nokkhum::Camera;

namespace nokkhum {

class CameraFactory {
public:
	CameraFactory();
	virtual ~CameraFactory();
	Camera* getIpCamera(int width, int height, int fps, string url, string type);
	Camera* getCamera(int width, int height, int fps, int device);
};

}

#endif /* NOKKHUM_CAMERA_FACTORY_HPP_ */
