/*
 * cv_camera.h
 *
 *  Created on: Apr 17, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CV_CAMERA_H_
#define NOKKHUM_CV_CAMERA_H_

#include "camera.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace nokkhum {

class CvCamera: public nokkhum::Camera {
public:
	CvCamera(int width, int height, int fps, int device);
	virtual ~CvCamera();

	void getImage(cv::Mat& image);

private:
	cv::VideoCapture *capture;
	int device;
};

}

#endif /* NOKKHUM_CV_CAMERA_H_ */
