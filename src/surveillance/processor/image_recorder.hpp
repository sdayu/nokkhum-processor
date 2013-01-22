/*
 * image-recorder.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_IMAGE_RECORDER_HPP_
#define NOKKHUM_IMAGE_RECORDER_HPP_

#include <string>

#include "image_processor.hpp"
#include "../../config/image_recorder_attribute.hpp"

namespace nokkhum {

class ImageRecorder: public nokkhum::ImageProcessor {
public:
	ImageRecorder(ImageQueue &input_image_queue);
	ImageRecorder(ImageQueue &input_image_queue, ImageRecorderAttribute &irp);
	virtual ~ImageRecorder();

	void start();

private:
	unsigned int width;
	unsigned int height;
	std::string directory;
	int interval;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_RECORDER_HPP_ */
