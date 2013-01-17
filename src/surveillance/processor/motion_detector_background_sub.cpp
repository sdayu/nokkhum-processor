#include "motion_detector_background_sub.hpp"

#include <iostream>
#include <glog/logging.h>
#include <ctime>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace nokkhum{

BackgroundMotionDetector::BackgroundMotionDetector(ImageQueue &input_image_queue) :
	MotionDetector(input_image_queue) {
	// TODO Auto-generated constructor stub
	name = "Background Motion Detection";

}

BackgroundMotionDetector::BackgroundMotionDetector(ImageQueue &input_image_queue, MotionDetectorAttribute &mdp) :
	MotionDetector(input_image_queue, mdp) {
	//std::cout << "hello background subtraction constructor :)" << std::endl;
	this -> name = "Background Motion Detection";
}

BackgroundMotionDetector::~BackgroundMotionDetector(){

}

bool BackgroundMotionDetector::detectMotion(cv::Mat background, cv::Mat current){
    // Convert to black and white
    //cv::Mat background_bw, current_bw,
	cv::Mat diff, thresh;
	// std::cout << "hello background subtraction :)" << std::endl;
    //cv::cvtColor(background, background_bw, CV_RGB2GRAY);
    //cv::cvtColor(current, current_bw, CV_RGB2GRAY);
    diff = cv::abs(current - background);
    cv::threshold(diff,thresh,50,255,CV_THRESH_BINARY);

    int motion_count = cv::countNonZero(thresh);

	if (motion_count > 3)
		return true;
	else
		return false;
}
}
