/*
 * face_detector_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "face_detector_attribute.hpp"

namespace nokkhum {

FaceDetectorAttribute::FaceDetectorAttribute(std::string name, int interval) :
		ImageProcessorAttribute(name), interval(interval) {

}

FaceDetectorAttribute::~FaceDetectorAttribute() {
	// TODO Auto-generated destructor stub
}

int FaceDetectorAttribute::getInterval() const {
	return interval;
}

void FaceDetectorAttribute::setInterval(int interval) {
	this->interval = interval;
}

} /* namespace nokkhum */
