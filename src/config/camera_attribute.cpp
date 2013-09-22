/*
 * camera_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "camera_attribute.hpp"

namespace nokkhum {

CameraAttribute::CameraAttribute(std::string name, std::string model,
		std::string video_uri, std::string audio_uri, std::string image_uri,
		int width, int height, int fps, std::string username,
		std::string password, std::string id) :
		name(name), model(model),
		video_uri(video_uri), audio_uri(audio_uri), image_uri(image_uri),
		width(width), height(height), fps(fps), username(username), password(password), id(id) {

}

CameraAttribute::~CameraAttribute() {
}

int CameraAttribute::getFps() const {
	return fps;
}

std::string CameraAttribute::getId() const {
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

std::string CameraAttribute::getVideoUri() const {
	return video_uri;
}

std::string CameraAttribute::getAudioUri() const {
	return audio_uri;
}

std::string CameraAttribute::getImageUri() const {
	return image_uri;
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

void CameraAttribute::setVideoUri(std::string uri) {
	this->video_uri = uri;
}

void CameraAttribute::setAudioUri(std::string uri) {
	this->audio_uri = uri;
}

void CameraAttribute::setImageUri(std::string uri) {
	this->image_uri = uri;
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
