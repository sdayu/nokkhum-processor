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
	std::shared_ptr<CameraAttribute> getCameraAttribute() const;
	std::shared_ptr<ImageProcessorAttribute> getImageProcessorAttribute() const;
	std::string getAttributes() const;

private:
	std::shared_ptr<CameraAttribute> camera_attribute;
	std::shared_ptr<ImageProcessorAttribute> image_processor_attribute;

	std::string attributes;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_CONFIGURATION_HPP_ */
