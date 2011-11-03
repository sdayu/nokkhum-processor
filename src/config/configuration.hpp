/*
 * configuration.hpp
 *
 *  Created on: Jul 22, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CONFIGURATION_HPP_
#define NOKKHUM_CONFIGURATION_HPP_

#include <string>

#include "camera_property.hpp"
#include "image_processor_property.hpp"

namespace nokkhum {

class Configuration {
public:
	Configuration();
	Configuration(std::string json);
	virtual ~Configuration();
	CameraProperty *getCameraProperty() const;
	ImageProcessorProperty *getImageProcessorProperty() const;
	std::string getAttributes() const;

private:
	CameraProperty *camera_property;
	ImageProcessorProperty *image_processor_property;

	std::string attributes;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_CONFIGURATION_HPP_ */
