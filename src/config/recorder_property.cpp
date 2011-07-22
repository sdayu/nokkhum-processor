/*
 * recorder_property..cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "recorder_property.hpp"

namespace nokkhum {

RecorderProperty::RecorderProperty(std::string name, std::string directory, int width, int height)
: ImageProcessorProperty(name), directory(directory), width(width), height(height){
	// TODO Auto-generated constructor stub

}

RecorderProperty::~RecorderProperty() {
	// TODO Auto-generated destructor stub
}

    std::string RecorderProperty::getDirectory() const
    {
        return directory;
    }

    int RecorderProperty::getHeight() const
    {
        return height;
    }

    int RecorderProperty::getWidth() const
    {
        return width;
    }

    void RecorderProperty::setDirectory(std::string directory)
    {
        this->directory = directory;
    }

    void RecorderProperty::setHeight(int height)
    {
        this->height = height;
    }

    void RecorderProperty::setWidth(int width)
    {
        this->width = width;}

} /* namespace nokkhum */
