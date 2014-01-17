/*
 * face_recognition.hpp
 *
 *  Created on: Nov 11, 2013
 *      Author: superizer
 */

#ifndef NOKKHUM_FACE_RECOGNITION_H_
#define NOKKHUM_FACE_RECOGNITION_H_

#include "image_processor.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "../../config/face_recognition_attribute.hpp"
#include "detectObject.h"
#include "preprocessFace.h"
#include "recognition.h"
#include "ImageUtils.h"

namespace nokkhum {

class FaceRecognition: public nokkhum::ImageProcessor {
public:
	FaceRecognition(ImageQueue &input_image_queue);
	FaceRecognition(ImageQueue &input_image_queue, FaceRecognitionAttribute &frp);
	virtual ~FaceRecognition();

	void start();

private:
	int detectAndPredict( cv::Mat& img,
			cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade1, cv::CascadeClassifier &eyeCascade2);
	void trainAndLearn();
	template <typename T> std::string toString(T t);
	bool findWord(std::string str, std::string word);
	int interval;
	std::string face_database;
	std::vector<cv::Mat> preprocessedFaces;
	std::vector<int> faceLabels;
	cv::Ptr<FaceRecognizer> model;
};

}

#endif /* NOKKHUM_FACE_RECOGNITION_H_ */
