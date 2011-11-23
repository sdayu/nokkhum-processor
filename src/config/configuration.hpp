/*
 * configuration.hpp
 *
 *  Created on: Jul 22, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CONFIGURATION_HPP_
#define NOKKHUM_CONFIGURATION_HPP_

#include <string>

#include "camera_attribute.hpp"
#include "image_processor_attribute.hpp"

namespace nokkhum {

class Configuration {
public:
	Configuration();
	Configuration(std::string json);
	virtual ~Configuration();
	CameraAttribute *getCameraAttribute() const;
	ImageProcessorAttribute *getImageProcessorAttribute() const;
	std::string getAttributes() const;

private:
	CameraAttribute *camera_attribute;
	ImageProcessorAttribute *image_processor_attribute;

	std::string attributes;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_CONFIGURATION_HPP_ */
