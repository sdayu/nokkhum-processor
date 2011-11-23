/*
 * recorder_attribute.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_RECORDER_ATTRIBUTE_HPP_
#define NOKKHUM_RECORDER_ATTRIBUTE_HPP_

#include "image_processor_attribute.hpp"
#include <string>

namespace nokkhum {

class RecorderAttribute : public ImageProcessorAttribute {
public:
	RecorderAttribute(std::string name, std::string directory, int width, int height);
	virtual ~RecorderAttribute();
    std::string getDirectory() const;
    int getHeight() const;
    int getWidth() const;
    void setDirectory(std::string directory);
    void setHeight(int height);
    void setWidth(int width);

private:
	std::string directory;
	int width;
	int height;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_RECORDER_ATTRIBUTE_HPP_ */
