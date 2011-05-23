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
//	std::cout << "running: " << running << std::endl;
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

		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		if (prevgray.data) {
//			cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3,
//					5, 1.2, 0);
			cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 1, 30, 1,
				1, 1.1, 0);
			cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
//			drawOptFlowMap(flow, cflow, 16, 1.5, CV_RGB(0, 255, 0));
			drawOptFlowMap(flow, cflow, 31, 1.5, CV_RGB(0, 255, 0));
			cv::imshow("video", cflow);
		}

		if (cv::waitKey(30) >= 0)
			break;
		std::swap(prevgray, gray);
	}
}

void MotionDetection::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap,
		int step, double scale, const cv::Scalar& color) {
	for (int y = 0; y < cflowmap.rows; y += step)
		for (int x = 0; x < cflowmap.cols; x += step) {
			const cv::Point2f& fxy = flow.at<cv::Point2f> (y, x);
			cv::line(cflowmap, cv::Point(x, y),
					cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), color);
			cv::circle(cflowmap, cv::Point(x, y), 2, color, -1);
		}
}

}
