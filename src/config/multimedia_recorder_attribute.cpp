/*
 * multimedia_recorder_attribute.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: superizer
 */


#include "multimedia_recorder_attribute.hpp"
namespace nokkhum {

MultimediaRecorderAttribute::MultimediaRecorderAttribute(std::string name,
		std::string directory, int width, int height, int fps) :
		RecorderAttribute(name, directory, width, height), fps(fps) {
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

const std::string& MultimediaRecorderAttribute::getAudioUrl() const {
	return audio_url;
}

void MultimediaRecorderAttribute::setAudioUrl(const std::string& audio_url) {
	this->audio_url = audio_url;
}

const std::string& MultimediaRecorderAttribute::getVideoUrl() const {
	return video_url;
}

void MultimediaRecorderAttribute::setVideoUrl(const std::string& video_url) {
	this->video_url = video_url;
}

} /* namespace nokkhum */




