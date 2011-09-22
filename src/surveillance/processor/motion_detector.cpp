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

#include <ctime>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace nokkhum {

MotionDetector::MotionDetector(CvMatQueue &input_image_queue) :
	ImageProcessor("Motion Detection", input_image_queue) {
	// TODO Auto-generated constructor stub

}

MotionDetector::MotionDetector(CvMatQueue &input_image_queue, MotionDetectorProperty *mdp) :
	ImageProcessor("Motion Detection", input_image_queue) {
	this->interval = mdp->getInterval();
	this->resolution = mdp->getResolution();

	this->drop_motion = 20;

}

MotionDetector::~MotionDetector() {
	// TODO Auto-generated destructor stub
}

void MotionDetector::start() {
//	std::cout<<"Motion detector start"<<std::endl;
	cv::namedWindow("Motion Detection", 1);

	cv::Mat prevgray, gray, flow, cflow, frame;

	boost::posix_time::ptime current_time, motion_time;
	motion_time = boost::posix_time::microsec_clock::local_time();

	int motion_count = 0;
	int step = 15;

	int image_count = 0;

	std::vector<cv::Mat> tmp_mat;

	while (running) {

		while(input_image_queue.empty()){
			usleep(100);
		}

		frame = input_image_queue.pop();
		tmp_mat.push_back(frame);

		if(++image_count < this->interval){
//			std::cout<<image_count<<" continue ..."<<std::endl;
			continue;
		}
		else{
//			std::cout<<image_count<<" reset ..."<<std::endl;

			image_count=0; //reset image count
		}

		motion_count = 0;

		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		if (prevgray.data) {
			cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 1, step, 1,
				1, 1.2, 0);
			cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
			drawOptFlowMap(flow, cflow, step+1, 1.5, CV_RGB(0, 255, 0));

			for (int y = 0; y < cflow.rows; y += step+1){
				for (int x = 0; x < cflow.cols; x += step+1) {
					const cv::Point2f& fxy = flow.at<cv::Point2f> (y, x);

					if(cvRound(fxy.x) != 0 && cvRound(fxy.y)!= 0){
						motion_count++;
					}
				}
			}

			if(motion_count > 4){
				cv::circle(cflow, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
				cv::circle(frame, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);

//				std::cout<<"temporary queue size: "<< std::dec << tmp_mat.size()<<std::endl;
				for(unsigned long i = 0; i<tmp_mat.size();++i){
					cv::Mat tmp_frame = tmp_mat[i];
					for(unsigned long j = 0; j<output_image_queue.getSize();++j){
//						std::cout<<"push frame: "<<i<<" to queue: "<<j<<std::endl;
						output_image_queue.get(j)->push(tmp_frame);
					}
				}
				tmp_mat.clear();
//				std::cout<<"affter clear: "<<tmp_mat.size()<<std::endl;
				motion_time = boost::posix_time::microsec_clock::local_time();
			}
			else{
				current_time = boost::posix_time::microsec_clock::local_time();
				boost::posix_time::time_duration td = current_time - motion_time;
				if(td.seconds() >= this->drop_motion){
//					std::cout<<"\n\n\n\n\n\n\n\ndrop frame:"<<tmp_mat.size()<<std::endl;
					tmp_mat.clear();

				}
				else{
					for(unsigned long i = 0; i<tmp_mat.size();++i){
						cv::Mat tmp_frame = tmp_mat[i];
						for(unsigned long j = 0; j<output_image_queue.getSize();++j){
//							std::cout<<"push frame with out motion: "<<i<<" to queue: "<<j<<std::endl;
							output_image_queue.get(j)->push(tmp_frame);
						}
					}
//					std::cout<<"write with out motion: "<<tmp_mat.size()<<std::endl;
					tmp_mat.clear();

				}
//				std::cout<<"motion time : "<<boost::posix_time::to_simple_string(motion_time)<<std::endl;
//				std::cout<<"current time: "<<boost::posix_time::to_simple_string(current_time)<<std::endl;
//				std::cout<<"diff time   : "<<td<<std::endl;
			}

			cv::imshow("Motion Detection", cflow);
		}

		if (cv::waitKey(30) >= 0)
			break;

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

//	std::cout << "motion count : "<< motionCount<<std::endl;
//	if(motionCount > 2){
//		std::cout<<"It has motion"<<std::endl;
//		cv::circle(cflowmap, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
//	}
}

}
