/*
 * motion_detector_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "motion_detector_attribute.hpp"

namespace nokkhum {

MotionDetectorAttribute::MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
		double sensitive, int interval, int wait_motion_time) :
		ImageProcessorAttribute(name), sensitive(sensitive), interval(interval),
		motion_analysis_method(motion_analysis_method), wait_motion_time(wait_motion_time){
			enable_area_of_interest = false;
}

MotionDetectorAttribute::MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
		double sensitive, int interval, int(wait_motion_time),
		bool enable_area_of_interest,  point p1, point p2) :
		ImageProcessorAttribute(name), sensitive(sensitive), interval(interval),
		wait_motion_time(wait_motion_time),
		motion_analysis_method(motion_analysis_method), enable_area_of_interest(enable_area_of_interest), p1(p1), p2(p2){

}

MotionDetectorAttribute::MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
		double sensitive, int interval, int(wait_motion_time),
		bool enable_area_of_interest,  std::vector< std::vector<cv::Point> > mul_point, std::vector<std::string> area_name) :
		ImageProcessorAttribute(name), sensitive(sensitive), interval(interval),
		wait_motion_time(wait_motion_time),
		motion_analysis_method(motion_analysis_method), enable_area_of_interest(enable_area_of_interest), mul_point(mul_point), area_name(area_name){

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

int MotionDetectorAttribute::getSensitive() const {
	return sensitive;
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

void MotionDetectorAttribute::setSensitive(double sensitive) {
	this->sensitive = sensitive;
}

int MotionDetectorAttribute::getWaitMotionTime() const{
	return this->wait_motion_time;
}

void MotionDetectorAttribute::setWaitMotionTime(int seconds){
	this->wait_motion_time = seconds;
}

std::vector< std::vector<cv::Point> > MotionDetectorAttribute::getMulPoint() const{
	return this->mul_point;
}

void MotionDetectorAttribute::setMulPoint(std::vector< std::vector<cv::Point> > mul_point){
	this->mul_point = mul_point;
}

std::vector<std::string> MotionDetectorAttribute::getAreaName() const{
	return this->area_name;
}

void MotionDetectorAttribute::setAreaName(std::vector<std::string> area_name){
	this->area_name = area_name;
}

} /* namespace nokkhum */
