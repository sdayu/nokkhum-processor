/*
 * cv_ip_camera.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: boatkrap
 */

#include "cv_ip_camera.hpp"

#include <iostream>
using namespace std;

#include <opencv/highgui.h>
#include <opencv/cv.h>
using namespace cv;

/* IP_CAMERA_HPP_ */
namespace nokkhum
{
    CvIpCamera::CvIpCamera(int width, int height, int frame_rate, string url)
    :IpCamera(width, height, frame_rate, url)
    {
		capture = new VideoCapture(url);
        // capture = new VideoCapture(0);
        // this->capture->set(CV_CAP_PROP_FPS, this->get_frame_rate());
        cout<< "test: "<<this->capture->get(CV_CAP_PROP_FPS)<<endl;

        if(!capture->isOpened()){
            cerr << "Camera failed to open!\n";
        }
    }

    CvIpCamera::~CvIpCamera()
    {
    	delete capture;
    }

    Mat CvIpCamera::get_image()
    {
    	Mat fram;
    	*(this->capture) >> fram;
    	return fram;
    }

    // open the default camera
    // TODO Auto-generated destructor stub
}
