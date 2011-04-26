/*
 * camera.h
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_HPP_
#define NOKKHUM_CAMERA_HPP_

#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace cv;

namespace nokkhum {

class Camera {
public:
	Camera();
	Camera(int width, int height, int frame_rate);
	virtual ~Camera();

	int get_width();
	int get_height();
	int get_frame_rate();

	virtual cv::Mat get_image() = 0;
private:
	int width;
	int height;
	int frame_rate;
};

}

#endif /* NOKKHUM_CAMERA_H_ */
