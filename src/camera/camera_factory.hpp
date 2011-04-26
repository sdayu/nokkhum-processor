/*
 * camera_factory.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_FACTORY_HPP_
#define NOKKHUM_CAMERA_FACTORY_HPP_

#include "camera.hpp"
using cv::Camera;

namespace nokkhum {

class CameraFactory {
public:
	CameraFactory();
	virtual ~CameraFactory();
	Camera* get_ipcamera(int width, int height, int frame_rate, string url, string type);
	Camera* get_camera(int width, int height, int frame_rate, int device);
};

}

#endif /* NOKKHUM_CAMERA_FACTORY_HPP_ */
