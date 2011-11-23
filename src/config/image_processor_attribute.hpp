/*
 * image_processor_attribute.h
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_ATTRIBUTE_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_ATTRIBUTE_HPP_

#include <string>
#include <vector>

#include "attribute.hpp"

namespace nokkhum {

class ImageProcessorAttribute : public Attribute {

public:
	ImageProcessorAttribute(std::string name);
	ImageProcessorAttribute();
	virtual ~ImageProcessorAttribute();

    std::string getName() const;
    void setName(std::string name);

    std::vector<ImageProcessorAttribute*> getImageProcessorAttributeVector() const;

    void addImageProcessorAttribute(ImageProcessorAttribute *imageProcessorAttribute);
private:
    std::string name;
    std::vector<ImageProcessorAttribute*> image_processor_attribute_vector;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_PROCESSOR_ATTRIBUTE_H_ */
