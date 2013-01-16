/*
 * motion_detector_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "motion_detector_attribute.hpp"

namespace nokkhum {

MotionDetectorAttribute::MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
		int resolution, int interval) :
		ImageProcessorAttribute(name), resolution(resolution), interval(interval),
		motion_analysis_method(motion_analysis_method){

}

MotionDetectorAttribute::~MotionDetectorAttribute() {
	// TODO Auto-generated destructor stub
}

int MotionDetectorAttribute::getInterval() const {
	return interval;
}

std::string MotionDetectorAttribute::getMotionAnalysis() const {
	return motion_analysis_method;
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
