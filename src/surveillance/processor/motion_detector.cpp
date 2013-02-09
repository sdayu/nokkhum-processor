/*
 * motion_detection.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "motion_detector.hpp"

#include <iostream>
#include <queue>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

#include <glog/logging.h>

#include <ctime>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace nokkhum {

MotionDetector::MotionDetector(ImageQueue &input_image_queue) :
	ImageProcessor("Motion Detection", input_image_queue) {
	// TODO Auto-generated constructor stub
	this->interval = 1;
	this->sensitive = 100;
	this->enable_area_of_interest = false;
	this->wait_motion_time = 10;

}

MotionDetector::MotionDetector(ImageQueue &input_image_queue, MotionDetectorAttribute &mdp) :
	ImageProcessor("Motion Detection", input_image_queue) {
	//std::cout << "hello optical flow constructor :(" << std::endl;
	this->interval = mdp.getInterval();
	this->sensitive = mdp.getSensitive();
	this->enable_area_of_interest = mdp.getEnableAreaOfInterest();
	this->wait_motion_time = mdp.getWaitMotionTime();
	this->pointStart = mdp.getStartPoint();
	this->pointEnd = mdp.getEndPoint();
	//this->width = mdp.get;

}

MotionDetector::~MotionDetector() {
	// TODO Auto-generated destructor stub
}

void MotionDetector::start() {
	//std::cout << "enable area of interest : " << this->enable_area_of_interest << std::endl;

//	std::cout<<"Motion detector start"<<std::endl;
	//cv::namedWindow("Motion Detection", 1);
	const int buffer_size = 10;
	cv::Mat prevgray, gray, flow, cflow, frame;

	boost::posix_time::ptime current_time, motion_time;
//	motion_time = boost::posix_time::microsec_clock::local_time();

	bool is_motion = false;
	//int step = 30; // before step = 15

	int image_count = 0;

	std::queue<nokkhum::Image> buffer_image;
	nokkhum::Image image;
	bool motion_sequence = false;

	while (running) {

		if(input_image_queue.empty()){
			std::this_thread::sleep_for( std::chrono::microseconds( 1000 ) );
			continue;
		}

		image = input_image_queue.pop();

		frame = image.get();
		if(this->enable_area_of_interest)
			cv::rectangle(frame ,cvPoint(this->pointStart.x, this->pointStart.y),cvPoint(this->pointEnd.x, this->pointEnd.y),cvScalar(255,0,0));

		buffer_image.push(image);

		if(++image_count < this->interval){
//			std::cout<<image_count<<" continue ..."<<std::endl;
			continue;
		}
		else{
//			std::cout<<image_count<<" reset ..."<<std::endl;

			image_count=0; //reset image count
		}


		cv::rectangle(frame,cvPoint(this->pointStart.x, this->pointStart.y),cvPoint(this->pointEnd.x, this->pointEnd.y),cvScalar(255,0,0));
		cv::imshow("Original", frame);
		this->width = frame.cols;
		if(this->enable_area_of_interest){
			frame = frame(cv::Rect(this->pointStart.x, this->pointStart.y, this->pointEnd.x, this->pointEnd.y));
		}
		//cv::imshow("Frame", frame);
		if(cv::waitKey(30)>=0) break;
		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		if (prevgray.data) {
			is_motion = detectMotion(prevgray, gray);

			if(is_motion){
//				cv::circle(cflow, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
//				std::cerr << "motion count: " << is_motion <<" sq: "<<motion_sequence << std::endl;
				cv::circle(frame, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
//				LOG(INFO) << "Have motion: " << std::dec << buffer_image.size() ;
//				std::cout<<"temporary queue size: "<< std::dec << buffer_image.size()<<std::endl;

				if (!motion_sequence){
					buffer_image.front().setMotionStatus(nokkhum::MotionStatus::BeginMotion);
					motion_sequence = true;
					// std::cerr << "start motion: " << motion_sequence << std::endl;
				}

				// std::cerr << "image in buffer: " << buffer_image.size() << std::endl;

				while(!buffer_image.empty()){
					this->push_to_output_image_queue(buffer_image.front());
					buffer_image.pop();
				}

//				std::cout<<"affter clear: "<<buffer_image.size()<<std::endl;
				motion_time = boost::posix_time::microsec_clock::local_time();
			}
			else{
				current_time = boost::posix_time::microsec_clock::local_time();
				boost::posix_time::time_duration td = current_time - motion_time;

				// LOG(INFO) << "motion diff time: " << td.total_seconds();
				if(td.total_seconds() >= this->wait_motion_time){
//					LOG(INFO) << "Drop frame : " << std::dec << buffer_image.size() << "time: "<< td.total_seconds();
//					std::cout<<"drop frame:"<<buffer_image.size()<<std::endl;
					if (motion_sequence){
						buffer_image.front().setMotionStatus(nokkhum::MotionStatus::EndMotion);
						motion_sequence = false;
						this->push_to_output_image_queue(buffer_image.front());
						// std::cerr << "end motion: " << motion_sequence << std::endl;
					}
					//std::cerr << "drop image: " << buffer_image.size() << std::endl;

					while(buffer_image.size() > buffer_size){
						buffer_image.pop();
//						std::cerr << "drop image: " << buffer_image.size() << std::endl;
					}

				}
				else{
					while(!buffer_image.empty()){
						this->push_to_output_image_queue(buffer_image.front());
						buffer_image.pop();
					}
//					LOG(INFO) << "write with out motion: "<<buffer_image.size();

				}
			}
			//if(is_motion){
	//
//			cv::imshow("Motion Detection", cflow);
		}

//		if (cv::waitKey(30) >= 0)
//			break;

		std::swap(prevgray, gray);
	}
}

void MotionDetector::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap,
		int step, double scale, const cv::Scalar& color) {
//	int motionCount = 0;
	for (int y = 0; y < cflowmap.rows; y += step){
		for (int x = 0; x < cflowmap.cols; x += step) {
			const cv::Point2f& fxy = flow.at<cv::Point2f> (y, x);
			cv::line(cflowmap, cv::Point(x, y),
					cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), color);
			cv::circle(cflowmap, cv::Point(x, y), 2, color, -1);
		}
	}

}

bool MotionDetector::detectMotion(cv::Mat prevgray, cv::Mat gray){
	// std::cout << "hello optical flow :(" << std::endl;
	int motion_count = 0;
	//int step = 30;
	//double step = 585*(1-(this->sensitive/100.0)) + 15;
	double step = (this->width-15)*(1-(this->sensitive/100.0)) + 15;
	//std::cout << "width = " << this->width << std::endl;
	cv::Mat flow;
	cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 1, step, 1,
					1, 1.2, 0);
	//std::cout << "step = " << step << std::endl;
				//cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
				//drawOptFlowMap(flow, frame, step+1, 1.5, CV_RGB(0, 255, 0));

	//			for (int y = 0; y < cflow.rows; y += step+1){
	//				for (int x = 0; x < cflow.cols; x += step+1) {
				for (int y = 0; y < flow.rows; y += step + 1) {
					for (int x = 0; x < flow.cols; x += step + 1) {
						const cv::Point2f& fxy = flow.at<cv::Point2f> (y, x);

						if(cvRound(fxy.x) != 0 && cvRound(fxy.y)!= 0){
							motion_count++;
						}
					}
				}

	if (motion_count > 0)
		return true;
	else
		return false;

}
}
