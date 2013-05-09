/*
 * image_processor.h
 *
 *  Created on: May 23, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_PROCESSOR_HPP_
#define NOKKHUM_IMAGE_PROCESSOR_HPP_

#include <memory>
#include <thread>

#include "../job.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../../util/image_queue.hpp"
#include "../../util/multiple_image_queue.hpp"

namespace nokkhum {

class ImageProcessor: public nokkhum::Job {
public:
	ImageProcessor(std::string name, ImageQueue &input_image_queue);
	virtual ~ImageProcessor();

	std::shared_ptr<ImageQueue> getNewOutputImageQueue();

protected:
	ImageQueue &input_image_queue;
	//CvMatQueue *output_image_queue;

	MultipleImageQueue output_image_queue;
	bool write_to_output_queue;

	void push_to_output_image_queue(nokkhum::Image);
	void start();
};

}

#endif /* NOKKHUM_IMAGE_PROCESSOR_HPP_ */
