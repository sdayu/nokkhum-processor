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

	int getWidth();
	int getHeight();
	int getFrameRate();

	virtual void getImage(Mat& image) = 0;
	Camera& operator >>(Mat& image);
private:
	int width;
	int height;
	int frame_rate;
};

}

#endif /* NOKKHUM_CAMERA_H_ */
