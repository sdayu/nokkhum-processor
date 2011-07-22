/*
 * configuration.hpp
 *
 *  Created on: Jul 22, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CONFIGURATION_HPP_
#define NOKKHUM_CONFIGURATION_HPP_

#include "camera_property.hpp"
#include "image_processor_property.hpp"

namespace nokkhum {

class Configuration {
public:
	Configuration();
	virtual ~Configuration();
	CameraProperty *getCameraProperty() const;
	ImageProcessorProperty *getImageProcessorProperty() const;

private:
	CameraProperty *camera_property;
	ImageProcessorProperty *image_processor_property;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_CONFIGURATION_HPP_ */
