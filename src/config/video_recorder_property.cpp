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

} /* namespace nokkhum */
