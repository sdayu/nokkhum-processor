/*
 * configuration.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: boatkrap
 */

#include "configuration.hpp"
#include "json_parser.hpp"

namespace nokkhum {

Configuration::Configuration() {
	this->camera_property = nullptr;
	this->image_processor_property = nullptr;
}

Configuration::Configuration(std::string json) {
	JsonParser jp;
	PropertyMap* property_map = jp.parse(json);
	this->camera_property = (CameraProperty*)(*property_map)["camera"];
	this->image_processor_property = (ImageProcessorProperty*)(*property_map)["processors"];

	delete property_map;
	property_map = nullptr;


//	std::cout<<"============== configuration =============="<<std::endl;
//	std::cout<<"camera name:"<< this->camera_property->getName() <<std::endl;
//	std::cout<<"Image Processor name:"<<this->image_processor_property->getName()<<std::endl;
//	std::cout<<"Image Processor size:"<<this->image_processor_property->getImageProcessorPropertyVector().size()<<std::endl;

	std::vector<ImageProcessorProperty*> ipp = this->image_processor_property->getImageProcessorPropertyVector();

//	for (std::vector<ImageProcessorProperty*>::size_type i = 0; i < ipp.size();++i){
//		std::cout<<"processor name: "<<ipp[i]->getName()<<std::endl;
//	}
}

Configuration::~Configuration() {
	delete this->camera_property;
	delete this->image_processor_property;

	this->camera_property = nullptr;
	this->image_processor_property = nullptr;

}

CameraProperty *Configuration::getCameraProperty() const {
	return camera_property;
}

ImageProcessorProperty *Configuration::getImageProcessorProperty() const {
	return image_processor_property;
}

} /* namespace nokkhum */
