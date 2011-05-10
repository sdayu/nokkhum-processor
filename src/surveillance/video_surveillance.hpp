/*
 * video_surveillance.hpp
 *
 *  Created on: May 3, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_VIDEO_SURVEILLANCE_HPP_
#define NOKKHUM_VIDEO_SURVEILLANCE_HPP_

#include <queue>

#include <opencv/cv.h>

#include "../camera/cv_ip_camera.hpp"

namespace nokkhum {

class VideoSurveillance {
public:
	VideoSurveillance();
	virtual ~VideoSurveillance();

	void start();
private:

};

}

#endif /* NOKKHUM_VIDEO_SURVEILLANCE_HPP_ */
