/*
 * motion_detection.h
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_MOTION_DETECTION_HPP_
#define NOKKHUM_MOTION_DETECTION_HPP_

#include "image_processor.hpp"

#include <opencv2/core/core.hpp>

#include "../../util/cv_mat_queue.hpp"
#include "../../config/motion_detector_attribute.hpp"

namespace nokkhum {

class MotionDetector : public nokkhum::ImageProcessor {
public:
	MotionDetector(CvMatQueue &input_image_queue);
	MotionDetector(CvMatQueue &input_image_queue, MotionDetectorAttribute &mdp);
	virtual ~MotionDetector();

	void start();
private:
	void drawOptFlowMap(const cv::Mat& flow, cv::Mat& cflowmap, int step,
			                    double scale, const cv::Scalar& color);

    int interval;
    int resolution;
    int drop_motion;
};

}

#endif /* NOKKHUM_MOTION_DETECTION_HPP_ */
