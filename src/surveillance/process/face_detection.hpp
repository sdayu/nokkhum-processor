/*
 * face_detection.h
 *
 *  Created on: May 26, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_FACE_DETECTION_H_
#define NOKKHUM_FACE_DETECTION_H_

#include "image_processor.hpp"

#include <opencv/cv.h>

namespace nokkhum {

class FaceDetection: public nokkhum::ImageProcessor {
public:
	FaceDetection(CvMatQueue &image_queue);
	virtual ~FaceDetection();

	void start();

private:
	void detectAndDraw( cv::Mat& img,
	                   cv::CascadeClassifier& cascade, cv::CascadeClassifier& nestedCascade,
	                   double scale);
};

}

#endif /* NOKKHUM_FACE_DETECTION_H_ */
