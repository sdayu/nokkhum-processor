/*
 * cv_ip_camera.hpp
 *
 *  Created on: Apr 16, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_CV_IP_CAMERA_HPP_
#define NOKKHUM_CV_IP_CAMERA_HPP_

#include "ip_camera.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

namespace nokkhum {

class CvIpCamera: public nokkhum::IpCamera {
public:
	CvIpCamera(int width, int height, int fps, string url, string username = "", string password = "");
	virtual ~CvIpCamera();

	void getImage(Mat& image);
	VideoCapture* getCapture();
	CvIpCamera& operator >>(Mat& image);
private:
	VideoCapture *capture;
};

}

#endif /* NOKKHUM_CV_IP_CAMERA_HPP_ */
