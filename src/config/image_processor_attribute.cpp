/*
 * image_processor_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */
#include <iostream>

#include "image_processor_attribute.hpp"

namespace nokkhum {

ImageProcessorAttribute::ImageProcessorAttribute(std::string name) :
		name(name) {
//	std::cout<<"create: "<<name<<std::endl;
}

ImageProcessorAttribute::ImageProcessorAttribute() {
	name = "default";
}

ImageProcessorAttribute::~ImageProcessorAttribute() {

//	std::cout<<"destroy: "<<name<<std::endl;
}

std::string ImageProcessorAttribute::getName() const {
	return name;
}

std::vector< std::shared_ptr<ImageProcessorAttribute> > ImageProcessorAttribute::getImageProcessorAttributeVector() const {
	return image_processor_attribute_vector;
}

void ImageProcessorAttribute::setName(std::string name) {
	this->name = name;
}

void ImageProcessorAttribute::addImageProcessorAttribute(
		std::shared_ptr<ImageProcessorAttribute> imageProcessorAttribute) {
	this->image_processor_attribute_vector.push_back(imageProcessorAttribute);
}

} /* namespace nokkhum */
