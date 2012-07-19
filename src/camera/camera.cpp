/*
 * camera.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#include "camera.hpp"

namespace nokkhum {

Camera::Camera() :
		width(320), height(240), fps(4) {
	// TODO Auto-generated constructor stub

}

Camera::Camera(int width, int height, int fps) :
		width(width), height(height), fps(fps) {
}

int Camera::getFps() {
	return this->fps;
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

std::string Camera::getModel() const {
	return model;
}

std::string Camera::getName() const {
	return name;
}

void Camera::setModel(std::string model) {
	this->model = model;
}

void Camera::setName(std::string name) {
	this->name = name;
}

bool Camera::isOpen(){
	return false;
}

}
