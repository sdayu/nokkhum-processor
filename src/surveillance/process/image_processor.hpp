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
#include <opencv/cv.h>

#include "../../util/cv_mat_queue.hpp"

namespace nokkhum {

class ImageProcessor: public nokkhum::Job {
public:
	ImageProcessor(std::string name, CvMatQueue &image_queue);
	virtual ~ImageProcessor();

protected:
	CvMatQueue &image_queue;
};

}

#endif /* NOKKHUM_IMAGE_PROCESSOR_HPP_ */
