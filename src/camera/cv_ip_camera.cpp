/*
 * cv_ip_camera.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: boatkrap
 */

#include "cv_ip_camera.hpp"

#include <iostream>
#include <stdexcept>

#include <opencv2/opencv.hpp>


/* IP_CAMERA_HPP_ */
namespace nokkhum
{
    CvIpCamera::CvIpCamera(int width, int height, int fps, std::string url, std::string username, std::string password)
    :IpCamera(width, height, fps, url, username, password)
    {
		capture = cv::VideoCapture(url);
//		capture.set(CV_CAP_PROP_FPS, fps);
//		capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
//		capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);

//      std::cout << "url: " << url << std::endl;

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
    	cv::Mat aq_image;
    	this->capture >> aq_image;
    	if (!aq_image.empty() && aq_image.size() != cv::Size(this->getWidth(), this->getHeight())){
    		cv::resize(aq_image, image, cv::Size(this->getWidth(), this->getHeight()));
    	}
    	else {
    		image = aq_image;
    	}
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
