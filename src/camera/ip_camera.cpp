/*
 * ip_camera.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#include "ip_camera.hpp"

namespace nokkhum {

IpCamera::IpCamera(int width, int height, int frame_rate, string url,
		string username, string password) :
	Camera(width, height, frame_rate), url(url), username(username),
			password(password) {
}

IpCamera::~IpCamera() {
	// TODO Auto-generated destructor stub
}

string IpCamera::getUrl() const {
	return url;
}



}
