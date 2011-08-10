/*
 * ip_camera.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#include "ip_camera.hpp"

namespace nokkhum {

IpCamera::IpCamera(int width, int height, int fps, string url, string username,
		string password) :
		Camera(width, height, fps), url(url), username(username), password(
				password) {
}

IpCamera::~IpCamera() {
	// TODO Auto-generated destructor stub
}

std::string IpCamera::getUrl() const {
	return url;
}

std::string IpCamera::getUsername() const {
	return username;
}

std::string IpCamera::getPassword() const {
	return password;
}

}
