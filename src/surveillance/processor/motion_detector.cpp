/*
 * motion_detection.cpp
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#include "motion_detector.hpp"

#include <iostream>
#include <algorithm>
#include <queue>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

#include <glog/logging.h>
#include <ctime>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

namespace nokkhum {

MotionDetector::MotionDetector(ImageQueue &input_image_queue) :
		ImageProcessor("Motion Detection", input_image_queue) {
	// TODO Auto-generated constructor stub
	this->interval = 1;
	this->sensitive = 100;
	this->enable_area_of_interest = false;
	this->wait_motion_time = 10;

}

MotionDetector::MotionDetector(ImageQueue &input_image_queue,
		MotionDetectorAttribute &mdp) :
		ImageProcessor("Motion Detection", input_image_queue) {
	//std::cout << "hello optical flow constructor :(" << std::endl;
	this->interval = mdp.getInterval();
	this->sensitive = mdp.getSensitive();
	this->enable_area_of_interest = mdp.getEnableAreaOfInterest();
	this->wait_motion_time = mdp.getWaitMotionTime();
	//this->pointStart = mdp.getStartPoint();
	//this->pointEnd = mdp.getEndPoint();
	this->mul_point = mdp.getMulPoint();
	this->area_name = mdp.getAreaName();
	//this->width = mdp.get;

}

MotionDetector::~MotionDetector() {
	// TODO Auto-generated destructor stub
}

void MotionDetector::start() {
	//std::cout << "enable area of interest : " << this->enable_area_of_interest << std::endl;

//	std::cout<<"Motion detector start"<<std::endl;
	//cv::namedWindow("Motion Detection", 1);
	const int buffer_size = 20;
	cv::Mat prevgray, gray, flow, cflow, frame;

	boost::posix_time::ptime current_time, motion_time;
//	motion_time = boost::posix_time::microsec_clock::local_time();

	bool is_motion = false;
	//int step = 30; // before step = 15

	int image_count = 0;

	std::queue<nokkhum::Image> buffer_image;
	nokkhum::Image image;
	bool motion_sequence = false;

	//Multiple area of interest

	std::vector<cv::Mat> mask;
	std::vector<int> minX, minY, maxX, maxY;
	int x1, x2, y1, y2;
	std::vector<cv::Mat> backgroundImageVec, currentImageVec;

	if (this->enable_area_of_interest) {
		for (int i = 0; i < (int) this->mul_point.size(); i++) {
			mask.push_back(cv::Mat(480, 640, CV_8UC3));
			cv::fillConvexPoly(mask[i], mul_point[i], cv::Scalar(255, 255, 255),
					8, 0);
		}

		//Sort point
		for (int i = 0; i < (int) this->mul_point.size(); i++) {
			std::sort(mul_point[i].begin(), mul_point[i].end(),
					[](cv::Point a, cv::Point b) {
						return a.x < b.x;
					});

			minX.push_back(mul_point[i][0].x);
			maxX.push_back(mul_point[i][mul_point[i].size() - 1].x);

			//std::sort(mul_point[i].begin(), mul_point[i].end(), this->sortY);
			std::sort(mul_point[i].begin(), mul_point[i].end(),
					[](cv::Point a, cv::Point b) {
						return a.y < b.y;
					});
			minY.push_back(mul_point[i][0].y);
			maxY.push_back(mul_point[i][mul_point[i].size() - 1].y);
		}

	}

	while (running) {

		if (input_image_queue.empty()) {
			std::this_thread::sleep_for(std::chrono::microseconds(1000));
			continue;
		}

		image = input_image_queue.pop();

		frame = image.get();
		/*std::cout << "frame size " << frame.cols << " " << frame.rows << std::endl;
		 *


		 std::cout << " point start : " << this->pointStart.x << "," << this->pointStart.y << " "
		 << " point end : " << this->pointEnd.x << "," << this->pointEnd.y << std::endl;*/

		//if(this->enable_area_of_interest)
		//	cv::rectangle(frame ,cvPoint(this->pointStart.x, this->pointStart.y),cvPoint(this->pointEnd.x, this->pointEnd.y),cvScalar(255,0,0));
		buffer_image.push(image);

		if (++image_count < this->interval) {
//			std::cout<<image_count<<" continue ..."<<std::endl;
			continue;
		} else {
//			std::cout<<image_count<<" reset ..."<<std::endl;

			image_count = 0; //reset image count
		}

		//cv::rectangle(frame,cvPoint(this->pointStart.x, this->pointStart.y),cvPoint(this->pointEnd.x, this->pointEnd.y),cvScalar(255,0,0));
		//cv::imshow("Original", frame);

		//if(this->enable_area_of_interest){
		//	frame = frame(cv::Rect(this->pointStart.x, this->pointStart.y, this->pointEnd.x - this->pointStart.x, this->pointEnd.y - this->pointStart.y));
		//}

		this->width = frame.cols;

		cv::cvtColor(frame, gray, CV_BGR2GRAY);

		std::string check;

		if (this->enable_area_of_interest) {
			//Create Background AOI
			if (backgroundImageVec.size() == 0)
				for (int i = 0; i < (int) this->mul_point.size(); ++i) {
					x1 = minX[i];
					y1 = minY[i];
					x2 = maxX[i];
					y2 = maxY[i];

					currentImageVec.push_back(frame & mask[i]); //Create Polygon
					backgroundImageVec.push_back(
							currentImageVec[i](
									cv::Rect(x1, y1, x2 - x1, y2 - y1))); //Resize Image
				}


			/*cv::Mat area_all;
			area_all = frame & mask[0];
			for (int i = 1; i < (int) this->mul_point.size(); ++i) {
				area_all = area_all | (frame & mask[i]);
			}*/

			currentImageVec.clear();
			//Draw Polygon
			for (int i = 0; i < (int) this->mul_point.size(); ++i) {
				x1 = minX[i];
				y1 = minY[i];
				x2 = maxX[i];
				y2 = maxY[i];
				currentImageVec.push_back(frame & mask[i]);
				currentImageVec[i] = currentImageVec[i](
						cv::Rect(x1, y1, x2 - x1, y2 - y1));
				//cv::imshow("ROI " + std::to_string(i),currentImageVec[i]);
			}

			std::string s = "";
			for (int i = 0; i < (int) this->mul_point.size(); ++i) {
				bool check = BackgroundSubtraction(backgroundImageVec[i],
						currentImageVec[i]);

				if (check) {
					s += area_name[i] + " ";
				}
			}

			if (s == "")
				check = "No Motion";
			else {
				check = "Area " + s + "have motion";
				is_motion = true;
			}

			/*cv::putText(area_all, check, cv::Point(30, 450),
					cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0, 0, 250),
					1, CV_AA);
			cv::imshow("Area All", area_all);*/

			for (int i = 0; i < (int) this->mul_point.size(); ++i) {
				backgroundImageVec[i] = currentImageVec[i].clone();
			}

		} else {
			if (prevgray.data) {
				if (!this->enable_area_of_interest) {
					is_motion = detectMotion(prevgray, gray);
				}
			}
		}

		if (is_motion) {
			//				cv::circle(cflow, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
			//				std::cerr << "motion count: " << is_motion <<" sq: "<<motion_sequence << std::endl;
			cv::circle(frame, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
			//				LOG(INFO) << "Have motion: " << std::dec << buffer_image.size() ;
			//				std::cout<<"temporary queue size: "<< std::dec << buffer_image.size()<<std::endl;

			if (!motion_sequence) {
				buffer_image.front().setMotionStatus(
						nokkhum::MotionStatus::BeginMotion);
				motion_sequence = true;
				Json::Value description;
				description["motion_area"] = check;
				buffer_image.front().setDescription(description);
				// std::cerr << "start motion: " << motion_sequence << std::endl;
			}

			// std::cerr << "image in buffer: " << buffer_image.size() << std::endl;

			while (!buffer_image.empty()) {
				this->push_to_output_image_queue(buffer_image.front());
				buffer_image.pop();
			}

			//				std::cout<<"affter clear: "<<buffer_image.size()<<std::endl;
			motion_time = boost::posix_time::microsec_clock::local_time();
		} else {

			current_time = boost::posix_time::microsec_clock::local_time();
			boost::posix_time::time_duration td = current_time - motion_time;

			// LOG(INFO) << "motion diff time: " << td.total_seconds();
			if (td.total_seconds() >= this->wait_motion_time) {
				//					LOG(INFO) << "Drop frame : " << std::dec << buffer_image.size() << "time: "<< td.total_seconds();
				//					std::cout<<"drop frame:"<<buffer_image.size()<<std::endl;
				if (motion_sequence) {
					buffer_image.front().setMotionStatus(
							nokkhum::MotionStatus::EndMotion);
					motion_sequence = false;
					this->push_to_output_image_queue(buffer_image.front());
					// std::cerr << "end motion: " << motion_sequence << std::endl;
				}
				//std::cerr << "drop image: " << buffer_image.size() << std::endl;

				while (buffer_image.size() > buffer_size) {
					buffer_image.pop();
					//						std::cerr << "drop image: " << buffer_image.size() << std::endl;
				}

			} else {
				while (!buffer_image.empty()) {
					this->push_to_output_image_queue(buffer_image.front());
					buffer_image.pop();
				}
				//					LOG(INFO) << "write with out motion: "<<buffer_image.size();

			}
			//if(is_motion){
			//
			//			cv::imshow("Motion Detection", cflow);
		}
		//if (cv::waitKey(30) >= 0)
		//	break;

		std::swap(prevgray, gray);
	}
}

void MotionDetector::drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap,
		int step, double scale, const cv::Scalar& color) {
//	int motionCount = 0;
	for (int y = 0; y < cflowmap.rows; y += step) {
		for (int x = 0; x < cflowmap.cols; x += step) {
			const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
			cv::line(cflowmap, cv::Point(x, y),
					cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), color);
			cv::circle(cflowmap, cv::Point(x, y), 2, color, -1);
		}
	}

}

bool MotionDetector::detectMotion(cv::Mat prevgray, cv::Mat gray) {
	// std::cout << "hello optical flow :(" << std::endl;
	int motion_count = 0;
	//int step = 30;
	//double step = 585*(1-(this->sensitive/100.0)) + 15;
	double step = (this->width - 15) * (1 - (this->sensitive / 100.0)) + 15;
	//std::cout << "width = " << this->width << std::endl;
	cv::Mat flow;
	cv::calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 1, step, 1, 1, 1.2,
			0);
	//std::cout << "step = " << step << std::endl;
	//cv::cvtColor(prevgray, cflow, CV_GRAY2BGR);
	//drawOptFlowMap(flow, frame, step+1, 1.5, CV_RGB(0, 255, 0));

	//			for (int y = 0; y < cflow.rows; y += step+1){
	//				for (int x = 0; x < cflow.cols; x += step+1) {
	for (int y = 0; y < flow.rows; y += step + 1) {
		for (int x = 0; x < flow.cols; x += step + 1) {
			const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);

			if (cvRound(fxy.x) != 0 && cvRound(fxy.y) != 0) {
				motion_count++;
			}
		}
	}

	if (motion_count > 0)
		return true;
	else
		return false;

}

bool MotionDetector::BackgroundSubtraction(cv::Mat background,
		cv::Mat current) {
	double sensitive = 50;
	cv::Mat background_bw;
	cv::Mat current_bw;
	cv::Mat diff;
	cv::Mat thresh;
	cvtColor(background, background_bw, CV_RGB2GRAY);
	cvtColor(current, current_bw, CV_RGB2GRAY);
	diff = abs(current_bw - background_bw);
	double thres = (1 - sensitive / 100.0) * 220.0;
	threshold(diff, thresh, thres, 255, CV_THRESH_BINARY);
	int count_motion = cv::countNonZero(thresh);
	if (count_motion > 3) {
		return 1;
	} else {
		return 0;
	}
}

}
