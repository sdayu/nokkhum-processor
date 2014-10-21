/*
 * video_recorder_attribute.hpp
 *
 *  Created on: Jul 25, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_NONE_PROCESSOR_ATTRIBUTE_HPP_
#define NOKKHUM_NONE_PROCESSOR_ATTRIBUTE_HPP_

#include <string>

#include "image_processor_attribute.hpp"

namespace nokkhum {

class NoneProcessorAttribute: public nokkhum::ImageProcessorAttribute {
public:
	NoneProcessorAttribute(std::string name);
	virtual ~NoneProcessorAttribute();
};

} /* namespace nokkhum */
#endif /* NOKKHUM_NONE_PROCESSOR_ATTRIBUTE_HPP_ */
