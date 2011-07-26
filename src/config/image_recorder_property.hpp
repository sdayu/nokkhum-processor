/*
 * image_recorder_property.hpp
 *
 *  Created on: Jul 26, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_RECORDER_PROPERTY_HPP_
#define NOKKHUM_IMAGE_RECORDER_PROPERTY_HPP_

#include <string>

#include "recorder_property.hpp"

namespace nokkhum {

class ImageRecorderProperty : public RecorderProperty {
public:
	ImageRecorderProperty(std::string name, std::string directory, int width, int height);
	virtual ~ImageRecorderProperty();
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_RECORDER_PROPERTY_HPP_ */
