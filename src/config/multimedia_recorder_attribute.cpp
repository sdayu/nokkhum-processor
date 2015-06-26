/*
 * multimedia_recorder_attribute.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: superizer
 */


#include "multimedia_recorder_attribute.hpp"
namespace nokkhum {

MultimediaRecorderAttribute::MultimediaRecorderAttribute(std::string name,
		std::string directory, int width, int height, int fps, std::string extension) :
		RecorderAttribute(name, directory, width, height, extension), fps(fps) {
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

const std::string& MultimediaRecorderAttribute::getAudioUri() const {
	return audio_uri;
}

void MultimediaRecorderAttribute::setAudioUri(const std::string& audio_uri) {
	this->audio_uri = audio_uri;
}

const std::string& MultimediaRecorderAttribute::getVideoUri() const {
	return video_uri;
}

void MultimediaRecorderAttribute::setVideoUri(const std::string& video_uri) {
	this->video_uri = video_uri;
}

} /* namespace nokkhum */




