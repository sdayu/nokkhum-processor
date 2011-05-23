/*
 * image_processor.h
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_HPP_

#include "../job.hpp"

#include <string>
#include <queue>
#include <opencv/cv.h>

namespace nokkhum {

class ImageProcessor: public nokkhum::Job {
public:
	ImageProcessor(std::string name, std::queue<cv::Mat> &image_queue);
	virtual ~ImageProcessor();

protected:
	std::queue<cv::Mat> &image_queue;
};

}

#endif /* NOKKHUM_IMAGE_PROCESSOR_HPP_ */
