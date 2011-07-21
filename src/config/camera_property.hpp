/*
 * camera_property.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_PROPERTY_HPP_
#define NOKKHUM_CAMERA_PROPERTY_HPP_

#include <string>

namespace nokkhum {

class CameraProperty {
public:
	CameraProperty(std::string name, std::string model, std::string url, int width, int hight, int fps);
	virtual ~CameraProperty();

    int getFps() const;
    int getHeight() const;
    std::string getModel() const;
    std::string getName() const;
    std::string getUrl() const;
    int getWidth() const;

    void setFps(int fps);
    void setHeight(int height);
    void setModel(std::string model);
    void setName(std::string name);
    void setUrl(std::string url);
    void setWidth(int width);

private:
	int width;
	int height;
	int fps;
	std::string url;
	std::string name;
	std::string model;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_CAMERA_PROPERTY_HPP_ */
