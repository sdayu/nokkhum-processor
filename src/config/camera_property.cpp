/*
 * camera_property.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "camera_property.hpp"

namespace nokkhum {

CameraProperty::CameraProperty(std::string name, std::string model,
		std::string url, int width, int height, int fps, std::string username,
		std::string password) :
		name(name), model(model), url(url), width(width), height(height), fps(
				fps), username(username), password(password) {

}

CameraProperty::~CameraProperty() {
}

int CameraProperty::getFps() const {
	return fps;
}

int CameraProperty::getHeight() const {
	return height;
}

std::string CameraProperty::getModel() const {
	return model;
}

std::string CameraProperty::getName() const {
	return name;
}

std::string CameraProperty::getUrl() const {
	return url;
}

int CameraProperty::getWidth() const {
	return width;
}

void CameraProperty::setFps(int fps) {
	this->fps = fps;
}

void CameraProperty::setHeight(int height) {
	this->height = height;
}

void CameraProperty::setModel(std::string model) {
	this->model = model;
}

void CameraProperty::setName(std::string name) {
	this->name = name;
}

void CameraProperty::setUrl(std::string url) {
	this->url = url;
}

void CameraProperty::setWidth(int width) {
	this->width = width;
}

std::string CameraProperty::getPassword() const {
	return password;
}

std::string CameraProperty::getUsername() const {
	return username;
}

} /* namespace nokkhum */
