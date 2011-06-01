/*
 * motion_detection.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "motion_detection.hpp"

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace nokkhum {

MotionDetection::MotionDetection(CvMatQueue &image_queue) :
	ImageProcessor("Motion Detection", image_queue) {
	// TODO Auto-generated constructor stub

}

MotionDetection::~MotionDetection() {
	// TODO Auto-generated destructor stub
}

void MotionDetection::start() {
//	cv::namedWindow("Motion Detection", 1);

	cv::Mat prevgray, gray, flow, cflow, frame;

	int motion_count = 0;
	int step = 15;

	const int compute_step = 3;
	int image_count = 0;

	while (running) {

		while(image_queue.empty()){
			usleep(100);
		}

		frame = image_queue.pop();
		if(image_count++ < compute_step){
			continue;
		}
		else{
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
			}

			//cv::imshow("Motion Detection", cflow);
		}

//		if (cv::waitKey(30) >= 0)
//			break;

		std::swap(prevgray, gray);
	}
}

void MotionDetection::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap,
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
