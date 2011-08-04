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
//	std::cout<<"create: "<<name<<std::endl;
}

ImageProcessorProperty::ImageProcessorProperty() {
	name = "default";
}

ImageProcessorProperty::~ImageProcessorProperty() {
	for(std::vector<ImageProcessorProperty*>::size_type i = 0;
			i < image_processor_property_vector.size();
			++i){
		delete image_processor_property_vector[i];
		image_processor_property_vector[i] = nullptr;
	}

//	std::cout<<"destroy: "<<name<<std::endl;
}

std::string ImageProcessorProperty::getName() const {
	return name;
}

std::vector<ImageProcessorProperty*> ImageProcessorProperty::getImageProcessorPropertyVector() const {
	return image_processor_property_vector;
}

void ImageProcessorProperty::setName(std::string name) {
	this->name = name;
}

void ImageProcessorProperty::addImageProcessorProperty(
		ImageProcessorProperty *imageProcessorProperty) {
	this->image_processor_property_vector.push_back(imageProcessorProperty);
}

} /* namespace nokkhum */
