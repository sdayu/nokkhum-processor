/*
 * image_processor_property.h
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_PROPERTY_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_PROPERTY_HPP_

#include <string>
#include <vector>

#include "property.hpp"

namespace nokkhum {

class ImageProcessorProperty : public Property {

typedef std::vector<ImageProcessorProperty*> ImageProcessorPropertyVector;

public:
	ImageProcessorProperty(std::string name);
	virtual ~ImageProcessorProperty();
    std::string getName() const;
    void setName(std::string name);
    ImageProcessorPropertyVector getImageProcessorPropertyVector() const;


private:
	std::string name;
	ImageProcessorPropertyVector image_processor_property_vector;
};

typedef std::vector<ImageProcessorProperty*> ImageProcessorPropertyVector;

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_PROCESSOR_PROPERTY_H_ */
