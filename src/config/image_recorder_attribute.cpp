/*
 * image_recorder_attribute.cpp
 *
 *  Created on: Jul 26, 2011
 *      Author: boatkrap
 */

#include "image_recorder_attribute.hpp"

namespace nokkhum {

ImageRecorderAttribute::ImageRecorderAttribute(std::string name, std::string directory, int width, int height, unsigned int interval)
: RecorderAttribute (name, directory, width, height), interval(interval) {
	// TODO Auto-generated constructor stub

}

ImageRecorderAttribute::~ImageRecorderAttribute() {
	// TODO Auto-generated destructor stub
}

unsigned int ImageRecorderAttribute::getInterval(){
	return this->interval;
}

} /* namespace nokkhum */
