/*
 * camera.h
 *
 *  Created on: Apr 11, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CAMERA_HPP_
#define NOKKHUM_CAMERA_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

namespace nokkhum {

class Camera {
public:
	Camera();
	Camera(int width, int height, int fps);
	virtual ~Camera();

	int getWidth();
	int getHeight();
	int getFps();

	virtual void getImage(Mat& image) = 0;
	Camera& operator >>(Mat& image);
private:
	int width;
	int height;
	int fps;
};

}

#endif /* NOKKHUM_CAMERA_H_ */
