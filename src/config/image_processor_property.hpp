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
public:
	ImageProcessorProperty(std::string name);
	virtual ~ImageProcessorProperty();
    std::string getName() const;
    void setName(std::string name);

private:
	std::string name;
	std::vector <ImageProcessorProperty> image_processor_property;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_PROCESSOR_PROPERTY_H_ */
/*
 * image_processor_property.h
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_PROPERTY_H_
#define NOKKHUM_IMAGE_PROCESSOR_PROPERTY_H_

#include <string>
#include <vector>

namespace nokkhum {

class ImageProcessorProperty {
public:
	ImageProcessorProperty(std::string name);
	virtual ~ImageProcessorProperty();
    std::string getName() const;
    void setName(std::string name);

private:
	std::string name;
	std::vector <ImageProcessorProperty> image_processor_property;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_PROCESSOR_PROPERTY_H_ */
