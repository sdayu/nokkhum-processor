/*
 * ip_camera.hpp
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IP_CAMERA_HPP_
#define NOKKHUM_IP_CAMERA_HPP_

#include <string>

#include "camera.hpp"

namespace nokkhum {

class IpCamera: public nokkhum::Camera {
public:
	IpCamera(int width, int height, int fps, std::string url, std::string username, std::string password);
	virtual ~IpCamera();
    std::string getUrl() const;
    std::string getUsername() const;
    std::string getPassword() const;

private:
    std::string url;
    std::string username;
    std::string password;
};

}

#endif /* NOKKHUM_IP_CAMERA_HPP_ */
