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
	IpCamera(int width, int height, int frame_rate, string url);
	virtual ~IpCamera();
    string get_url() const;

private:
	string url;
};

}

#endif /* NOKKHUM_IP_CAMERA_HPP_ */
