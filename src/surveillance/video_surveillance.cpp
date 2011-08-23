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
#include "process/video_recorder.hpp"

#include "../video/cv_video_writer.hpp"
#include "../util/multiple_mat_queue.hpp"
#include "process/motion_detector.hpp"
#include "process/face_detector.hpp"

namespace nokkhum {

VideoSurveillance::VideoSurveillance() {

}

VideoSurveillance::~VideoSurveillance() {
	// TODO Auto-generated destructor stub
}

// This member function start video surveillance process
void VideoSurveillance::start() {

	//CvIpCamera camera(320, 240, 10, "rtsp://172.30.140.204/play2.sdp");
	CvIpCamera camera(320, 240, 10, "rtsp://172.30.143.249/play2.sdp");

	MultipleMatQueue multiple_queue(3);

	ImageAcquisition acquisition(camera, multiple_queue);

	time_t rawtime;
	time ( &rawtime );
	tm* time_struct =  localtime(&rawtime);

	string record_name;
	std::ostringstream oss;
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

	VideoRecorder video_recorder(multiple_queue.get(0));

//	CvVideoWriter writer1(oss.str(), "/tmp/frame",
//			camera.getWidth(), camera.getHeight(),
//			camera.getFps());
//
//	VideoRecorder video_recorder1(writer1, multiple_queue.get(1));
	MotionDetector montion_detection(multiple_queue.get(1));
	FaceDetector face_detection(multiple_queue.get(2));

    std::cout<< "start initial"<<std::endl;
    thread acquisiting(std::ref(acquisition));
    thread recorder(std::ref(video_recorder));
    thread motion_thread(std::ref(montion_detection));
    thread face_thread(std::ref(face_detection));


    std::cout<< "write to:"<< writer.getRecordName() <<std::endl;
    std::cout<< "main process sleep"<<std::endl;

    sleep(60);

    std::cout<< "stop thread"<<std::endl;
    acquisition.stop();
    video_recorder.stop();
    montion_detection.stop();
    face_detection.stop();

    std::cout<< "begin finalization"<<std::endl;
    std::cout<< "queue 0 size: " << multiple_queue.get(0).size() << std::endl;
    std::cout<< "queue 1 size: " << multiple_queue.get(1).size() << std::endl;
    std::cout<< "queue 2 size: " << multiple_queue.get(2).size() << std::endl;

    acquisiting.join();
    recorder.join();
    motion_thread.join();

//    cv::namedWindow("show", 1);
//    while(!multiple_queue.get(2).empty()){
//    	cv::imshow("show",multiple_queue.get(2).pop());
//    	if (cv::waitKey(30) > 0)
//    		break;
//    }


    std::cout<< "end"<<std::endl;
}

}
