/*
 * video_surveillance.cpp
 *
 *  Created on: May 3, 2011
 *      Author: boatkrap
 */

#include "video_surveillance.hpp"

#include <ctime>

#include <iostream>
#include <thread>
using std::thread;

namespace nokkhum {

VideoSurveillance::VideoSurveillance() {
	camera = new CvIpCamera(320, 240, 10, "rtsp://172.30.140.204/play2.sdp");

}

VideoSurveillance::~VideoSurveillance() {
	// TODO Auto-generated destructor stub
}

// This member function start video surveillance process
void VideoSurveillance::start() {
	bool running = true;
	time_t rawtime;
	Mat image;

	namedWindow("video",1);
    while(running)
    {
    	time ( &rawtime );
    		std::cout << "time: " << ctime (&rawtime) << std::endl;
    		(*camera) >> image;

    		this->image_queue.push(image);
            imshow("video", image);

            //writer << mat;

            if(waitKey(30) >= 0) break;
    }
}

}
