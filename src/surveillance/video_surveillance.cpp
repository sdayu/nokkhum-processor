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
#include <queue>
#include <string>
#include <sstream>
#include <iomanip>
using std::thread;
using std::queue;
using std::string;

#include "image_acquisition.hpp"
#include "video_recorder.hpp"

#include "../video/cv_video_writer.hpp"

namespace nokkhum {

VideoSurveillance::VideoSurveillance() {
	camera = new CvIpCamera(320, 240, 10, "rtsp://172.30.140.204/play2.sdp");

}

VideoSurveillance::~VideoSurveillance() {
	// TODO Auto-generated destructor stub
}

// This member function start video surveillance process
void VideoSurveillance::start() {

	ImageAcquisition acquisition(*camera, image_queue);

	time_t rawtime;
	time ( &rawtime );
	tm* time_struct =  localtime(&rawtime);

	string record_name;
	ostringstream oss;
	oss << time_struct->tm_year+1900
			<< std::setw(2) << std::setfill('0') << time_struct->tm_mon+1
			<< std::setw(2) << std::setfill('0') << time_struct->tm_mday
			<< std::setw(2) << std::setfill('0') << time_struct->tm_hour
			<< std::setw(2) << std::setfill('0') << time_struct->tm_min
			<< std::setw(2) << std::setfill('0') << time_struct->tm_sec
			<< ".avi";

	CvVideoWriter writer(oss.str(), "/tmp",
			this->camera->getWidth(), this->camera->getHeight(),
			this->camera->getFps());

    //VideoRecorder video_recorder(writer, image_queue);

    std::cout<< "start initial"<<std::endl;
    thread acquisiting(std::ref(acquisition));
    //thread recorder(std::ref(video_recorder));

    acquisition.start();
    //video_recorder.start();

    std::cout<< "write to:"<< writer.getRecordName() <<std::endl;
    std::cout<< "main process sleep"<<std::endl;
    sleep(30);
    std::cout<< "stop thread"<<std::endl;
    acquisition.stop();
    //video_recorder.stop();
    std::cout<< "begin finalization"<<std::endl;
    std::cout<< "acq running :"<<acquisition.running<<std::endl;
    acquisiting.join();
    //recorder.join();

    std::cout<< "end"<<std::endl;
//	namedWindow("video",1);
//    while(true)
//    {
//    	time ( &rawtime );
//    		std::cout << "time: " << ctime (&rawtime) << std::endl;
//
//            imshow("video", image_queue.front());
//
//            //writer << mat;
//
//            if(waitKey(30) >= 0) break;
//    }

}

}
