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

MotionDetection::MotionDetection(std::queue<cv::Mat> &image_queue) :
	ImageProcessor("Motion Detection", image_queue) {
	// TODO Auto-generated constructor stub

}

MotionDetection::~MotionDetection() {
	// TODO Auto-generated destructor stub
}

void MotionDetection::start() {
	cv::namedWindow("video", 1);

	cv::Mat prevgray, gray, flow, cflow, frame;
	cv::Mat diff;

	int count = 0;
	bool isCompute = false;

	std::cout << "motion running: " << running << std::endl;
	while (running) {
		//time ( &rawtime );

		//cv::imshow("video", multiple_queue.get(1).front());
		//multiple_queue.get(1).pop();
		//if(waitKey(30) >= 0) break;

		while(image_queue.empty()){
			usleep(100);
		}

		frame = image_queue.front();
		image_queue.pop();
		if (isCompute){
			isCompute = false;
		}
		else{
			isCompute = true;
			continue;
		}

		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		if (prevgray.data) {
//			cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3,
//					5, 1.2, 0);
			cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 1, 30, 1,
				1, 1.2, 0);
			cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
//			drawOptFlowMap(flow, cflow, 16, 1.5, CV_RGB(0, 255, 0));
			drawOptFlowMap(flow, cflow, 31, 1.5, CV_RGB(0, 255, 0));
			cv::imshow("video", cflow);

			cv::absdiff(gray, prevgray, diff);

//			cv::compare(gray, prevgray, diff, cv::CMP_NE);
			count = cv::countNonZero(diff);
			std::cout<<"count zero : "<<count<<std::endl;

//			if (count>100000)
//				cv::waitKey(0);


		}

		if (cv::waitKey(30) >= 0)
			break;
		std::swap(prevgray, gray);
	}
}

void MotionDetection::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap,
		int step, double scale, const cv::Scalar& color) {
	int motionCount = 0;
	for (int y = 0; y < cflowmap.rows; y += step){
		for (int x = 0; x < cflowmap.cols; x += step) {
			const cv::Point2f& fxy = flow.at<cv::Point2f> (y, x);
			cv::line(cflowmap, cv::Point(x, y),
					cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), color);
			cv::circle(cflowmap, cv::Point(x, y), 2, color, -1);

			if(cvRound(fxy.x) != 0 || cvRound(fxy.y)!= 0){
				motionCount++;
			}
		}
	}

	std::cout << "motion count : "<< motionCount<<std::endl;
	if(motionCount > 10){
		std::cout<<"It has motion"<<std::endl;
		cv::circle(cflowmap, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
	}
}

}
