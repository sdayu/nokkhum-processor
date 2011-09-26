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
#include "../../config/image_recorder_property.hpp"

namespace nokkhum {

class ImageRecorder: public nokkhum::ImageProcessor {
public:
	ImageRecorder(CvMatQueue &input_image_queue);
	ImageRecorder(CvMatQueue &input_image_queue, ImageRecorderProperty *irp);
	virtual ~ImageRecorder();

	void start();

private:
	unsigned int width;
	unsigned int height;
	std::string directory;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_IMAGE_RECORDER_HPP_ */
