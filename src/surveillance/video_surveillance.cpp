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
#include "../util/multiple_mat_queue.hpp"

namespace nokkhum {

VideoSurveillance::VideoSurveillance() {

}

VideoSurveillance::~VideoSurveillance() {
	// TODO Auto-generated destructor stub
}

// This member function start video surveillance process
void VideoSurveillance::start() {

	CvIpCamera camera(320, 240, 10, "rtsp://172.30.140.204/play2.sdp");

	MultipleMatQueue multiple_queue(2);

	ImageAcquisition acquisition(camera, multiple_queue);

	time_t rawtime;
	time ( &rawtime );
	tm* time_struct =  localtime(&rawtime);

	string record_name;
	ostringstream oss;
	oss << time_struct->tm_year+1900
			<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_mon+1
			<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_mday
			<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_hour
			<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_min
			<< "-" << std::setw(2) << std::setfill('0') << time_struct->tm_sec
			<< ".avi";

	CvVideoWriter writer(oss.str(), "/tmp",
			camera.getWidth(), camera.getHeight(),
			camera.getFps());

	VideoRecorder video_recorder(writer, multiple_queue.get(0));

//	CvVideoWriter writer1(oss.str(), "/tmp/frame",
//			camera.getWidth(), camera.getHeight(),
//			camera.getFps());
//
//	VideoRecorder video_recorder1(writer1, multiple_queue.get(1));


    std::cout<< "start initial"<<std::endl;
    thread acquisiting(std::ref(acquisition));
    thread recorder(std::ref(video_recorder));
//    thread recorder1(std::ref(video_recorder1));

    std::cout<< "write to:"<< writer.getRecordName() <<std::endl;
    std::cout<< "main process sleep"<<std::endl;
    sleep(20);
    std::cout<< "stop thread"<<std::endl;
    acquisition.stop();
    video_recorder.stop();
//    video_recorder1.stop();
    std::cout<< "begin finalization"<<std::endl;
    std::cout<< "queue 0 size: " << multiple_queue.get(0).size() << endl;
    std::cout<< "queue 1 size: " << multiple_queue.get(1).size() << endl;
    acquisiting.join();
    recorder.join();
//    recorder1.join();
    namedWindow("video",1);

    while(!multiple_queue.get(1).empty())
    {
    	time ( &rawtime );

    	std::cout<< "queue 1 size: " << multiple_queue.get(1).size() << endl;

    	cv::imshow("video", multiple_queue.get(1).front());
    	multiple_queue.get(1).pop();
        if(waitKey(30) >= 0) break;
    }

    std::cout<< "end"<<std::endl;
}

}
