/*
 * cv_ip_camera.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: boatkrap
 */

#include "cv_ip_camera.hpp"

#include <iostream>
#include <stdexcept>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>


/* IP_CAMERA_HPP_ */
namespace nokkhum
{
    CvIpCamera::CvIpCamera(int width, int height, int fps, string url, string username, string password)
    :IpCamera(width, height, fps, url, username, password)
    {
		capture = cv::VideoCapture(url);
		capture.set(CV_CAP_PROP_FPS, fps);
        // capture = new VideoCapture(0);
        // this->capture->set(CV_CAP_PROP_FPS, this->get_frame_rate());
//        cout<< "url: "<<url<<endl;

		if (!capture.isOpened()) {
				std::cerr << "Camera failed to open!\n";
				throw std::runtime_error("Camera failed to open!"); //TODO need to specify exception
		}
    }

    CvIpCamera::~CvIpCamera()
    {

    }

    void CvIpCamera::getImage(Mat& image)
    {
    	this->capture >> image;
    }


    VideoCapture* CvIpCamera::getCapture(){
    	return &this->capture;
    }

    CvIpCamera & CvIpCamera::operator >>(Mat& image)
    {
    	this->getImage(image);
    	return *this;
    }

    bool CvIpCamera::isOpen(){
    	return capture.isOpened();
    }

    // open the default camera
    // TODO Auto-generated destructor stub
}
