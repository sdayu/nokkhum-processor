/*
 * cv_camera.h
 *
 *  Created on: Apr 17, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CV_CAMERA_H_
#define NOKKHUM_CV_CAMERA_H_

#include "camera.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace cv;

namespace nokkhum {

class CvCamera: public nokkhum::Camera {
public:
	CvCamera(int width, int height, int frame_rate, int device);
	virtual ~CvCamera();

	void getImage(Mat& image);

private:
	VideoCapture *capture;
	int device;
};

}

#endif /* NOKKHUM_CV_CAMERA_H_ */
