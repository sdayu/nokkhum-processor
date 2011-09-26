/*
 * video_recorder_property.cpp
 *
 *  Created on: Jul 25, 2011
 *      Author: boatkrap
 */

#include "video_recorder_property.hpp"

namespace nokkhum {

VideoRecorderProperty::VideoRecorderProperty(std::string name,
		std::string directory, int width, int height, int fps) :
		RecorderProperty(name, directory, width, height), fps(fps) {
	// TODO Auto-generated constructor stub

	this->maximum_wait_motion = 0;
	this->record_motion = false;

}

VideoRecorderProperty::VideoRecorderProperty(std::string name,
		std::string directory, int width, int height, int fps,
		bool record_motion, int maximum_wait_motion) :
		RecorderProperty(name, directory, width, height), fps(fps),
		maximum_wait_motion(maximum_wait_motion), record_motion(record_motion)
		{

}

VideoRecorderProperty::~VideoRecorderProperty() {
	// TODO Auto-generated destructor stub
}

int VideoRecorderProperty::getFps() const {
	return fps;
}

void VideoRecorderProperty::setFps(int fps) {
	this->fps = fps;
}

int VideoRecorderProperty::getMaximumWaitMotion() const {
	return maximum_wait_motion;
}

bool VideoRecorderProperty::isRecordMotion() const {
	return record_motion;
}

} /* namespace nokkhum */
