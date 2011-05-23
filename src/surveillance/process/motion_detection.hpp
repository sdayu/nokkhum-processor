/*
 * motion_detection.h
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_MOTION_DETECTION_HPP_
#define NOKKHUM_MOTION_DETECTION_HPP_

#include "image_processor.hpp"

#include <queue>
#include <opencv/cv.h>

namespace nokkhum {

class MotionDetection: public nokkhum::ImageProcessor {
public:
	MotionDetection(std::queue<cv::Mat> &image_queue);
	virtual ~MotionDetection();

	void start();
private:
	void drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step,
			                    double scale, const cv::Scalar& color);
};

}

#endif /* NOKKHUM_MOTION_DETECTION_HPP_ */
