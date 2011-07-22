/*
 * image_processor_property.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "image_processor_property.hpp"

namespace nokkhum {

ImageProcessorProperty::ImageProcessorProperty(std::string name) :
		name(name) {

}

ImageProcessorProperty::~ImageProcessorProperty() {
	// TODO Auto-generated destructor stub
}

std::string ImageProcessorProperty::getName() const {
	return name;
}

void ImageProcessorProperty::setName(std::string name) {
	this->name = name;
}

} /* namespace nokkhum */
