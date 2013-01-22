/*
 * image_recorder_attribute.hpp
 *
 *  Created on: Jul 26, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_RECORDER_ATTRIBUTE_HPP_
#define NOKKHUM_IMAGE_RECORDER_ATTRIBUTE_HPP_

#include <string>

#include "recorder_attribute.hpp"

namespace nokkhum {

class ImageRecorderAttribute : public RecorderAttribute {
public:
	ImageRecorderAttribute(std::string name, std::string directory, int width, int height, unsigned int interval);
	virtual ~ImageRecorderAttribute();

	unsigned int getInterval();

protected:
	int interval;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_RECORDER_ATTRIBUTE_HPP_ */
