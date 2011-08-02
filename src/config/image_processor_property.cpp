/*
 * image_processor_property.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */
#include <iostream>

#include "image_processor_property.hpp"

namespace nokkhum {

ImageProcessorProperty::ImageProcessorProperty(std::string name) :
		name(name) {

}

ImageProcessorProperty::ImageProcessorProperty(){
	name = "default";
}

ImageProcessorProperty::~ImageProcessorProperty() {
	// TODO Auto-generated destructor stub
}

std::string ImageProcessorProperty::getName() const {
	return name;
}

ImageProcessorPropertyVector *ImageProcessorProperty::getImageProcessorPropertyVector() const {
	return image_processor_property_vector;
}

void ImageProcessorProperty::setImageProcessorPropertyVector(
		ImageProcessorPropertyVector *image_processor_property_vector) {
	this->image_processor_property_vector = image_processor_property_vector;
}

void ImageProcessorProperty::setName(std::string name) {
	this->name = name;
}

} /* namespace nokkhum */
