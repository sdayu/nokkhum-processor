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
#include <chrono>
#include <thread>

namespace nokkhum {

class CameraFactory {
public:
	CameraFactory();
	virtual ~CameraFactory();
	std::shared_ptr<nokkhum::Camera> getCamera(std::shared_ptr<nokkhum::CameraAttribute>);
};

class CameraStartTimer {
public:
	CameraStartTimer(unsigned long millisecond);
	virtual ~CameraStartTimer();

	void start();
	void stop();


private:
	bool runnable;
	std::chrono::milliseconds sleep_duration;
	std::thread timer;

	void run();
};

}
#endif /* NOKKHUM_CAMERA_FACTORY_HPP_ */
