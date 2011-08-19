/*
 * image_processor.h
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_HPP_

#include "../job.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../../util/cv_mat_queue.hpp"
#include "../../util/multiple_mat_queue.hpp"

namespace nokkhum {

class ImageProcessor: public nokkhum::Job {
public:
	ImageProcessor(std::string name, CvMatQueue &input_image_queue);
	virtual ~ImageProcessor();

protected:
	CvMatQueue &input_image_queue;
	//CvMatQueue *output_image_queue;

	MultipleMatQueue output_image_queue;


	bool write_to_output_queue;
};

}

#endif /* NOKKHUM_IMAGE_PROCESSOR_HPP_ */
