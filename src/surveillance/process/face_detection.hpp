/*
 * face_detection.h
 *
 *  Created on: May 26, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_FACE_DETECTION_H_
#define NOKKHUM_FACE_DETECTION_H_

#include "image_processor.hpp"

namespace nokkhum {

class FaceDetection: public nokkhum::ImageProcessor {
public:
	FaceDetection(CvMatQueue &image_queue);
	virtual ~FaceDetection();

	void start();
};

}

#endif /* NOKKHUM_FACE_DETECTION_H_ */
