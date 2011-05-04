/*
 * camera.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#include "camera.hpp"

namespace nokkhum {

Camera::Camera() :
	width(320), height(240), frame_rate(4) {
	// TODO Auto-generated constructor stub

}

Camera::Camera(int width, int height, int frame_rate) :
		width(width), height(height), frame_rate(frame_rate){
}

int Camera::getFrameRate() {
	return this->frame_rate;
}

int Camera::getHeight() {
	return this->height;
}

int Camera::getWidth() {
	return this->width;
}

Camera & Camera::operator >>(Mat& image) {
	getImage(image);
	return *this;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

}
