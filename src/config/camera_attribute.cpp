/*
 * camera_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "camera_attribute.hpp"

namespace nokkhum {

CameraAttribute::CameraAttribute(std::string name, std::string model,
		std::string url, int width, int height, int fps, std::string username,
		std::string password, int id) :
		name(name), model(model), url(url), width(width), height(height), fps(
				fps), username(username), password(password), id(id) {

}

CameraAttribute::~CameraAttribute() {
}

int CameraAttribute::getFps() const {
	return fps;
}

int CameraAttribute::getId() const {
	return id;
}

int CameraAttribute::getHeight() const {
	return height;
}

std::string CameraAttribute::getModel() const {
	return model;
}

std::string CameraAttribute::getName() const {
	return name;
}

std::string CameraAttribute::getUrl() const {
	return url;
}

int CameraAttribute::getWidth() const {
	return width;
}

void CameraAttribute::setFps(int fps) {
	this->fps = fps;
}

void CameraAttribute::setHeight(int height) {
	this->height = height;
}

void CameraAttribute::setModel(std::string model) {
	this->model = model;
}

void CameraAttribute::setName(std::string name) {
	this->name = name;
}

void CameraAttribute::setUrl(std::string url) {
	this->url = url;
}

void CameraAttribute::setWidth(int width) {
	this->width = width;
}

std::string CameraAttribute::getPassword() const {
	return password;
}

std::string CameraAttribute::getUsername() const {
	return username;
}

} /* namespace nokkhum */
