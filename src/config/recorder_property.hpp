/*
 * recorder_property.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_RECORDER_PROPERTY_HPP_
#define NOKKHUM_RECORDER_PROPERTY_HPP_

#include "image_processor_property.hpp"
#include <string>

namespace nokkhum {

class RecorderProperty : public ImageProcessorProperty {
public:
	RecorderProperty(std::string name, std::string directory, int width, int height);
	virtual ~RecorderProperty();
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
#endif /* NOKKHUM_RECORDER_PROPERTY_HPP_ */
