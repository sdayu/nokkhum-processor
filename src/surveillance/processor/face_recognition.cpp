/*
 * face_recognition.cpp
 *
 *  Created on: May 23, 2013
 *      Author: superizer
 */

#include "face_recognition.hpp"

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

FaceRecognition::FaceRecognition(ImageQueue &input_image_queue) :
		ImageProcessor("Face Recognition", input_image_queue) {
	this->interval = 0;
	// TODO Auto-generated constructor stub

}

FaceRecognition::FaceRecognition(ImageQueue & input_image_queue,
		FaceRecognitionAttribute &frp) :
		ImageProcessor("Face Recognition", input_image_queue) {
	this->interval = frp.getInterval();
	this->face_database = frp.getFaceDatabase();

}

FaceRecognition::~FaceRecognition() {
	// TODO Auto-generated destructor stub
}

template<typename T> std::string FaceRecognition::toString(T t) {
	std::ostringstream out;
	out << t;
	return out.str();
}

bool FaceRecognition::findWord(std::string str, std::string word) {
	size_t found = str.find(word);
	if (found != std::string::npos)
		return 1;
	return 0;
}

void FaceRecognition::start() {
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

	trainAndLearn();

	while (running) {

		if (input_image_queue.empty()) {
			std::this_thread::sleep_for(std::chrono::microseconds(1000));
			continue;
		}

//		std::cout<< "wait: "<<image_count<<std::endl;
		image = input_image_queue.pop();
		frame = image.clone();

		if (++image_count < this->interval) {
			continue;
		} else {
			image_count = 0; //reset image count
		}

		int result = detectAndPredict(frame, faceCascade, eyeCascade1,
				eyeCascade2);

		// save image
		if (result != -1) {
				Json::Value description;

				std::string name;
				if(result == 0) name = "tone";
				else if(result == 1) name = "oat";
				else if(result == 2) name = "ierk";
				else if(result == 3) name = "lin";

				description["face_name"] = "face-" + name;
				image.setDescription(description);
				image << frame;
				for(unsigned int i = 0; i < output_image_queue.getSize(); ++i){
					output_image_queue.get(i)->push(image);
				}
			}
		}

//		cv::imshow("Face Recognition", frame);
//
//		if (cv::waitKey(30) > 0)
//			break;

}
void FaceRecognition::trainAndLearn() {

	boost::filesystem::path path(this->face_database);
	boost::filesystem::recursive_directory_iterator itr(path);

	while (itr != boost::filesystem::recursive_directory_iterator()) {
		std::string dir = itr->path().string();
		if (FaceRecognition::findWord(dir, ".jpg")) {
			//cout << dir << endl;
			this->preprocessedFaces.push_back(
					cv::imread(dir, CV_LOAD_IMAGE_GRAYSCALE));
			if (FaceRecognition::findWord(dir, "face-0"))
				this->faceLabels.push_back(0); // tone
			else if (FaceRecognition::findWord(dir, "face-1"))
				this->faceLabels.push_back(1); // oat
			else if (FaceRecognition::findWord(dir, "face-2"))
				this->faceLabels.push_back(2); // ierk
			else if (FaceRecognition::findWord(dir, "face-3"))
				this->faceLabels.push_back(3); // lin
		}
		++itr;
	}

	if ((this->preprocessedFaces.size() > 0)
			&& (this->preprocessedFaces.size() == this->faceLabels.size())) {
		this->model = learnCollectedFaces(this->preprocessedFaces,
				this->faceLabels, "FaceRecognizer.Fisherfaces");
	}

}

int FaceRecognition::detectAndPredict(cv::Mat& img,
		cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade1,
		cv::CascadeClassifier &eyeCascade2) {

	cv::Rect faceRect;
	cv::Rect searchedLeftEye, searchedRightEye;
	cv::Point leftEye, rightEye;
	const bool preprocessLeftAndRightSeparately = true;

	const int faceWidth = 70;
//	const int faceHeight = faceWidth;

	cv::Mat preprocessedFace = getPreprocessedFace(img, faceWidth, faceCascade,
			eyeCascade1, eyeCascade2, preprocessLeftAndRightSeparately,
			&faceRect, &leftEye, &rightEye, &searchedLeftEye,
			&searchedRightEye);

	bool gotFaceAndEyes = false;

	if (preprocessedFace.data)
		gotFaceAndEyes = true;

	if (gotFaceAndEyes && (this->preprocessedFaces.size() > 0)
			&& (this->preprocessedFaces.size() == this->faceLabels.size())) {
		cv::Mat reconstructedFace;
		reconstructedFace = reconstructFace(this->model, preprocessedFace);

		double similarity = getSimilarity(preprocessedFace, reconstructedFace);

		std::string name = "Unknown";
		float UNKNOWN_PERSON_THRESHOLD = 0.7f;

		if (similarity < UNKNOWN_PERSON_THRESHOLD) {
			int iden = model->predict(preprocessedFace);
			return iden;
		}
	}
	return -1; // unknown people

} // end recognitionAndDetect

} //end namespce nokkhum
