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

#include "acquisition/image_acquisition.hpp"
#include "processor/video_recorder.hpp"

#include "../video/cv_video_writer.hpp"
#include "../util/multiple_mat_queue.hpp"
#include "processor/motion_detector.hpp"
#include "processor/face_detector.hpp"

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

	ImageAcquisition acquisition(camera, 3);
	MotionDetector montion_detection(multiple_queue.get(1));
	FaceDetector face_detection(multiple_queue.get(2));

    std::cout<< "start initial"<<std::endl;
    thread acquisiting(std::ref(acquisition));
//    thread recorder(std::ref(video_recorder));
    thread motion_thread(std::ref(montion_detection));
    thread face_thread(std::ref(face_detection));


    //std::cout<< "write to:"<< writer.getRecordName() <<std::endl;
    std::cout<< "main process sleep"<<std::endl;

    sleep(60);

    std::cout<< "stop thread"<<std::endl;
    acquisition.stop();
    //video_recorder.stop();
    montion_detection.stop();
    face_detection.stop();

    std::cout<< "begin finalization"<<std::endl;
    std::cout<< "queue 0 size: " << multiple_queue.get(0).size() << std::endl;
    std::cout<< "queue 1 size: " << multiple_queue.get(1).size() << std::endl;
    std::cout<< "queue 2 size: " << multiple_queue.get(2).size() << std::endl;

    acquisiting.join();
//    recorder.join();
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
