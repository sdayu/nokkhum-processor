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
			enable_area_of_interest = false;
}

MotionDetectorAttribute::MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
		int resolution, int interval, bool enable_area_of_interest,  point p1, point p2) :
		ImageProcessorAttribute(name), resolution(resolution), interval(interval),
		motion_analysis_method(motion_analysis_method), enable_area_of_interest(enable_area_of_interest), p1(p1), p2(p2){

}

MotionDetectorAttribute::~MotionDetectorAttribute() {
	// TODO Auto-generated destructor stub
}

int MotionDetectorAttribute::getInterval() const {
	return interval;
}

bool MotionDetectorAttribute::getEnableAreaOfInterest() const{
	return enable_area_of_interest;
}

std::string MotionDetectorAttribute::getMotionAnalysis() const {
	return motion_analysis_method;
}

int MotionDetectorAttribute::getResolution() const {
	return resolution;
}

point MotionDetectorAttribute::getStartPoint() const{
	return p1;
}
point MotionDetectorAttribute::getEndPoint() const{
	return p2;
}

void MotionDetectorAttribute::setInterval(int interval) {
	this->interval = interval;
}

void MotionDetectorAttribute::setResolution(int resolution) {
	this->resolution = resolution;
}

} /* namespace nokkhum */
