/*
 * camera_attribute.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_ATTRIBUTE_HPP_
#define NOKKHUM_CAMERA_ATTRIBUTE_HPP_

#include <string>

#include "attribute.hpp"

namespace nokkhum {

class CameraAttribute : public Attribute {
public:
	CameraAttribute(std::string name, std::string model, std::string url, int width, int hight, int fps, std::string username, std::string password);
	virtual ~CameraAttribute();

    int getFps() const;
    int getHeight() const;
    int getWidth() const;
    std::string getModel() const;
    std::string getName() const;
    std::string getUrl() const;
    std::string getPassword() const;
    std::string getUsername() const;

    void setFps(int fps);
    void setHeight(int height);
    void setModel(std::string model);
    void setName(std::string name);
    void setUrl(std::string url);
    void setWidth(int width);



private:
    std::string name;
    std::string model;
    std::string url;
	int width;
	int height;
	int fps;
	std::string username;
	std::string password;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_CAMERA_ATTRIBUTE_HPP_ */
