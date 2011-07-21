/*
 * face_detector_property.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "face_detector_property.hpp"

namespace nokkhum {

FaceDetectorProperty::FaceDetectorProperty(std::string name, int interval) :
		ImageProcessorProperty(name), interval(interval) {

}

FaceDetectorProperty::~FaceDetectorProperty() {
	// TODO Auto-generated destructor stub
}

int FaceDetectorProperty::getInterval() const {
	return interval;
}

void FaceDetectorProperty::setInterval(int interval) {
	this->interval = interval;
}

} /* namespace nokkhum */
