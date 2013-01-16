/*
 * motion_detection.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "motion_detector.hpp"

#include <iostream>
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

}

MotionDetector::MotionDetector(ImageQueue &input_image_queue, MotionDetectorAttribute &mdp) :
	ImageProcessor("Motion Detection", input_image_queue) {
	//std::cout << "hello optical flow constructor :(" << std::endl;
	this->interval = mdp.getInterval();
	this->resolution = mdp.getResolution();

	this->drop_motion = 10;

}

MotionDetector::~MotionDetector() {
	// TODO Auto-generated destructor stub
}

void MotionDetector::start() {
//	std::cout<<"Motion detector start"<<std::endl;
//	cv::namedWindow("Motion Detection", 1);

	cv::Mat prevgray, gray, flow, cflow, frame;

	boost::posix_time::ptime current_time, motion_time;
//	motion_time = boost::posix_time::microsec_clock::local_time();

	int motion_count = 0;
	//int step = 30; // before step = 15

	int image_count = 0;

	std::vector<nokkhum::Image> tmp_image;
	nokkhum::Image image;
	bool motion_sequence = false;

	while (running) {

		if(input_image_queue.empty()){
			std::this_thread::sleep_for( std::chrono::microseconds( 1000 ) );
			continue;
		}

		image = input_image_queue.pop();
		tmp_image.push_back(image);

		if(++image_count < this->interval){
//			std::cout<<image_count<<" continue ..."<<std::endl;
			continue;
		}
		else{
//			std::cout<<image_count<<" reset ..."<<std::endl;

			image_count=0; //reset image count
		}

		motion_count = 0;

		frame = image.get();
		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		if (prevgray.data) {
			motion_count = detectMotion(prevgray, gray);

			if(motion_count > 3){
//				cv::circle(cflow, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
//				std::cerr << "motion count: " << motion_count <<" sq: "<<motion_sequence << std::endl;
				cv::circle(frame, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
//				LOG(INFO) << "Have motion: " << std::dec << tmp_image.size() ;
//				std::cout<<"temporary queue size: "<< std::dec << tmp_image.size()<<std::endl;

				if (!motion_sequence){
					tmp_image[0].setMotionStatus(nokkhum::MotionStatus::BeginMotion);
					motion_sequence = true;
//					std::cerr << "start motion: " << motion_sequence << std::endl;
				}

				for(unsigned long i = 0; i<tmp_image.size();++i){
					this->push_to_output_image_queue(tmp_image[i]);
				}
				tmp_image.clear();
//				std::cout<<"affter clear: "<<tmp_image.size()<<std::endl;
				motion_time = boost::posix_time::microsec_clock::local_time();
			}
			else{
				current_time = boost::posix_time::microsec_clock::local_time();
				boost::posix_time::time_duration td = current_time - motion_time;

				// LOG(INFO) << "motion diff time: " << td.total_seconds();
				if(td.total_seconds() >= this->drop_motion){
//					LOG(INFO) << "Drop frame : " << std::dec << tmp_image.size() << "time: "<< td.total_seconds();
//					std::cout<<"drop frame:"<<tmp_image.size()<<std::endl;
					if (motion_sequence){
						tmp_image[0].setMotionStatus(nokkhum::MotionStatus::EndMotion);
						motion_sequence = false;
						this->push_to_output_image_queue(tmp_image[0]);
						//std::cerr << "end motion: " << motion_sequence << std::endl;
					}
//					std::cerr << "drop image: " << tmp_image.size() << std::endl;
					tmp_image.clear();

				}
				else{
					for(unsigned long i = 0; i<tmp_image.size();++i){
						this->push_to_output_image_queue(tmp_image[i]);
					}
//					LOG(INFO) << "write with out motion: "<<tmp_image.size();
					tmp_image.clear();

				}
//				std::cout<<"motion time : "<<boost::posix_time::to_simple_string(motion_time)<<std::endl;
//				std::cout<<"current time: "<<boost::posix_time::to_simple_string(current_time)<<std::endl;
//				std::cout<<"diff time   : "<<td<<std::endl;
			}

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

int MotionDetector::detectMotion(cv::Mat prevgray, cv::Mat gray){
	//std::cout << "hello optical flow :(" << std::endl;
	int motion_count = 0;
	int step = 30;
	cv::Mat flow;
	cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 1, step, 1,
					1, 1.2, 0);
	//			cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
	//			drawOptFlowMap(flow, frame, step+1, 1.5, CV_RGB(0, 255, 0));

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
	return motion_count;
}
}
