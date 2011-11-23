/*
 * motion_detector_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "motion_detector_attribute.hpp"

namespace nokkhum {

MotionDetectorAttribute::MotionDetectorAttribute(std::string name, int resolution,
		int interval) :
		ImageProcessorAttribute(name), resolution(resolution), interval(interval) {

}

MotionDetectorAttribute::~MotionDetectorAttribute() {
	// TODO Auto-generated destructor stub
}

int MotionDetectorAttribute::getInterval() const {
	return interval;
}

int MotionDetectorAttribute::getResolution() const {
	return resolution;
}

void MotionDetectorAttribute::setInterval(int interval) {
	this->interval = interval;
}

void MotionDetectorAttribute::setResolution(int resolution) {
	this->resolution = resolution;
}

} /* namespace nokkhum */
