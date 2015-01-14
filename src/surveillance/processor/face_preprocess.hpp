/*
 * face_preprocess.hpp
 *
 *  Created on: Jan 15, 2014
 *      Author: superizer
 */

#ifndef NOKKHUM_FACE_PREPROCESS_H_
#define NOKKHUM_FACE_PREPROCESS_H_

#include "image_processor.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <string>

#include "../../config/face_preprocess_attribute.hpp"
//#include "detectObject.h"
//#include "preprocessFace.h"
//#include "recognition.h"
//#include "ImageUtils.h"

namespace nokkhum {

class FacePreprocess: public nokkhum::ImageProcessor {
public:
	FacePreprocess(ImageQueue &input_image_queue);
	FacePreprocess(ImageQueue &input_image_queue, FacePreprocessAttribute &fpp);
	virtual ~FacePreprocess();

	void start();

private:
	int face_id;
	int i;
	int face_num;
	std::string face_database;
	int interval;
	cv::Rect faceRect;
	cv::Rect searchedLeftEye, searchedRightEye;
	cv::Point leftEye, rightEye;
	template <typename T> std::string toString(T t);
	bool findWord(std::string str, std::string word);
	cv::Mat getPreprocessFace( cv::Mat& img,
			cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade1, cv::CascadeClassifier &eyeCascade2);

};

}

#endif /* NOKKHUM_FACE_PREPROCESS_H_ */
