/*
 * face_detection.cpp
 *
 *  Created on: May 26, 2011
 *      Author: boatkrap
 */

#include "face_detector.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace nokkhum {

FaceDetector::FaceDetector(CvMatQueue &input_image_queue) :
		ImageProcessor("Face Detection", input_image_queue) {
	// TODO Auto-generated constructor stub

}

FaceDetector::FaceDetector(CvMatQueue & input_image_queue,
		FaceDetectorAttribute *fdp) :
		ImageProcessor("Face Detection", input_image_queue) {
	this->interval = fdp->getInterval();

}

FaceDetector::~FaceDetector() {
	// TODO Auto-generated destructor stub
}

void FaceDetector::start() {
//	cv::namedWindow("Face Detection", 1);

	int image_count = 0;

	std::string cascadeName =
			"/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
	std::string nestedCascadeName =
			"/usr/share/opencv/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
	double scale = 1.3;

	cv::Mat frame, image;
	cv::CascadeClassifier cascade, nestedCascade;

	if (!cascade.load(cascadeName)) {
		std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
		return;
	}

	if (!nestedCascade.load(nestedCascadeName)) {
		std::cerr
				<< "WARNING: Could not load classifier cascade for nested objects"
				<< std::endl;
	}


	while (running) {

		if (input_image_queue.empty()) {
			usleep(1000);
			continue;
		}

//		std::cout<< "wait: "<<image_count<<std::endl;

		frame = input_image_queue.pop();

		if (++image_count < this->interval) {
			continue;
		} else {
			image_count = 0; //reset image count
		}

//		std::cout<< "detect face"<<std::endl;

		bool result = detectAndDraw(frame, cascade, nestedCascade, scale);
		if (result){
			for(unsigned int i = 0; i < output_image_queue.getSize(); ++i){
//				std::cout<<"push face detect"<<std::endl;
				output_image_queue.get(i)->push(frame);
			}
		}


//		cv::imshow("Face Detection", frame);

		if (cv::waitKey(30) > 0)
			break;

	}
}

bool FaceDetector::detectAndDraw(cv::Mat& img, cv::CascadeClassifier& cascade,
		cv::CascadeClassifier& nestedCascade, double scale) {
	bool detect = false;
	int i = 0;
	// double t = 0;
	std::vector<cv::Rect> faces;
	const static cv::Scalar colors[] = { CV_RGB(0,0,255), CV_RGB(0,128,255),
			CV_RGB(0,255,255), CV_RGB(0,255,0), CV_RGB(255,128,0),
			CV_RGB(255,255,0), CV_RGB(255,0,0), CV_RGB(255,0,255) };
	cv::Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale),
			CV_8UC1);

	cv::cvtColor(img, gray, CV_BGR2GRAY);
	cv::resize(gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
	cv::equalizeHist(smallImg, smallImg);

	// t = (double)cvGetTickCount();
	cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0
	//|CV_HAAR_FIND_BIGGEST_OBJECT
	//|CV_HAAR_DO_ROUGH_SEARCH
			| CV_HAAR_SCALE_IMAGE
			, cv::Size(30, 30));
	// t = (double)cvGetTickCount() - t;
	// std::cout<< "detection time = " << t/((double)cvGetTickFrequency()*1000.) << " ms " <<std::endl;
	for (std::vector<cv::Rect>::const_iterator r = faces.begin();
			r != faces.end(); r++, i++) {
		cv::Mat smallImgROI;
		std::vector<cv::Rect> nestedObjects;
		cv::Point center;
		cv::Scalar color = colors[i % 8];
		int radius;
		center.x = cvRound((r->x + r->width * 0.5) * scale);
		center.y = cvRound((r->y + r->height * 0.5) * scale);
		radius = cvRound((r->width + r->height) * 0.25 * scale);
		circle(img, center, radius, color, 3, 8, 0);
		if (radius > 0)
			detect = true;
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(*r);
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		//|CV_HAAR_DO_CANNY_PRUNING
				| CV_HAAR_SCALE_IMAGE
				, cv::Size(30, 30));
		for (std::vector<cv::Rect>::const_iterator nr = nestedObjects.begin();
				nr != nestedObjects.end(); nr++) {
			center.x = cvRound((r->x + nr->x + nr->width * 0.5) * scale);
			center.y = cvRound((r->y + nr->y + nr->height * 0.5) * scale);
			radius = cvRound((nr->width + nr->height) * 0.25 * scale);
			circle(img, center, radius, color, 3, 8, 0);
			if (radius > 0)
				detect = true;
		}


	}
	return detect;
} // end detectAndDraw

} //end namespce nokkhum
