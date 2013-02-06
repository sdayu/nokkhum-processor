/*
 * camera_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "camera_attribute.hpp"

namespace nokkhum {

CameraAttribute::CameraAttribute(std::string name, std::string model,
		std::string video_url, std::string audio_url, std::string image_url,
		int width, int height, int fps, std::string username,
		std::string password, int id) :
		name(name), model(model),
		video_url(video_url), audio_url(audio_url), image_url(image_url),
		width(width), height(height), fps(fps), username(username), password(password), id(id) {

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

std::string CameraAttribute::getVideoUrl() const {
	return video_url;
}

std::string CameraAttribute::getAudioUrl() const {
	return video_url;
}

std::string CameraAttribute::getImageUrl() const {
	return video_url;
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

void CameraAttribute::setVideoUrl(std::string url) {
	this->video_url = url;
}

void CameraAttribute::setAudioUrl(std::string url) {
	this->audio_url = url;
}

void CameraAttribute::setImageUrl(std::string url) {
	this->image_url = url;
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
