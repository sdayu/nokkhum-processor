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
	RecorderAttribute(std::string name, std::string directory,
					  int width, int height, std::string extension);
	virtual ~RecorderAttribute();
    std::string getDirectory() const;
    std::string getExtension() const;
    int getHeight() const;
    int getWidth() const;

    void setDirectory(std::string directory);
    void setExtension(std::string extension);
    void setHeight(int height);
    void setWidth(int width);

private:
	std::string directory;
	int width;
	int height;
	std::string extension;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_RECORDER_ATTRIBUTE_HPP_ */
