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

int Camera::get_frame_rate() {
	return this->frame_rate;
}

int Camera::get_height() {
	return this->height;
}

int Camera::get_width() {
	return this->width;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

}
