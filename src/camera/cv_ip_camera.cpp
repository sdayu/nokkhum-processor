/*
 * cv_ip_camera.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: boatkrap
 */

#include "cv_ip_camera.hpp"

#include <iostream>
#include <exception>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

/* IP_CAMERA_HPP_ */
namespace nokkhum
{
    CvIpCamera::CvIpCamera(int width, int height, int fps, string url, string username, string password)
    :IpCamera(width, height, fps, url, username, password)
    {
		capture = new VideoCapture(url);
        // capture = new VideoCapture(0);
        // this->capture->set(CV_CAP_PROP_FPS, this->get_frame_rate());
//        cout<< "url: "<<url<<endl;

		if (!capture->isOpened()) {
				std::cerr << "Camera failed to open!\n";
				throw std::exception(); //TODO need to specify exception
		}
    }

    CvIpCamera::~CvIpCamera()
    {
    	delete capture;
    }

    void CvIpCamera::getImage(Mat& image)
    {
    	*(this->capture) >> image;
    }


    VideoCapture* CvIpCamera::getCapture(){
    	return this->capture;
    }

    CvIpCamera & CvIpCamera::operator >>(Mat& image)
    {
    	this->getImage(image);
    	return *this;
    }

    // open the default camera
    // TODO Auto-generated destructor stub
}
