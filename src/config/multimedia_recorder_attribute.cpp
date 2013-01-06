/*
 * multimedia_recorder_attribute.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: superizer
 */


#include "multimedia_recorder_attribute.hpp"
namespace nokkhum {

MultimediaRecorderAttribute::MultimediaRecorderAttribute(std::string name,
		std::string directory, std::string url, int width, int height, int fps) :
		RecorderAttribute(name, directory, width, height), url(url), fps(fps) {
	// TODO Auto-generated constructor stub
}

MultimediaRecorderAttribute::~MultimediaRecorderAttribute() {
	// TODO Auto-generated destructor stub
}

int MultimediaRecorderAttribute::getFps() const {
	return fps;
}

void MultimediaRecorderAttribute::setFps(int fps) {
	this->fps = fps;
}

std::string MultimediaRecorderAttribute::getUrl() const {
	return url;
}

void MultimediaRecorderAttribute::setUrl(std::string url) {
	this->url = url;
}

} /* namespace nokkhum */




