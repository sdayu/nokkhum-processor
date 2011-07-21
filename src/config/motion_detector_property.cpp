/*
 * motion_detector_property.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "motion_detector_property.hpp"

namespace nokkhum {

MotionDetectorProperty::MotionDetectorProperty(std::string name, int resolution,
		int interval) :
		ImageProcessorProperty(name), resolution(resolution), interval(interval) {

}

MotionDetectorProperty::~MotionDetectorProperty() {
	// TODO Auto-generated destructor stub
}

int MotionDetectorProperty::getInterval() const {
	return interval;
}

int MotionDetectorProperty::getResolution() const {
	return resolution;
}

void MotionDetectorProperty::setInterval(int interval) {
	this->interval = interval;
}

void MotionDetectorProperty::setResolution(int resolution) {
	this->resolution = resolution;
}

} /* namespace nokkhum */
