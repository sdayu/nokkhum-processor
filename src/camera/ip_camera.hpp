/*
 * ip_camera.hpp
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IP_CAMERA_HPP_
#define NOKKHUM_IP_CAMERA_HPP_

#include <string>
using namespace std;

#include "camera.hpp"

namespace nokkhum {

class IpCamera: public nokkhum::Camera {
public:
	IpCamera(int width, int height, int frame_rate, string url, string username, string password);
	virtual ~IpCamera();
    string getUrl() const;

private:
	string url;
	string username;
	string password;
};

}

#endif /* NOKKHUM_IP_CAMERA_HPP_ */
