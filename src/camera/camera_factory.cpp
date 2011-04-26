/*
 * camera_factory.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: boatkrap
 */

#include "camera_factory.hpp"
#include "cv_camera.hpp"
namespace nokkhum {

CameraFactory::CameraFactory() {
	// TODO Auto-generated constructor stub

}

CameraFactory::~CameraFactory() {
	// TODO Auto-generated destructor stub
}

Camera* CameraFactory::get_ipcamera(int width, int height, int frame_rate,
		string url, string type) {
}

Camera* CameraFactory::get_camera(int width, int height, int frame_rate,
		int device) {
	Camera camera = new CvCamera(width, height, frame_rate, device);
	return camera;
}

}
