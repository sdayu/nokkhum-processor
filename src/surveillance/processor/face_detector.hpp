/*
 * face_detection.h
 *
 *  Created on: May 26, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_FACE_DETECTION_H_
#define NOKKHUM_FACE_DETECTION_H_

#include "image_processor.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "../../config/face_detector_property.hpp"

namespace nokkhum {

class FaceDetector: public nokkhum::ImageProcessor {
public:
	FaceDetector(CvMatQueue &input_image_queue);
	FaceDetector(CvMatQueue &input_image_queue, FaceDetectorProperty *fdp);
	virtual ~FaceDetector();

	void start();

private:
	void detectAndDraw( cv::Mat& img,
	                   cv::CascadeClassifier& cascade, cv::CascadeClassifier& nestedCascade,
	                   double scale);
	int interval;
};

}

#endif /* NOKKHUM_FACE_DETECTION_H_ */
