/*
 * face_preprocess.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: superizer
 */

#include "face_preprocess.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

namespace nokkhum {

FacePreprocess::FacePreprocess(ImageQueue &input_image_queue) :
		ImageProcessor("Face Preprocess", input_image_queue) {
	this->interval = 0;
	// TODO Auto-generated constructor stub

}

FacePreprocess::FacePreprocess(ImageQueue & input_image_queue,
		FacePreprocessAttribute &fpp) :
		ImageProcessor("Face Preprocess", input_image_queue) {
	this->interval = fpp.getInterval();
	this->face_database = fpp.getFaceDatabase();
	this->face_id = fpp.getFaceId();
	this->face_num = fpp.getFaceNum();
	this->i = 0;
}

FacePreprocess::~FacePreprocess() {
	// TODO Auto-generated destructor stub
}

template<typename T> std::string FacePreprocess::toString(T t) {
	std::ostringstream out;
	out << t;
	return out.str();
}

bool FacePreprocess::findWord(std::string str, std::string word) {
	size_t found = str.find(word);
	if (found != std::string::npos)
		return 1;
	return 0;
}

void FacePreprocess::start() {
	std::cout << " Hello FacePreprocess start" << std::endl;
//	cv::namedWindow("Face Detection", 1);

	int image_count = 0;

	std::string faceCascadeFilename =
			"/usr/share/opencv/lbpcascades/lbpcascade_frontalface.xml";
	std::string eyeCascadeFilename1 =
			"/usr/share/opencv/haarcascades/haarcascade_eye.xml";
	std::string eyeCascadeFilename2 =
			"/usr/share/opencv/haarcascades/haarcascade_eye_tree_eyeglasses.xml";

	cv::Mat frame;
	nokkhum::Image image;
	cv::CascadeClassifier faceCascade, eyeCascade1, eyeCascade2;

	if (!faceCascade.load(faceCascadeFilename)) {
		std::cerr << "ERROR: Could not load face classifier cascade"
				<< std::endl;
		return;
	}

	if (!eyeCascade1.load(eyeCascadeFilename1)) {
		std::cerr << "ERROR: Could not load eye classifier cascade 1 "
				<< std::endl;
		return;
	}

	if (!eyeCascade2.load(eyeCascadeFilename2)) {
		std::cerr << "ERROR: Could not load eye classifier cascade 2 "
				<< std::endl;
		return;
	}

	while (running) {

		if (input_image_queue.empty()) {
			std::this_thread::sleep_for(std::chrono::microseconds(1000));
			continue;
		}

		image = input_image_queue.pop();
		frame = image.clone();

		if (++image_count < this->interval) {
			continue;
		} else {
			image_count = 0; //reset image count
		}

		cv::Mat preprocessedFace = getPreprocessFace(frame, faceCascade,
				eyeCascade1, eyeCascade2);

		bool gotFaceAndEyes = false;
		if (preprocessedFace.data)
			gotFaceAndEyes = true;

		std::string address = "";
		if (gotFaceAndEyes) {

			//cv::imshow("Preprocess Face", preprocessedFace);

			std::string folder = this->face_database + "/face-"
					+ toString(this->face_id);
			boost::filesystem::path path(folder);
			boost::filesystem::create_directory(path);

			address = folder + "/" + toString(i) + ".jpg";
			i++;
			cv::imwrite(address, preprocessedFace);

			if (faceRect.width > 0) {
				cv::rectangle(frame, faceRect, CV_RGB(255, 255, 0), 2, CV_AA);
				cv::Scalar eyeColor = CV_RGB(0, 255, 255);
				if (leftEye.x >= 0)
					cv::circle(frame,
							cv::Point(faceRect.x + leftEye.x,
									faceRect.y + leftEye.y), 6, eyeColor, 1,
							CV_AA);
				if (rightEye.x >= 0)
					cv::circle(frame,
							cv::Point(faceRect.x + rightEye.x,
									faceRect.y + rightEye.y), 6, eyeColor, 1,
							CV_AA);
			}

		}
		std::string output;

		if (address != "")
			output = "saving face image";
		else
			output = "can't detect";

		cv::putText(frame, output, cvPoint(30, 30),
				cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(200, 200, 250),
				1, CV_AA);
		cv::imshow("Face Preprocess", frame);

		if (cv::waitKey(30) >= 0)
			break;

		if (i == face_num + 1)
			running = false;
	}

}
cv::Mat FacePreprocess::getPreprocessFace(cv::Mat& img,
		cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade1,
		cv::CascadeClassifier &eyeCascade2) {
	bool preprocessLeftAndRightSeparately = true;
	int faceWidth = 70;

	cv::Mat preprocessedFace = getPreprocessedFace(img, faceWidth, faceCascade,
			eyeCascade1, eyeCascade2, preprocessLeftAndRightSeparately,
			&faceRect, &leftEye, &rightEye, &searchedLeftEye,
			&searchedRightEye);

	return preprocessedFace;
}

} //end namespce nokkhum
